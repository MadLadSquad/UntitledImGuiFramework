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

void UImGui::OpenGLRenderer::ImGuiNewFrame() noexcept
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

void UImGui::OpenGLRenderer::loadTexture(const intptr_t id, const uint32_t x, const uint32_t y, const uint32_t depth, const void* data) noexcept
{
    glGenTextures(1, reinterpret_cast<GLuint*>(id));
    glBindTexture(GL_TEXTURE_2D, *reinterpret_cast<GLuint*>(id));

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    uint32_t dataType = GL_UNSIGNED_BYTE;
    if (depth > 8)
        dataType = GL_UNSIGNED_SHORT;

#if defined(GL_UNPACK_ROW_LENGTH) && !defined(__EMSCRIPTEN__)
    glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
#endif
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, static_cast<int>(x), static_cast<int>(y), 0, GL_RGBA, dataType, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, 0);
}

void UImGui::OpenGLRenderer::loadTextureImGui(const intptr_t id, const uint32_t x, const uint32_t y, const uint32_t depth, const void* data) noexcept
{
    glGenTextures(1, reinterpret_cast<GLuint*>(id));
    glBindTexture(GL_TEXTURE_2D, *reinterpret_cast<GLuint*>(id));

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

#if defined(GL_UNPACK_ROW_LENGTH) && !defined(__EMSCRIPTEN__)
    glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
#endif
    uint32_t dataType = GL_UNSIGNED_BYTE;
    if (depth > 8)
        dataType = GL_UNSIGNED_SHORT;

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, static_cast<int>(x), static_cast<int>(y), 0, GL_RGBA, dataType, data);
}

void UImGui::OpenGLRenderer::useTexture(const intptr_t id) noexcept
{
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, *reinterpret_cast<GLuint*>(id));
}

void UImGui::OpenGLRenderer::clearTexture(const intptr_t id) noexcept
{
    glDeleteTextures(1, reinterpret_cast<GLuint*>(id));
}
