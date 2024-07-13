#include "VulkanRenderer.hpp"

void UImGui::VulkanRenderer::init(RendererInternal& renderer) noexcept
{
#ifndef __EMSCRIPTEN__
    instance.init();
    device.create();
#endif
}

void UImGui::VulkanRenderer::renderStart(double deltaTime) noexcept
{

}

void UImGui::VulkanRenderer::renderEnd(double deltaTime) noexcept
{

}

void UImGui::VulkanRenderer::destroy() noexcept
{
#ifndef __EMSCRIPTEN__
    device.destroy();
    instance.destroy();
#endif
}

void UImGui::VulkanRenderer::ImGuiNewFrame() noexcept
{

}

void UImGui::VulkanRenderer::ImGuiShutdown() noexcept
{

}

void UImGui::VulkanRenderer::ImGuiInit() noexcept
{

}

void UImGui::VulkanRenderer::ImGuiRenderData() noexcept
{

}
