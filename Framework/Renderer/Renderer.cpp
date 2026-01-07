#include "Renderer.hpp"
#ifdef __EMSCRIPTEN__
    #include <emscripten.h>
    #include <imgui_internal.h>
#endif
#include <ryml.hpp>
#include <Core/Components/Instance.hpp>
#include <ImGui/ImGui.hpp>
#include <Window/WindowUtils.hpp>
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
    // Doing this first because a lot of internal code reuses interface functions so the earlier, the better
    auto& global = Global::get();
    global.renderer = this;

    loadConfig();

    // The window gets created after getting the renderer settings but before starting the renderer, because depending
    // on the API we need to configure our renderer with different properties
    if (global.instance->initInfo.customWindow != nullptr)
        global.window.window = global.instance->initInfo.customWindow;
    else if (global.instance->initInfo.cInitInfo != nullptr && global.instance->initInfo.cInitInfo->customWindow != nullptr)
        global.window.window = static_cast<GenericWindow*>(global.instance->initInfo.cInitInfo->customWindow);

    Window::get()->createWindow();
    renderer->init(metadata);

    global.modulesManager.init(global.instance->initInfo.configDir);
    GUIRenderer::init(renderer);

    // The need to conform to the JS event loop is the main reason the stop method is separate from start
#ifdef __EMSCRIPTEN__
    emscripten_set_main_loop_arg(tick, this, 0, true);
#else
    while (!WindowUtils::shouldRender())
        tick(this);
#endif
}

void UImGui::RendererInternal::stop() const noexcept
{
    GUIRenderer::shutdown(renderer);
    renderer->destroy();
    Modules::get().destroy();
    Window::get()->destroyWindow();
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

        WindowUtils::waitEventsTimeout(waitTimeout);

        timer.stop();
        const double elapsed = timer.get();
        const double duration = elapsed - waitTimeout;
        const double idleExpected = 1.0 / inst.data.idleFrameRate;

        inst.bIdling = duration > (idleExpected * 0.9);
    }
#endif

    double now = 0.0;
    WindowUtils::pollEvents(now, deltaTime, inst.lastTime);

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
        WindowUtils::waitEventsTimeout(1.0f);

    inst.renderer->renderStart(deltaTime);
    GUIRenderer::beginUI(static_cast<float>(deltaTime), inst.renderer);
    inst.renderer->renderEnd(deltaTime);
}

void UImGui::RendererInternal::loadConfig() noexcept
{
    auto& initInfo = Instance::get()->initInfo;
    const auto file = Utility::loadFileToString(initInfo.configDir + "Core/Renderer.yaml");
    if (file.empty())
    {
        Logger::log("Couldn't load the renderer config file, please fix this error before publishing for production! Reverting to the default settings!", ULOG_LOG_TYPE_ERROR);
        return;
    }

    auto tree = ryml::parse_in_arena(file.c_str());
    if (tree.empty())
    {
        Logger::log("Invalid renderer config file, please fix this error before publishing for production! Reverting to the default settings!", ULOG_LOG_TYPE_ERROR);
        return;
    }

    const auto node = tree.rootref();

    {
        auto rendererConf = node["renderer"];
        if (keyValid(rendererConf))
        {
            FString tmp;
            rendererConf >> tmp;
            Utility::toLower(tmp);

            for (int i = 0; i < UIMGUI_RENDERER_TYPE_COUNT; i++)
            {
                for (int j = 0; j < UIMGUI_RENDERER_TYPE_ALT_NAMES_COUNT; j++)
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
            data.rendererType = data.rendererType == UIMGUI_RENDERER_TYPE_VULKAN_WEBGPU ? UIMGUI_RENDERER_TYPE_OPENGL : data.rendererType;
#endif
            data.textureRendererType = data.rendererType;

            if (data.rendererType == UIMGUI_RENDERER_TYPE_CUSTOM)
            {
                if (initInfo.customRenderer != nullptr)
                    custom = initInfo.customRenderer;
                else if (initInfo.cInitInfo != nullptr && initInfo.cInitInfo->customRenderer != nullptr)
                    custom = static_cast<GenericRenderer*>(initInfo.cInitInfo->customRenderer);
                else
                {
                    Logger::log("Renderer set to \"custom\" but an invalid custom renderer was provided.\n"
                        "Make sure to provide one in the init info struct of your instance in the constructor of the instance!", ULOG_LOG_TYPE_ERROR);
                    Logger::log("Switching to the OpenGL renderer.", ULOG_LOG_TYPE_NOTE);

                    custom = nullptr;
                    data.rendererType = UIMGUI_RENDERER_TYPE_OPENGL;
                }
                renderers[UIMGUI_RENDERER_TYPE_CUSTOM] = custom;
            }
        }
    }

    {
        auto vsync = node["v-sync"];
        if (keyValid(vsync))
            vsync >> data.bUsingVSync;
    }

    {
        auto msaa = node["msaa-samples"];
        if (keyValid(msaa))
            msaa >> data.msaaSamples;
    }

    {
        auto powerSaving = node["power-saving"];
        if (keyValid(powerSaving))
        {
            auto enabled = powerSaving["enabled"];
            if (keyValid(enabled))
                enabled >> data.bEnablePowerSavingMode;

            auto idleFrames = node["idle-frames"];
            if (keyValid(idleFrames))
                idleFrames >> data.idleFrameRate;
        }
    }

    {
        auto emscripten = node["emscripten"];
        if (keyValid(emscripten))
        {
            auto canvasSelector = emscripten["canvas-selector"];
            if (keyValid(canvasSelector))
            {
                // Doing this because the RendererData structure is in C and we use String there
                FString tmpCanvasSelector;
                canvasSelector >> tmpCanvasSelector;
                data.emscriptenCanvas = tmpCanvasSelector.c_str();
            }
        }
    }

    renderer = CAST(decltype(renderer), renderers[static_cast<int>(data.rendererType)]);

    {
        auto customRenderer = node["custom-renderer"];
        if (keyValid(customRenderer))
            renderer->parseCustomConfig(customRenderer);
    }
}

void UImGui::RendererInternal::saveConfig() const noexcept
{
    ryml::Tree tree;

    ryml::NodeRef root = tree.rootref();
    root |= ryml::MAP;

    root["renderer"] << RENDERER_TYPE_STRINGS[data.rendererType][0];
    root["v-sync"] << data.bUsingVSync;
    root["msaa-samples"] << data.msaaSamples;

    auto powerSaving = root["power-saving"];
    powerSaving |= ryml::MAP;
    powerSaving["enabled"] << data.bEnablePowerSavingMode;
    powerSaving["idle-frames"] << data.idleFrameRate;

    auto emscripten = root["emscripten"];
    emscripten |= ryml::MAP;
    emscripten["canvas-selector"] = data.emscriptenCanvas;

    auto customConfig = root["custom-renderer"];
    if (keyValid(customConfig))
        renderer->saveCustomConfig(customConfig);

    std::ofstream fout((Instance::get()->initInfo.configDir + "Core/Renderer.yaml").c_str());
    fout << tree;
    fout.close();
}
