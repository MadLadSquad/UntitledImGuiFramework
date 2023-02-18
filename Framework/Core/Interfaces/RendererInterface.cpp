#include "RendererInterface.hpp"
#include <Global.hpp>

UImGui::RendererData& UImGui::Renderer::data() noexcept
{
    return Renderer::get().data;
}

void UImGui::Renderer::saveSettings() noexcept
{
    Renderer::get().saveConfig();
}

UImGui::RendererInternal& UImGui::Renderer::get() noexcept
{
    return *internalGlobal.renderer;
}
