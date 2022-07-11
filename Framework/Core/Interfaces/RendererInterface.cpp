#include "RendererInterface.hpp"
#include <Global.hpp>

UImGui::RendererData& UImGui::Renderer::data() noexcept
{
    return internalGlobal.renderer->data;
}

void UImGui::Renderer::saveSettings() noexcept
{
    internalGlobal.renderer->saveConfig();
}
