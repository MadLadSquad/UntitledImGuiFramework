#include "Renderer.hpp"
#include <yaml-cpp/yaml.h>
#include <Core/Components/Instance.hpp>
#include <Renderer/ImGui/ImGui.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <Interfaces/WindowInterface.hpp>
#include <Interfaces/RendererInterface.hpp>

void UImGui::RendererInternal::start() noexcept
{
    // Normally we would just use the Renderer::get but since we assign a pointer here we need to avoid the SEGFAULT and
    // other madness the normal solution entails
    internalGlobal.renderer = this;
    internalGlobal.init();

    vendorString = (char*)glGetString(GL_VENDOR);
    if (vendorString.starts_with("NVIDIA"))
    {
        driverVersion = (char*)glGetString(GL_VERSION);
        apiVersion = driverVersion;

        driverVersion.erase(0, driverVersion.find("NVIDIA ") + strlen("NVIDIA "));
        apiVersion.erase(apiVersion.find(" NVIDIA"));
    }

    gpuName = (char*)glGetString(GL_RENDERER);

    GUIRenderer::init(Window::get().windowMain, Window::get().windowData.layoutLocation);

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

        auto& colours = ImGui::GetStyle().Colors[ImGuiCol_WindowBg];
        glClearColor(colours.x, colours.y, colours.z, colours.w);
        glClear(GL_COLOR_BUFFER_BIT);

        GUIRenderer::beginFrame();
        glUseProgram(0);

        GUIRenderer::beginUI(static_cast<float>(deltaTime));
        glfwSwapBuffers(Window::get().windowMain);
    }
}

void UImGui::RendererInternal::stop() noexcept
{
    GUIRenderer::shutdown(Window::get().windowData.layoutLocation);
    Window::get().destroyWindow();
}

void UImGui::RendererInternal::loadConfig()
{
    YAML::Node node;
    try
    {
        node = YAML::LoadFile(UIMGUI_CONFIG_DIR"Core/Renderer.yaml");
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

    std::ofstream fout(UIMGUI_CONFIG_DIR"Core/Renderer.yaml");
    fout << out.c_str();
    fout.close();
}