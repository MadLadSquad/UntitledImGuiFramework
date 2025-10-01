#include "RendererUtils.hpp"
#include <Interfaces/WindowInterface.hpp>
#include <Core/Platform/WASM.hpp>
#include <ImGui/ImGui.hpp>
#include <Interfaces/RendererInterface.hpp>
#include <imgui_impl_opengl3.h>

UImGui::GenericRenderer* UImGui::RendererUtils::getRenderer() noexcept
{
    return Renderer::get().renderer;
}

void UImGui::RendererUtils::setupManually() noexcept
{
    Window::get()->setupManualRenderingHints();
}

void UImGui::RendererUtils::OpenGL::setHints(const int majorVersion, const int minorVersion, const RendererClientAPI clientApi, const Profile profile, const bool bForwardCompatible, const uint32_t samples) noexcept
{
    Window::get()->OpenGL_setHints(majorVersion, minorVersion, clientApi, profile, bForwardCompatible, samples);
}

void UImGui::RendererUtils::OpenGL::swapFramebuffers() noexcept
{
    Window::get()->OpenGL_swapBuffers();
}

UImGui::RendererUtils::OpenGL::Context* UImGui::RendererUtils::OpenGL::createContext() noexcept
{
    return Window::get()->OpenGL_createContext();
}

void UImGui::RendererUtils::OpenGL::setCurrentContext(Context* ctx) noexcept
{
    Window::get()->OpenGL_setCurrentContext(ctx);
}

void UImGui::RendererUtils::OpenGL::destroyContext(Context* ctx) noexcept
{
    Window::get()->OpenGL_destroyContext(ctx);
}

UImGui::RendererUtils::OpenGL::Context* UImGui::RendererUtils::OpenGL::getCurrentContext() noexcept
{
    return Window::get()->OpenGL_getCurrentContext();
}

void UImGui::RendererUtils::OpenGL::setSwapInterval(const int interval) noexcept
{
    Window::get()->OpenGL_setSwapInterval(interval);
}

void UImGui::RendererUtils::OpenGL::ImGuiInit(const String glslVersion) noexcept
{
    Window::get()->ImGuiInitFor_OpenGL();
    ImGuiInstallCallbacks();
    ImGui_ImplOpenGL3_Init(glslVersion);
}

UImGui::RendererUtils::OpenGL::GetProcAddressFun UImGui::RendererUtils::OpenGL::getProcAddressFunction() noexcept
{
    return Window::get()->OpenGL_getProcAddressFunction();
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

void UImGui::RendererUtils::ImGuiInitOther() noexcept
{
    Window::get()->ImGuiInitFor_Other();
}

void UImGui::RendererUtils::ImGuiInstallCallbacks() noexcept
{
    Window::get()->ImGuiInstallCallbacks();
}

#ifndef __EMSCRIPTEN__
void UImGui::RendererUtils::Vulkan::ImGuiInit(ImGui_ImplVulkan_InitInfo& initInfo) noexcept
{
    Window::get()->ImGuiInitFor_Vulkan();
    ImGui_ImplVulkan_Init(&initInfo);
}

VkResult UImGui::RendererUtils::Vulkan::createWindowSurface(const VkInstance instance, const VkAllocationCallbacks* allocator, VkSurfaceKHR* surface) noexcept
{
    return Window::get()->Vulkan_createWindowSurface(instance, allocator, surface);
}

void UImGui::RendererUtils::Vulkan::fillInstanceAndLayerExtensions(TVector<const char*>& instanceExtensions, TVector<const char*>& instanceLayers) noexcept
{
    Window::get()->Vulkan_fillInstanceAndLayerExtensions(instanceExtensions, instanceLayers);
}
#endif