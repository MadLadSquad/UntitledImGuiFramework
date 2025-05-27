#include "CRendererUtils.h"
#include <Renderer/RendererUtils.hpp>

void UImGui_RendererUtils_setupManually()
{
    UImGui::RendererUtils::setupManually();
}

void UImGui_RendererUtils_setOpenGLHints(const int majorVersion, const int minorVersion, const UImGui_RendererClientAPI clientApi, const UImGui_OpenGLProfile profile, const bool bForwardCompatible)
{
    UImGui::RendererUtils::OpenGL::setHints(majorVersion, minorVersion, clientApi, profile, bForwardCompatible);
}

void UImGui_RendererUtils_swapOpenGLFramebuffer()
{
    UImGui::RendererUtils::OpenGL::swapFramebuffer();
}

bool UImGui_RendererUtils_WebGPU_supported()
{
    return UImGui::RendererUtils::WebGPU::supported();
}