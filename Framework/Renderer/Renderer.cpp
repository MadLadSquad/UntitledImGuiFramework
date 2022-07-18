#include "Renderer.hpp"
#include <yaml.h>
#include <Core/Components/Instance.hpp>
#include <Renderer/ImGui/ImGui.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

void UImGui::RendererInternal::start() noexcept
{
    internalGlobal.renderer = this;
    internalGlobal.window.createWindow();
    GUIRenderer::init(internalGlobal.window.windowMain, "../Config/DefaultLayout.ini");

    double lastTime = 0.0f;
    while (!glfwWindowShouldClose(internalGlobal.window.windowMain))
    {
        static double deltaTime = 0.0f;
        glfwPollEvents();

        double now = glfwGetTime();
        deltaTime = now - lastTime;
        lastTime = now;

        auto& colours = ImGui::GetStyle().Colors[ImGuiCol_WindowBg];
        glClearColor(colours.x, colours.y, colours.z, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        GUIRenderer::beginFrame();
        glUseProgram(0);

        GUIRenderer::beginUI(static_cast<float>(deltaTime));
        glfwSwapBuffers(internalGlobal.window.windowMain);
    }
}

void UImGui::RendererInternal::stop() noexcept
{
    GUIRenderer::shutdown();
    internalGlobal.window.destroyWindow();
}

void UImGui::RendererInternal::loadConfig()
{
    YAML::Node node;
    try
    {
        node = YAML::LoadFile("../Config/Core/Renderer.yaml");
    }
    catch (YAML::BadFile&)
    {
        logger.consoleLog("Invalid renderer config file, please fix this error before publishing for production! Because of the missing data we're using the default settings!", UVK_LOG_TYPE_ERROR);
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

    std::ofstream fout("../Config/Settings/Renderer.yaml");
    fout << out.c_str();
    fout.close();
}