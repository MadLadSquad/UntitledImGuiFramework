#include "Renderer.hpp"
#ifdef __EMSCRIPTEN__
    #include <emscripten.h>
#endif
#include <yaml-cpp/yaml.h>
#include <Core/Components/Instance.hpp>
#include <Renderer/ImGui/ImGui.hpp>
#include <GLFW/glfw3.h>
#include <Interfaces/WindowInterface.hpp>
#include <Global.hpp>

#include <Platform/WASM.hpp>

void UImGui::RendererInternal::start()
{
    loadConfig();

    auto& global = Global::get();

    // Normally we would just use the Renderer::get but since we assign a pointer here we need to avoid the SEGFAULT and
    // other madness the normal solution entails
    global.renderer = this;
    global.init();

#ifdef __EMSCRIPTEN__
    renderer = data.bVulkan ? CAST(decltype(renderer), &wgpu) : CAST(decltype(renderer), &opengl);
#else
    renderer = data.bVulkan ? CAST(decltype(renderer), &vulkan) : CAST(decltype(renderer), &opengl);
#endif
    renderer->init(*this);

    global.modulesManagerr.init(global.instance->initInfo.configDir);
    GUIRenderer::init(Window::get().windowData.layoutLocation, renderer);

#ifdef __EMSCRIPTEN__
    emscripten_set_main_loop_arg(tick, this, 0, true);
#else
    while (!glfwWindowShouldClose(Window::get().windowMain))
        tick(this);
#endif
}

void UImGui::RendererInternal::stop() const noexcept
{
    GUIRenderer::shutdown(Window::get().windowData.layoutLocation, renderer);
    renderer->destroy();
    Global::get().modulesManagerr.destroy();
    Window::get().destroyWindow();
}

void UImGui::RendererInternal::tick(void* rendererInstance) noexcept
{
    auto& inst = *(static_cast<RendererInternal*>(rendererInstance));
    static double deltaTime = 0.0f;
    glfwPollEvents();

    const double now = glfwGetTime();
    deltaTime = now - inst.lastTime;
    inst.lastTime = now;

    // Updates the state of the keybindings
    Global::get().window.updateKeyState();

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

    if (node["vulkan"])
        data.bVulkan = node["vulkan"].as<bool>() &&
#ifdef __EMSCRIPTEN__
            em_supports_wgpu();
#else
            true;
#endif
    if (node["v-sync"])
        data.bUsingVSync = node["v-sync"].as<bool>();
    if (node["msaa-samples"])
        data.msaaSamples = node["msaa-samples"].as<uint32_t>();
    if (node["sample-rate-shading"])
        data.bSampleRateShading = node["sample-rate-shading"].as<bool>();
    if (node["sample-rate-shading-mult"])
        data.sampleRateShadingMult = node["sample-rate-shading-mult"].as<float>();
}

void UImGui::RendererInternal::saveConfig() const noexcept
{
    YAML::Emitter out;
    out << YAML::BeginMap;

    out << YAML::Key << "vulkan" << YAML::Value << data.bVulkan;
    out << YAML::Key << "v-sync" << YAML::Value << data.bUsingVSync;
    out << YAML::Key << "msaa-samples" << YAML::Value << data.msaaSamples;
    out << YAML::Key << "sample-rate-shading" << YAML::Value << data.bSampleRateShading;
    out << YAML::Key << "sample-rate-shading-mult" << YAML::Value << data.sampleRateShadingMult;

    std::ofstream fout(Instance::get()->initInfo.configDir + "Core/Renderer.yaml");
    fout << out.c_str();
    fout.close();
}
