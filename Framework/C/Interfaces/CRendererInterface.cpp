#include "CRendererInterface.h"
#include "Interfaces/RendererInterface.hpp"

UImGui_RendererData* UImGui_Renderer_data()
{
    return &UImGui::Renderer::data();
}

void UImGui_Renderer_saveSettings()
{
    UImGui::Renderer::saveSettings();
}

UImGui_String UImGui_Renderer_getVendorString()
{
    return UImGui::Renderer::getVendorString().c_str();
}

UImGui_String UImGui_Renderer_getAPIVersion()
{
    return UImGui::Renderer::getAPIVersion().c_str();
}

UImGui_String UImGui_Renderer_getGPUName()
{
    return UImGui::Renderer::getGPUName().c_str();
}

UImGui_String UImGui_Renderer_getDriverVersion()
{
    return UImGui::Renderer::getDriverVersion().c_str();
}