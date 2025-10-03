#include "CRendererUtils.h"
#include <Renderer/RendererUtils.hpp>

void UImGui_RendererUtils_setupManually()
{
    UImGui::RendererUtils::setupManually();
}

void UImGui_RendererUtils_OpenGL_setHints(const int majorVersion, const int minorVersion, const UImGui_RendererClientAPI clientApi, const UImGui_OpenGLProfile profile, const bool bForwardCompatible)
{
    UImGui::RendererUtils::OpenGL::setHints(majorVersion, minorVersion, clientApi, profile, bForwardCompatible);
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
