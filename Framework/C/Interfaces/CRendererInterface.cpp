#include "CRendererInterface.h"
#include "Interfaces/RendererInterface.hpp"
#include "Renderer/GenericRenderer/GenericRenderer.hpp"
#include "Global.hpp"

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

void UImGui_RendererInternalMetadata_setVendorString(const UImGui_String str)
{
    UImGui::Global::get().renderer->metadata.vendorString = str;
}

void UImGui_RendererInternalMetadata_setApiVersion(const UImGui_String str)
{
    UImGui::Global::get().renderer->metadata.apiVersion = str;

}

void UImGui_RendererInternalMetadata_setDriverVersion(const UImGui_String str)
{
    UImGui::Global::get().renderer->metadata.driverVersion = str;

}

void UImGui_RendererInternalMetadata_setGPUName(const UImGui_String str)
{
    UImGui::Global::get().renderer->metadata.gpuName = str;
}
