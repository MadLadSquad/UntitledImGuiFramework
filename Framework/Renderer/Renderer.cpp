#include "Renderer.hpp"
#include <yaml-cpp/yaml.h>
#include <Core/Components/Instance.hpp>
#include <Renderer/ImGui/ImGui.hpp>
#include <GLFW/glfw3.h>
#include <Interfaces/WindowInterface.hpp>
#include <Interfaces/RendererInterface.hpp>

void UImGui::RendererInternal::start() noexcept
{
    loadConfig();

    // Normally we would just use the Renderer::get but since we assign a pointer here we need to avoid the SEGFAULT and
    // other madness the normal solution entails
    internalGlobal.renderer = this;
    internalGlobal.init();

    renderer = data.bVulkan ? (decltype(renderer))&vulkan : (decltype(renderer))&opengl;
    renderer->init(*this);

    UImGui::internalGlobal.modulesManagerr.init(UImGui::internalGlobal.instance->initInfo.configDir);
    if (!data.bVulkan) // TODO: Remove this when the renderer is done
        GUIRenderer::init(Window::get().windowData.layoutLocation, renderer);

    double lastTime = 0.0f;
    while (!glfwWindowShouldClose(Window::get().windowMain))
    {
        static double deltaTime = 0.0f;
        glfwPollEvents();

        double now = glfwGetTime();
        deltaTime = now - lastTime;
        lastTime = now;

        // Updates the state of the keybindings
        internalGlobal.window.updateKeyState();

        renderer->renderStart(deltaTime);
        if (!data.bVulkan) // TODO: Remove this when the renderer is done
            GUIRenderer::beginUI(static_cast<float>(deltaTime), renderer);
        renderer->renderEnd(deltaTime);
    }
}

void UImGui::RendererInternal::stop() noexcept
{
    if (!data.bVulkan) // TODO: Remove this when the renderer is done
        GUIRenderer::shutdown(Window::get().windowData.layoutLocation, renderer);
    renderer->destroy();
    UImGui::internalGlobal.modulesManagerr.destroy();
    Window::get().destroyWindow();
}

void UImGui::RendererInternal::loadConfig()
{
    YAML::Node node;
    try
    {
        node = YAML::LoadFile(UImGui::internalGlobal.instance->initInfo.configDir + "Core/Renderer.yaml");
    }
    catch (YAML::BadFile&)
    {
        Logger::log("Invalid renderer config file, please fix this error before publishing for production! Because of the missing data we're using the default settings!", UVK_LOG_TYPE_ERROR);
        return;
    }

    if (node["vulkan"])
        data.bVulkan = node["vulkan"].as<bool>();
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

    std::ofstream fout(UImGui::internalGlobal.instance->initInfo.configDir + "Core/Renderer.yaml");
    fout << out.c_str();
    fout.close();
}
