#include "RendererInterface.hpp"
#include <Global.hpp>

UImGui::RendererData& UImGui::Renderer::data() noexcept
{
    return get().data;
}

void UImGui::Renderer::saveSettings() noexcept
{
    get().saveConfig();
}

UImGui::RendererInternal& UImGui::Renderer::get() noexcept
{
    return *Global::get().renderer;
}

const UImGui::FString& UImGui::Renderer::getVendorString() noexcept
{
    return get().vendorString;
}

const UImGui::FString& UImGui::Renderer::getAPIVersion() noexcept
{
    return get().apiVersion;
}

const UImGui::FString& UImGui::Renderer::getGPUName() noexcept
{
    return get().gpuName;
}

const UImGui::FString& UImGui::Renderer::getDriverVersion() noexcept
{
    return get().driverVersion;
}

void UImGui::Renderer::forceUpdate() noexcept
{
    get().bIdling = false;
}
