#include "WebGPURenderer.hpp"
#include <RendererUtils.hpp>
#include <WindowUtils.hpp>
#include <Interfaces/RendererInterface.hpp>
#include <Interfaces/WindowInterface.hpp>
#ifdef __EMSCRIPTEN__
    #include <imgui_impl_wgpu.h>
#endif
#include <Types.hpp>

void UImGui::WebGPURenderer::parseCustomConfig(const ryml::ConstNodeRef& config) noexcept {}
void UImGui::WebGPURenderer::saveCustomConfig(ryml::NodeRef& config) noexcept {}
void UImGui::WebGPURenderer::waitOnGPU() noexcept {}

void UImGui::WebGPURenderer::resizeSurface(uint32_t width, uint32_t height) noexcept
{
#ifdef __EMSCRIPTEN__
    this->width = width;
    this->height = height;

    surfaceConfiguration.width = width;
    surfaceConfiguration.height = height;
    wgpuSurfaceConfigure(surface, &surfaceConfiguration);

    if (msaaTextureView)
        wgpuTextureViewRelease(msaaTextureView);
    if (msaaTexture)
        wgpuTextureRelease(msaaTexture);

    WGPUTextureDescriptor msaaDesc = {};
    msaaDesc.dimension = WGPUTextureDimension_2D;
    msaaDesc.size = { width, height, 1 };
    msaaDesc.sampleCount = Renderer::data().msaaSamples > 4 ? 4 : Renderer::data().msaaSamples;
    msaaDesc.format = surfaceConfiguration.format;
    msaaDesc.mipLevelCount = 1;
    msaaDesc.usage = WGPUTextureUsage_RenderAttachment;

    msaaTexture = wgpuDeviceCreateTexture(device, &msaaDesc);
    msaaTextureView = wgpuTextureCreateView(msaaTexture, nullptr);
#endif
}

UImGui::WebGPURenderer::WebGPURenderer() noexcept
{
    type = UIMGUI_RENDERER_API_TYPE_HINT_WEBGPU;
}

void UImGui::WebGPURenderer::setupWindowIntegration() noexcept
{
    RendererUtils::setupManually();
}

#ifdef __EMSCRIPTEN__
static WGPUAdapter requestAdapter(wgpu::Instance& instance, UImGui::FString& gpuName, UImGui::FString& vendorString) noexcept
{
    wgpu::Adapter acquiredAdapter;
    wgpu::RequestAdapterOptions adapterOptions;
    auto onRequestAdapter = [&](wgpu::RequestAdapterStatus status, wgpu::Adapter adapter, wgpu::StringView message)
    {
        if (status != wgpu::RequestAdapterStatus::Success)
        {
            Logger::log("Failed to get a WebGPU adapter! Error: ", ULOG_LOG_TYPE_ERROR, message.data);
            return;
        }
        acquiredAdapter = std::move(adapter);
    };

    // Wait until we get an adapter
    wgpu::Future waitAdapterFunc {
        instance.RequestAdapter(&adapterOptions, wgpu::CallbackMode::WaitAnyOnly, onRequestAdapter)
    };
    wgpu::WaitStatus waitStatusAdapter = instance.WaitAny(waitAdapterFunc, UINT64_MAX);
    
    if (acquiredAdapter == nullptr || waitStatusAdapter != wgpu::WaitStatus::Success)
        Logger::log("Error when requesting the WebGPU adapter! Wait status: ", ULOG_LOG_TYPE_ERROR, static_cast<int>(waitStatusAdapter));

    auto c_adapter = acquiredAdapter.MoveToCHandle();

    WGPUAdapterInfo info = {};
    wgpuAdapterGetInfo(c_adapter, &info);

    gpuName.resize(info.description.length);
    memcpy(gpuName.data(), info.device.data, info.device.length);

    vendorString.resize(info.vendor.length);
    memcpy(vendorString.data(), info.vendor.data, info.vendor.length);

    wgpuAdapterInfoFreeMembers(info);

    Logger::log("Acquired a WebGPU adapter: ", ULOG_LOG_TYPE_SUCCESS, vendorString);

    return c_adapter;
}

static wgpu::Device requestDevice(wgpu::Instance& instance, wgpu::Adapter& adapter) noexcept
{
    // Set device callback functions
    wgpu::DeviceDescriptor devicesDescriptor;
    devicesDescriptor.SetDeviceLostCallback(
        wgpu::CallbackMode::AllowSpontaneous,
        [](const wgpu::Device&, wgpu::DeviceLostReason type, wgpu::StringView msg)
        {
            char* str = const_cast<char*>("Unknown");
            switch (type)
            {
            case wgpu::DeviceLostReason::Destroyed:
                str = const_cast<char*>("Destroyed");
                break;
            case wgpu::DeviceLostReason::CallbackCancelled:
                str = const_cast<char*>("Callback cancelled");
                break;
            case wgpu::DeviceLostReason::FailedCreation:
                str = const_cast<char*>("Creation failed");
                break;
            default:
                break;
            }

            Logger::log("WebGPU device lost! Reason: ", ULOG_LOG_TYPE_ERROR, str, " - ", msg.data);
        }
    );
    devicesDescriptor.SetUncapturedErrorCallback(
        [](const wgpu::Device&, wgpu::ErrorType type, wgpu::StringView msg)
        {
            char* str = const_cast<char*>("Unknown error");
            switch (type)
            {
            case wgpu::ErrorType::Validation:
                str = const_cast<char*>("Validation error");
                break;
            case wgpu::ErrorType::OutOfMemory:
                str = const_cast<char*>("Out of memory error");
                break;
            case wgpu::ErrorType::Internal:
                str = const_cast<char*>("Internal error");
                break;
            default:
                break;
            }

            Logger::log("WebGPU device error! ", ULOG_LOG_TYPE_ERROR, str, ": ", msg.data);
        }
    );

    wgpu::Device acquiredDevice;
    auto onRequestDevice = [&](wgpu::RequestDeviceStatus status, wgpu::Device dev, wgpu::StringView message)
    {
        if (status != wgpu::RequestDeviceStatus::Success)
        {
            Logger::log("Failed to get a WebGPU device! Error: ", ULOG_LOG_TYPE_ERROR, message.data);
            return;
        }
        acquiredDevice = std::move(dev);
    };

    // Synchronously (wait until) get Device
    wgpu::Future waitDeviceFunc { adapter.RequestDevice(&devicesDescriptor, wgpu::CallbackMode::WaitAnyOnly, onRequestDevice) };
    wgpu::WaitStatus waitStatusDevice = instance.WaitAny(waitDeviceFunc, UINT64_MAX);

    if (acquiredDevice == nullptr || waitStatusDevice != wgpu::WaitStatus::Success)
        Logger::log("Failed to request a WebGPU device! Wait status: ", ULOG_LOG_TYPE_ERROR, static_cast<int>(waitStatusDevice));
    return acquiredDevice;
}

#endif

void UImGui::WebGPURenderer::setupPostWindowCreation() noexcept
{
#ifdef __EMSCRIPTEN__
    static constexpr wgpu::InstanceFeatureName timedWaitAny = wgpu::InstanceFeatureName::TimedWaitAny;
    WGPUTextureFormat format = WGPUTextureFormat_Undefined;

    const wgpu::InstanceDescriptor instanceDescriptor
    {
        .requiredFeatureCount = 1,
        .requiredFeatures = &timedWaitAny,
    };
    wgpu::Instance inst = wgpu::CreateInstance(&instanceDescriptor);

    wgpu::Adapter adapter = requestAdapter(inst, gpuName, vendorString);

    device = requestDevice(inst, adapter).MoveToCHandle();

    wgpu::EmscriptenSurfaceSourceCanvasHTMLSelector canvasDescriptor = {};
    canvasDescriptor.selector = UImGui::Renderer::data().emscriptenCanvas;

    const wgpu::SurfaceDescriptor surfaceDescriptor{ .nextInChain = &canvasDescriptor };
    surface = inst.CreateSurface(&surfaceDescriptor).MoveToCHandle();

    if (!surface)
    {
        Logger::log("Failed to create the surface!", ULOG_LOG_TYPE_ERROR);
        return;
    }

    // Moving Dawn objects into WGPU handles
    instance = inst.MoveToCHandle();

    WGPUSurfaceCapabilities surfaceCapabilities = {};
    wgpuSurfaceGetCapabilities(surface, adapter.Get(), &surfaceCapabilities);

    format = surfaceCapabilities.formats[0];

    width = CAST(uint32_t, Window::getWindowSize().x);
    height = CAST(uint32_t, Window::getWindowSize().y);

    surfaceConfiguration =
    {
        .device = device,
        .format = format,
        .usage = WGPUTextureUsage_RenderAttachment,
        .width = width,
        .height = height,
        .alphaMode = WGPUCompositeAlphaMode_Auto,
        .presentMode = WGPUPresentMode_Fifo, // TODO: Use this code in the future: Renderer::data().bUsingVSync ? WGPUPresentMode_Fifo : WGPUPresentMode_Mailbox
    };

    wgpuSurfaceConfigure(surface, &surfaceConfiguration);
    queue = wgpuDeviceGetQueue(device);

    Logger::log("Successfully stated the WebGPU renderer!", ULOG_LOG_TYPE_SUCCESS);
#endif
}

void UImGui::WebGPURenderer::init(RendererInternalMetadata& metadata) noexcept
{
    metadata.gpuName = gpuName;
    metadata.vendorString = vendorString;
}

void UImGui::WebGPURenderer::renderStart(double deltaTime) noexcept
{
#ifdef __EMSCRIPTEN__
    auto w = CAST(int, Window::getWindowSize().x);
    auto h = CAST(int, Window::getWindowSize().y);

    if (width != w || height != h || width <= 0 || height <= 0 || (Renderer::data().msaaSamples > 1 && msaaTextureView == nullptr))
        resizeSurface(w, h);

    wgpuSurfaceGetCurrentTexture(surface, &surfaceTexture);
    if (ImGui_ImplWGPU_IsSurfaceStatusError(surfaceTexture.status))
        Logger::log("Unrecoverable surface texture status: ", ULOG_LOG_TYPE_ERROR, surfaceTexture.status);

    if (ImGui_ImplWGPU_IsSurfaceStatusSubOptimal(surfaceTexture.status))
        if (w > 0 && h > 0)
            resizeSurface(w, h);
#endif
}

void UImGui::WebGPURenderer::renderEnd(double deltaTime) noexcept
{
#ifdef __EMSCRIPTEN__
    auto clear = ImGui::GetStyle().Colors[ImGuiCol_WindowBg];

    const WGPUTextureViewDescriptor viewDescriptor
    {
        .format = surfaceConfiguration.format,
        .dimension = WGPUTextureViewDimension_2D,
        .mipLevelCount = WGPU_MIP_LEVEL_COUNT_UNDEFINED,
        .arrayLayerCount = WGPU_ARRAY_LAYER_COUNT_UNDEFINED,
        .aspect = WGPUTextureAspect_All,
    };
    WGPUTextureView swapchainView = wgpuTextureCreateView(surfaceTexture.texture, &viewDescriptor);

    WGPURenderPassColorAttachment colorAttachment = {};
    if (Renderer::data().msaaSamples <= 1)
    {
        colorAttachment.view = swapchainView;
        colorAttachment.resolveTarget = nullptr;
        colorAttachment.storeOp = WGPUStoreOp_Store;
    }
    else
    {
        colorAttachment.view = msaaTextureView;                // MSAA target
        colorAttachment.resolveTarget = swapchainView;       // resolve to surface
        colorAttachment.storeOp = WGPUStoreOp_Discard;
    }
    colorAttachment.loadOp = WGPULoadOp_Clear;
    colorAttachment.clearValue = { clear.x * clear.w, clear.y * clear.w, clear.z * clear.w, clear.w };
    colorAttachment.depthSlice = WGPU_DEPTH_SLICE_UNDEFINED;

    const WGPURenderPassDescriptor renderPassDescriptor
    {
        .colorAttachmentCount = 1,
        .colorAttachments = &colorAttachment
    };
    WGPUCommandEncoderDescriptor encoderDescriptor{};
    WGPUCommandEncoder encoder = wgpuDeviceCreateCommandEncoder(device, &encoderDescriptor);

    WGPURenderPassEncoder pass = wgpuCommandEncoderBeginRenderPass(encoder, &renderPassDescriptor);
    ImGui_ImplWGPU_RenderDrawData(ImGui::GetDrawData(), pass);
    wgpuRenderPassEncoderEnd(pass);

    WGPUCommandBufferDescriptor commandBufferDescriptor = {};
    WGPUCommandBuffer commandBuffer = wgpuCommandEncoderFinish(encoder, &commandBufferDescriptor);
    wgpuQueueSubmit(queue, 1, &commandBuffer);

    wgpuTextureViewRelease(swapchainView);

    wgpuRenderPassEncoderRelease(pass);
    wgpuCommandEncoderRelease(encoder);
    wgpuCommandBufferRelease(commandBuffer);
#endif
}

void UImGui::WebGPURenderer::destroy() noexcept
{
#ifdef __EMSCRIPTEN__
    if (msaaTextureView != nullptr)
        wgpuTextureViewRelease(msaaTextureView);
    if (msaaTexture != nullptr)
        wgpuTextureRelease(msaaTexture);

    wgpuSurfaceUnconfigure(surface);
    wgpuSurfaceRelease(surface);
    wgpuQueueRelease(queue);
    wgpuDeviceRelease(device);
    wgpuInstanceRelease(instance);
#endif
}

void UImGui::WebGPURenderer::ImGuiNewFrame() noexcept
{
#ifdef __EMSCRIPTEN__
    ImGui_ImplWGPU_NewFrame();
#endif
    RendererUtils::beginImGuiFrame();
}

void UImGui::WebGPURenderer::ImGuiShutdown() noexcept
{
#ifdef __EMSCRIPTEN__
    ImGui_ImplWGPU_Shutdown();
#endif
}

void UImGui::WebGPURenderer::ImGuiInit() noexcept
{
    RendererUtils::ImGuiInitOther();
    RendererUtils::ImGuiInstallCallbacks();
#ifdef __EMSCRIPTEN__
    ImGui_ImplWGPU_InitInfo init_info;
    init_info.Device = device;
    init_info.NumFramesInFlight = 3;
    init_info.RenderTargetFormat = surfaceConfiguration.format;
    init_info.DepthStencilFormat = WGPUTextureFormat_Undefined;
    init_info.PipelineMultisampleState = {
        .nextInChain = nullptr,
        .count = Renderer::data().msaaSamples > 4 ? 4 : Renderer::data().msaaSamples,
        .mask = UINT32_MAX,
        .alphaToCoverageEnabled = false
    };
    ImGui_ImplWGPU_Init(&init_info);
#endif
}

void UImGui::WebGPURenderer::ImGuiRenderData() noexcept
{
}

