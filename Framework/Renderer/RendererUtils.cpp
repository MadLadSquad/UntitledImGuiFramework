#include "RendererUtils.hpp"
#include <Interfaces/WindowInterface.hpp>
#include <GLFW/glfw3.h>
#include <Core/Platform/WASM.hpp>
#include <ImGui/ImGui.hpp>
#include <Renderer/GenericRenderer/GenericRenderer.hpp>
#include <Interfaces/RendererInterface.hpp>

UImGui::GenericRenderer* UImGui::RendererUtils::getRenderer() noexcept
{
    return Renderer::get().renderer;
}

void UImGui::RendererUtils::setupManually() noexcept
{
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
}

void UImGui::RendererUtils::OpenGL::setHints(const int majorVersion, const int minorVersion, const RendererClientAPI clientApi, const Profile profile, const bool bForwardCompatible) noexcept
{
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, majorVersion);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minorVersion);
    glfwWindowHint(GLFW_CLIENT_API, CAST(int, clientApi));
    glfwWindowHint(GLFW_OPENGL_PROFILE, CAST(int, profile));
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, CAST(int, bForwardCompatible));
}

void UImGui::RendererUtils::OpenGL::swapFramebuffers() noexcept
{
    glfwSwapBuffers(Window::getInternal());
}

UImGui::RendererUtils::OpenGL::Context* UImGui::RendererUtils::OpenGL::createContext() noexcept
{
    // TODO: SDL
    return nullptr;
}

void UImGui::RendererUtils::OpenGL::setCurrentContext(Context* ctx) noexcept
{
    UNUSED(ctx);
    glfwMakeContextCurrent(Window::getInternal());
}

void UImGui::RendererUtils::OpenGL::destroyContext(UImGui::RendererUtils::OpenGL::Context* ctx) noexcept
{
    // TODO: SDL
    UNUSED(ctx);
}

UImGui::RendererUtils::OpenGL::Context* UImGui::RendererUtils::OpenGL::getCurrentContext() noexcept
{
    return glfwGetCurrentContext();
}

void UImGui::RendererUtils::OpenGL::setSwapInterval(const int interval) noexcept
{
    glfwSwapInterval(interval);
}

bool UImGui::RendererUtils::WebGPU::supported() noexcept
{
#ifdef __EMSCRIPTEN__
    return em_supports_wgpu();
#else
    return false;
#endif
}

void UImGui::RendererUtils::beginImGuiFrame() noexcept
{
    GUIRenderer::beginFrame();
}