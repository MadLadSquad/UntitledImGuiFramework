#include "WebGPURenderer.hpp"
#ifdef __EMSCRIPTEN__
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_wgpu.h"
#include <emscripten.h>
#include <emscripten/html5.h>
#include <emscripten/html5_webgpu.h>
#include <GLFW/glfw3.h>

#include <Components/Instance.hpp>
#include <Interfaces/WindowInterface.hpp>
#include <Interfaces/RendererInterface.hpp>
#include <ImGui/ImGui.hpp>

static void errorCallback(WGPUErrorType errorType, const char* message, void*)
{
    const char* errorTypeString;
    switch (errorType)
    {
        case WGPUErrorType_Validation:
            errorTypeString = "Validation";
            break;
        case WGPUErrorType_OutOfMemory:
            errorTypeString = "Out of memory";
            break;
        case WGPUErrorType_DeviceLost:
            errorTypeString = "Device lost";
            break;
        default:
            errorTypeString = "Unknown";
            break;
    }
    Logger::log("WebGPU ", ULOG_LOG_TYPE_ERROR, errorTypeString, ": ", message);
}

void UImGui::WebGPURenderer::createSwapchain() noexcept
{
    if (swapchain)
        wgpuSwapChainRelease(swapchain);
    swapchainWidth = static_cast<uint32_t>(Window::windowSize().x);
    swapchainHeight = static_cast<uint32_t>(Window::windowSize().y);

    const WGPUSwapChainDescriptor swapchainDescriptor =
    {
        .usage = WGPUTextureUsage_RenderAttachment,
        .format = preferredFormat,
        .width = swapchainWidth,
        .height = swapchainHeight,
        .presentMode = WGPUPresentMode_Fifo, // TODO: Add V-Sync handling when WebGPU allows us to do that
    };

    swapchain = wgpuDeviceCreateSwapChain(device, surface, &swapchainDescriptor);
}

// TODO: Implement setting the renderer metadata structure when WebGPU allows for it
void UImGui::WebGPURenderer::init(RendererInternalMetadata&) noexcept
{
    wgpu::Instance inst = wgpuCreateInstance(nullptr);
    device = emscripten_webgpu_get_device();
    if (!device)
    {
        UImGui::Instance::shutdown();
        return;
    }

    wgpu::SurfaceDescriptorFromCanvasHTMLSelector HTMLSurfaceDescriptor{};
    HTMLSurfaceDescriptor.selector = "#canvas";

    const wgpu::SurfaceDescriptor surfaceDescriptor = { .nextInChain = &HTMLSurfaceDescriptor };
    wgpu::Surface lsurface = inst.CreateSurface(&surfaceDescriptor);

    const wgpu::Adapter adapter = {};
    preferredFormat = (WGPUTextureFormat)lsurface.GetPreferredFormat(adapter);

    instance = inst.MoveToCHandle();
    surface = lsurface.MoveToCHandle();

    wgpuDeviceSetUncapturedErrorCallback(device, errorCallback, nullptr);
    createSwapchain();

    Logger::log("Created the WebGPU renderer!", ULOG_LOG_TYPE_SUCCESS);
}

void UImGui::WebGPURenderer::renderStart(double deltaTime) noexcept
{
    if (swapchainWidth != Window::windowSize().x || swapchainHeight != Window::windowSize().y)
    {
        ImGui_ImplWGPU_InvalidateDeviceObjects();
        createSwapchain();
        ImGui_ImplWGPU_CreateDeviceObjects();
    }
}

void UImGui::WebGPURenderer::renderEnd(double deltaTime) noexcept
{
    const auto& colours = ImGui::GetStyle().Colors[ImGuiCol_WindowBg];

    if (multisampledTexture == nullptr || multisampledTextureWidth != swapchainWidth || multisampledTextureHeight != swapchainHeight)
    {
        if (multisampledTexture != nullptr)
        {
            wgpuTextureViewRelease(multisampledTextureView);
            wgpuTextureDestroy(multisampledTexture);
            wgpuTextureRelease(multisampledTexture);
        }

        multisampledTextureWidth = swapchainWidth;
        multisampledTextureHeight = swapchainHeight;

        multisampledTextureDescriptor = WGPUTextureDescriptor
        {
            .nextInChain = nullptr,
            .usage = WGPUTextureUsage_RenderAttachment,
            .dimension = WGPUTextureDimension_2D,
            .size = { multisampledTextureWidth, multisampledTextureHeight, 1 },
            .format = preferredFormat,
            .mipLevelCount = 1,
            .sampleCount = static_cast<uint32_t>(Renderer::data().msaaSamples > 1 ? 4 : 1),
            .viewFormatCount = 0,
            .viewFormats = nullptr,
        };
        multisampledTexture = wgpuDeviceCreateTexture(device, &multisampledTextureDescriptor);

        const WGPUTextureViewDescriptor multisampledTextureViewDescriptor =
        {
            .format = preferredFormat,
            .dimension = WGPUTextureViewDimension_2D,
            .baseMipLevel = 0,
            .mipLevelCount = 1,
            .baseArrayLayer = 0,
            .arrayLayerCount = 1,
            .aspect = WGPUTextureAspect_All,
        };
        multisampledTextureView = wgpuTextureCreateView(multisampledTexture, &multisampledTextureViewDescriptor);
    }

    const WGPURenderPassColorAttachment colourAttachments  =
    {
        .view = multisampledTextureView,
        .depthSlice = WGPU_DEPTH_SLICE_UNDEFINED,
        .resolveTarget = wgpuSwapChainGetCurrentTextureView(swapchain),
        .loadOp = WGPULoadOp_Clear,
        .storeOp = WGPUStoreOp_Store,
        .clearValue = { colours.x, colours.y, colours.z, colours.w },
    };

    const WGPURenderPassDescriptor renderPassDescriptor =
    {
        .colorAttachmentCount = 1,
        .colorAttachments = &colourAttachments,
        .depthStencilAttachment = nullptr,
    };

    const WGPUCommandEncoderDescriptor encoderDescriptor = {};
    WGPUCommandEncoder encoder = wgpuDeviceCreateCommandEncoder(device, &encoderDescriptor);

    WGPURenderPassEncoder pass = wgpuCommandEncoderBeginRenderPass(encoder, &renderPassDescriptor);
    ImGui_ImplWGPU_RenderDrawData(ImGui::GetDrawData(), pass);
    wgpuRenderPassEncoderEnd(pass);

    WGPUCommandBufferDescriptor commandBufferDescriptor = {};
    WGPUCommandBuffer commandBuffer = wgpuCommandEncoderFinish(encoder, &commandBufferDescriptor);
    WGPUQueue queue = wgpuDeviceGetQueue(device);
    wgpuQueueSubmit(queue, 1, &commandBuffer);

    wgpuTextureViewRelease(colourAttachments.resolveTarget);
    wgpuRenderPassEncoderRelease(pass);
    wgpuCommandEncoderRelease(encoder);
    wgpuCommandBufferRelease(commandBuffer);
}

void UImGui::WebGPURenderer::destroy() noexcept
{

}

void UImGui::WebGPURenderer::ImGuiNewFrame() noexcept
{
    ImGui_ImplWGPU_NewFrame();
    GUIRenderer::beginFrame();
}

void UImGui::WebGPURenderer::ImGuiShutdown() noexcept
{
    ImGui_ImplWGPU_Shutdown();
}

void UImGui::WebGPURenderer::ImGuiInit() noexcept
{
    ImGui_ImplGlfw_InitForOther(Window::getInternal(), true);
    ImGui_ImplGlfw_InstallEmscriptenCallbacks(Window::getInternal(), "canvas");

    ImGui_ImplWGPU_InitInfo initInfo{};
    initInfo.Device = device;
    initInfo.NumFramesInFlight = 3;
    initInfo.RenderTargetFormat = preferredFormat;
    initInfo.DepthStencilFormat = WGPUTextureFormat_Undefined;
    initInfo.PipelineMultisampleState.count = static_cast<uint32_t>(Renderer::data().msaaSamples > 1 ? 4 : 1);

    ImGui_ImplWGPU_Init(&initInfo);
}

void UImGui::WebGPURenderer::ImGuiRenderData() noexcept
{

}
#else
void UImGui::WebGPURenderer::init(RendererInternalMetadata& metadata) noexcept {}
void UImGui::WebGPURenderer::renderStart(double deltaTime) noexcept {}
void UImGui::WebGPURenderer::renderEnd(double deltaTime) noexcept {}
void UImGui::WebGPURenderer::destroy() noexcept {}

void UImGui::WebGPURenderer::ImGuiNewFrame() noexcept {}
void UImGui::WebGPURenderer::ImGuiShutdown() noexcept {}
void UImGui::WebGPURenderer::ImGuiInit() noexcept {}
void UImGui::WebGPURenderer::ImGuiRenderData() noexcept {}
#endif
#include <Renderer/RendererUtils.hpp>

void UImGui::WebGPURenderer::setupWindowIntegration() noexcept
{
    RendererUtils::setupManually();
}

void UImGui::WebGPURenderer::setupPostWindowCreation() noexcept{};
void UImGui::WebGPURenderer::waitOnGPU() noexcept{}
void UImGui::WebGPURenderer::parseCustomConfig(YAML::Node&) noexcept{};
