#include "OpenGLRenderer.hpp"
#include <Renderer.hpp>
#include <ImGui/ImGui.hpp>
#include <Interfaces/WindowInterface.hpp>
#ifndef __APPLE__
    #include <GL/glew.h>
#else
    #include <OpenGL/GL.h>
#endif
#include <GLFW/glfw3.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

void UImGui::OpenGLRenderer::init(RendererInternal& renderer) noexcept
{
    renderer.vendorString = (const char*)glGetString(GL_VENDOR);
    if (renderer.vendorString.starts_with("NVIDIA"))
    {
        renderer.driverVersion = (const char*)glGetString(GL_VERSION);
        renderer.apiVersion = renderer.driverVersion;

        renderer.driverVersion.erase(0, renderer.driverVersion.find("NVIDIA ") + strlen("NVIDIA "));
        renderer.apiVersion.erase(renderer.apiVersion.find(" NVIDIA"));
    }
    renderer.gpuName = (const char*)glGetString(GL_RENDERER);
}

void UImGui::OpenGLRenderer::renderStart(double deltaTime) noexcept
{
    const auto& colours = ImGui::GetStyle().Colors[ImGuiCol_WindowBg];
    glClearColor(colours.x, colours.y, colours.z, colours.w);
    glClear(GL_COLOR_BUFFER_BIT);
}

void UImGui::OpenGLRenderer::renderEnd(double deltaTime) noexcept
{
    glfwSwapBuffers(Window::get().windowMain);
}

void UImGui::OpenGLRenderer::destroy() noexcept
{

}

void UImGui::OpenGLRenderer::ImGuiNewFrame()
{
    ImGui_ImplOpenGL3_NewFrame();
    GUIRenderer::beginFrame();
    glUseProgram(0);
}

void UImGui::OpenGLRenderer::ImGuiShutdown() noexcept
{
    ImGui_ImplOpenGL3_Shutdown();
}

void UImGui::OpenGLRenderer::ImGuiInit() noexcept
{
    ImGui_ImplGlfw_InitForOpenGL(Window::get().data(), true);
#ifdef __APPLE__
    ImGui_ImplOpenGL3_Init("#version 410");
#elif __EMSCRIPTEN__
    ImGui_ImplGlfw_InstallEmscriptenCanvasResizeCallback("canvas");
    ImGui_ImplOpenGL3_Init("#version 100");
#else
    ImGui_ImplOpenGL3_Init("#version 450");
#endif
}

void UImGui::OpenGLRenderer::ImGuiRenderData() noexcept
{
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
