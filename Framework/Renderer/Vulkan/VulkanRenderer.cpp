#include "VulkanRenderer.hpp"
#include <ImGui/ImGui.hpp>

void UImGui::VulkanRenderer::init(RendererInternal& renderer) noexcept
{
#ifndef __EMSCRIPTEN__
    instance.init();
    device.create(renderer);
    draw.init();
#endif
}

void UImGui::VulkanRenderer::renderStart(double deltaTime) noexcept
{

}

void UImGui::VulkanRenderer::renderEnd(double deltaTime) noexcept
{
#ifndef __EMSCRIPTEN__
    draw.ImGuiDraw(ImGui::GetDrawData());
#endif
}

void UImGui::VulkanRenderer::destroy() noexcept
{
#ifndef __EMSCRIPTEN__
    draw.destroy();
    device.destroy();
    instance.destroy();
#endif
}

void UImGui::VulkanRenderer::ImGuiNewFrame() noexcept
{
#ifndef __EMSCRIPTEN__
    ImGui_ImplVulkan_NewFrame();
    GUIRenderer::beginFrame();
#endif
}

void UImGui::VulkanRenderer::ImGuiShutdown() noexcept
{
#ifndef __EMSCRIPTEN__
    device.get().waitIdle();
    ImGui_ImplVulkan_Shutdown();
#endif
}

void UImGui::VulkanRenderer::ImGuiInit() noexcept
{
#ifndef __EMSCRIPTEN__
    draw.ImGuiInit();
#endif
}

void UImGui::VulkanRenderer::ImGuiRenderData() noexcept
{

}

void UImGui::VulkanRenderer::waitOnGPU() noexcept
{
#ifndef __EMSCRPITEN__
    draw.waitOnGPU();
#endif
}
