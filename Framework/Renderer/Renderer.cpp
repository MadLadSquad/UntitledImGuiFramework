#include "Renderer.hpp"
#ifdef __EMSCRIPTEN__
    #include <emscripten.h>
    #include <imgui_internal.h>
#endif
#include <yaml-cpp/yaml.h>
#include <Core/Components/Instance.hpp>
#include <Renderer/ImGui/ImGui.hpp>
#include <GLFW/glfw3.h>
#include <Interfaces/WindowInterface.hpp>
#include <Global.hpp>

#include <Platform/WASM.hpp>

// 1:1 string binding with C/Internal/RendererData.h
static constexpr const char* RENDERER_TYPE_STRINGS[UIMGUI_RENDERER_TYPE_COUNT][UIMGUI_RENDERER_TYPE_ALT_NAMES_COUNT] =
{
    { "opengl",     "gl",       "legacy",   "ogl"       },
    { "vulkan",     "vk",       "webgpu",   "wgpu"      },
    { "custom",     "custom",   "custom",   "custom"    }
};

void UImGui::RendererInternal::start()
{
    loadConfig();
    renderer = CAST(decltype(renderer), renderers[static_cast<int>(data.rendererType)]);

    // Global should be initialised before the renderer is started because global starts the window and the window
    auto& global = Global::get();
    global.renderer = this;
    global.init();

    renderer->init(metadata);

    global.modulesManagerr.init(global.instance->initInfo.configDir);
    GUIRenderer::init(renderer);

#ifdef __EMSCRIPTEN__
    emscripten_set_main_loop_arg(tick, this, 0, true);
#else
    while (!glfwWindowShouldClose(Window::getInternal()))
        tick(this);
#endif
}

void UImGui::RendererInternal::stop() const noexcept
{
    GUIRenderer::shutdown(renderer);
    renderer->destroy();
    Global::get().modulesManagerr.destroy();
    Window::get().destroyWindow();
}

void UImGui::RendererInternal::tick(void* rendererInstance) noexcept
{
    auto& inst = *(static_cast<RendererInternal*>(rendererInstance));
    static double deltaTime = 0.0f;

#ifndef __EMSCRIPTEN__
    inst.bIdling = false;
    if (inst.data.idleFrameRate > 0.0f && inst.data.bEnablePowerSavingMode)
    {
        const double waitTimeout = 1.0 / inst.data.idleFrameRate;

        Timer timer;
        timer.start();

        glfwWaitEventsTimeout(waitTimeout);

        timer.stop();
        const double elapsed = timer.get();
        const double duration = elapsed - waitTimeout;
        const double idleExpected = 1.0 / inst.data.idleFrameRate;

        inst.bIdling = duration > (idleExpected * 0.9);
    }
#endif

    glfwPollEvents();

    const double now = glfwGetTime();
    deltaTime = now - inst.lastTime;
    inst.lastTime = now;

    // Updates the state of the keybindings
    Global::get().window.updateKeyState();

#ifdef __EMSCRIPTEN__
    if (inst.data.idleFrameRate > 0.0f && inst.data.bEnablePowerSavingMode)
    {
        ImGuiContext& g = *ImGui::GetCurrentContext();
        bool bHasInputEvent = !g.InputEventsQueue.empty();

        static double lastRefreshTime = 0.0f;
        static double accumulatedTime = 0.0f;
        accumulatedTime += deltaTime;

        bool bShouldIdle = false;
        if (bHasInputEvent)
        {
            inst.bIdling = false;
            bShouldIdle = false;
        }
        else
        {
            inst.bIdling = true;
            if ((accumulatedTime - lastRefreshTime) < 1.0 / inst.data.idleFrameRate)
                bShouldIdle = true;
            else
                bShouldIdle = false;
        }

        if (!bShouldIdle)
        {
            lastRefreshTime = accumulatedTime;
            accumulatedTime = 0.0f;
        }
        else
        {
            lastRefreshTime = 0.0f;
            return;
        }
    }
#endif

    // Do not render if the window is minimised
    if (Window::getWindowIconified())
        glfwWaitEvents();

    inst.renderer->renderStart(deltaTime);
    GUIRenderer::beginUI(static_cast<float>(deltaTime), inst.renderer);
    inst.renderer->renderEnd(deltaTime);
}

void UImGui::RendererInternal::loadConfig() noexcept
{
    YAML::Node node;
    try
    {
        node = YAML::LoadFile((Instance::get()->initInfo.configDir + "Core/Renderer.yaml").c_str());
    }
    catch (YAML::BadFile&)
    {
        Logger::log("Invalid renderer config file, please fix this error before publishing for production! Because of the missing data we're using the default settings!", ULOG_LOG_TYPE_ERROR);
        return;
    }

    if (node["renderer"])
    {
        auto tmp = node["renderer"].as<FString>();
        Utility::toLower(tmp);

        for (char i = 0; i < UIMGUI_RENDERER_TYPE_COUNT; i++)
        {
            for (char j = 0; j < UIMGUI_RENDERER_TYPE_ALT_NAMES_COUNT; j++)
            {
                if (tmp == RENDERER_TYPE_STRINGS[i][j])
                {
                    data.rendererType = static_cast<RendererType>(i);
                    goto escape_render_type_loop;
                }
            }
        }
escape_render_type_loop:;
#ifdef __EMSCRIPTEN__
        data.rendererType = data.rendererType == UIMGUI_RENDERER_TYPE_VULKAN_WEBGPU ? static_cast<RendererType>(em_supports_wgpu()) : data.rendererType;
#endif
    }
    if (node["v-sync"])
        data.bUsingVSync = node["v-sync"].as<bool>();
    if (node["msaa-samples"])
        data.msaaSamples = node["msaa-samples"].as<uint32_t>();

    const auto& powerSaving = node["power-saving"];
    if (powerSaving)
    {
        if (powerSaving["enabled"])
            data.bEnablePowerSavingMode = powerSaving["enabled"].as<bool>();
        if (powerSaving["idle-frames"])
            data.idleFrameRate = powerSaving["idle-frames"].as<float>();
    }

    renderer = renderers[static_cast<int>(data.rendererType)];
}

void UImGui::RendererInternal::saveConfig() const noexcept
{
    YAML::Emitter out;
    out << YAML::BeginMap;

    out << YAML::Key << "renderer" << YAML::Value << RENDERER_TYPE_STRINGS[data.rendererType];
    out << YAML::Key << "v-sync" << YAML::Value << data.bUsingVSync;
    out << YAML::Key << "msaa-samples" << YAML::Value << data.msaaSamples;
    out << YAML::Key << "power-saving" << YAML::Value << YAML::BeginMap;
    out << YAML::Key << "enabled" << YAML::Value << data.bEnablePowerSavingMode;
    out << YAML::Key << "idle-frames" << YAML::Value << data.idleFrameRate;
    out << YAML::EndMap;

    std::ofstream fout((Instance::get()->initInfo.configDir + "Core/Renderer.yaml").c_str());
    fout << out.c_str();
    fout.close();
}
