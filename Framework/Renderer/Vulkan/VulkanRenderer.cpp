#include "VulkanRenderer.hpp"

void UImGui::VulkanRenderer::init(UImGui::RendererInternal& renderer) noexcept
{
#ifndef __EMSCRIPTEN__
    instance.init();
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

void UImGui::VulkanRenderer::loadTexture(const intptr_t id, const uint32_t x, const uint32_t y, const uint32_t depth, const void* data) noexcept
{

}

void UImGui::VulkanRenderer::loadTextureImGui(const intptr_t id, const uint32_t x, const uint32_t y, const uint32_t depth, const void* data) noexcept
{

}

void UImGui::VulkanRenderer::useTexture(intptr_t id) noexcept
{

}

void UImGui::VulkanRenderer::clearTexture(intptr_t id) noexcept
{

}
