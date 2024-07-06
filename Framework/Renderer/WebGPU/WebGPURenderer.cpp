#include "WebGPURenderer.hpp"
#ifdef __EMSCRIPTEN__
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_wgpu.h"
#include <emscripten.h>
#include <emscripten/html5.h>
#include <emscripten/html5_webgpu.h>
#include <GLFW/glfw3.h>


void UImGui::WebGPURenderer::init(RendererInternal& renderer) noexcept
{

}

void UImGui::WebGPURenderer::renderStart(double deltaTime) noexcept
{

}

void UImGui::WebGPURenderer::renderEnd(double deltaTime) noexcept
{

}

void UImGui::WebGPURenderer::destroy() noexcept
{

}

void UImGui::WebGPURenderer::ImGuiNewFrame() noexcept
{

}

void UImGui::WebGPURenderer::ImGuiShutdown() noexcept
{

}

void UImGui::WebGPURenderer::ImGuiInit() noexcept
{

}

void UImGui::WebGPURenderer::ImGuiRenderData() noexcept
{

}

void UImGui::WebGPURenderer::loadTexture(intptr_t id, uint32_t x, uint32_t y, uint32_t depth, const void* data) noexcept
{

}

void UImGui::WebGPURenderer::loadTextureImGui(intptr_t id, uint32_t x, uint32_t y, uint32_t depth, const void* data) noexcept
{

}

void UImGui::WebGPURenderer::useTexture(intptr_t id) noexcept
{

}

void UImGui::WebGPURenderer::clearTexture(intptr_t id) noexcept
{

}

#else
void UImGui::WebGPURenderer::init(RendererInternal& renderer) noexcept {}
void UImGui::WebGPURenderer::renderStart(double deltaTime) noexcept {}
void UImGui::WebGPURenderer::renderEnd(double deltaTime) noexcept {}
void UImGui::WebGPURenderer::destroy() noexcept {}

void UImGui::WebGPURenderer::ImGuiNewFrame() noexcept {}
void UImGui::WebGPURenderer::ImGuiShutdown() noexcept {}
void UImGui::WebGPURenderer::ImGuiInit() noexcept {}
void UImGui::WebGPURenderer::ImGuiRenderData() noexcept {}

void UImGui::WebGPURenderer::loadTexture(intptr_t id, uint32_t x, uint32_t y, uint32_t depth, const void* data) noexcept {}
void UImGui::WebGPURenderer::loadTextureImGui(intptr_t id, uint32_t x, uint32_t y, uint32_t depth, const void* data) noexcept {}
void UImGui::WebGPURenderer::useTexture(intptr_t id) noexcept {}
void UImGui::WebGPURenderer::clearTexture(intptr_t id) noexcept {}
#endif