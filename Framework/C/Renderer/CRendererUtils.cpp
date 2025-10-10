#include "CRendererUtils.h"
#include <Renderer/RendererUtils.hpp>

void UImGui_RendererUtils_setupManually()
{
    UImGui::RendererUtils::setupManually();
}

void UImGui_RendererUtils_OpenGL_setHints(const int majorVersion, const int minorVersion, const UImGui_RendererClientAPI clientApi, const UImGui_OpenGLProfile profile, const bool bForwardCompatible, uint32_t samples)
{
    UImGui::RendererUtils::OpenGL::setHints(majorVersion, minorVersion, clientApi, profile, bForwardCompatible, samples);
}

void UImGui_RendererUtils_OpenGL_swapFramebuffers()
{
    UImGui::RendererUtils::OpenGL::swapFramebuffers();
}

UImGui_OpenGLContext* UImGui_RendererUtils_OpenGL_createContext()
{
    return UImGui::RendererUtils::OpenGL::createContext();
}

void UImGui_RendererUtils_OpenGL_setCurrentContext(UImGui_OpenGLContext* ctx)
{
    UImGui::RendererUtils::OpenGL::setCurrentContext(ctx);
}

void UImGui_RendererUtils_OpenGL_destroyContext(UImGui_OpenGLContext* ctx)
{
    UImGui::RendererUtils::OpenGL::destroyContext(ctx);
}

UImGui_OpenGLContext* UImGui_RendererUtils_OpenGL_getCurrentContext()
{
    return UImGui::RendererUtils::OpenGL::getCurrentContext();
}

void UImGui_RendererUtils_OpenGL_setSwapInterval(const int interval)
{
    UImGui::RendererUtils::OpenGL::setSwapInterval(interval);
}

bool UImGui_RendererUtils_WebGPU_supported()
{
    return UImGui::RendererUtils::WebGPU::supported();
}

void UImGui_RendererUtils_beginImGuiFrame()
{
    UImGui::RendererUtils::beginImGuiFrame();
}

void UImGui_RendererUtils_ImGuiInstallCallbacks()
{
    UImGui::RendererUtils::ImGuiInstallCallbacks();
}

UImGui_OpenGL_GetProcAddressFun UImGui_RendererUtils_OpenGL_getProcAddressFunction()
{
    return UImGui::RendererUtils::OpenGL::getProcAddressFunction();
}

void UImGui_RendererUtils_OpenGL_ImGuiInit(const UImGui_String glslVersion)
{
    UImGui::RendererUtils::OpenGL::ImGuiInit(glslVersion);
}

void UImGui_RendererUtils_ImGuiInitOther()
{
    UImGui::RendererUtils::ImGuiInitOther();
}

UImGui_CGenericRenderer* UImGui_RendererUtils_getRenderer()
{
    return UImGui::RendererUtils::getRenderer();
}

#ifndef __EMSCRIPTEN__
void UImGui_RendererUtils_Vulkan_ImGuiInit(void* initInfo)
{
    UImGui::RendererUtils::Vulkan::ImGuiInit(*static_cast<ImGui_ImplVulkan_InitInfo*>(initInfo));
}

VkResult UImGui_RendererUtils_Vulkan_createWindowSurface(VkInstance instance, const VkAllocationCallbacks* allocator, VkSurfaceKHR* surface)
{
    return UImGui::RendererUtils::Vulkan::createWindowSurface(instance, allocator, surface);
}

void UImGui_RendererUtils_Vulkan_fillInstanceAndLayerExtensions(const char*** instanceExtensions, size_t* instanceExtensionsSize, const char*** instanceLayers, size_t* instanceLayersSize)
{
    UImGui::TVector<const char*> extensions;
    UImGui::TVector<const char*> layers;

    UImGui::RendererUtils::Vulkan::fillInstanceAndLayerExtensions(extensions, layers);

    *instanceExtensionsSize = extensions.size();
    *instanceLayersSize = layers.size();

    *instanceExtensions = static_cast<const char**>(UImGui_Allocator_allocate(sizeof(const char*) * *instanceExtensionsSize));
    *instanceLayers = static_cast<const char**>(UImGui_Allocator_allocate(sizeof(const char*) * *instanceLayersSize));

    // Shallow copy because the strings are basically guaranteed to be static data
    memcpy(*instanceExtensions, extensions.data(), extensions.size() * sizeof(const char*));
    memcpy(*instanceLayers, layers.data(), layers.size() * sizeof(const char*));
}
#endif
