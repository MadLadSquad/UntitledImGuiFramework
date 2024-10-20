#include <WebGPU/WebGPUTexture.hpp>
#include <Interfaces/RendererInterface.hpp>

UImGui::WebGPUTexture::WebGPUTexture(const String location) noexcept
{
    init(location);
}

void UImGui::WebGPUTexture::init(const String location) noexcept
{
    defaultInit(location);
}

void UImGui::WebGPUTexture::load(void* data, FVector2 size, uint32_t depth, const bool bFreeImageData,
    const TFunction<void(void*)>& freeFunc) noexcept
{
    beginLoad(&data, size);
#ifdef __EMSCRIPTEN__
    textureDescriptor = WGPUTextureDescriptor
    {
        .nextInChain = nullptr,
        .usage = WGPUTextureUsage_TextureBinding | WGPUTextureUsage_CopyDst,
        .dimension = WGPUTextureDimension_2D,
        .size = { static_cast<uint32_t>(size.x), static_cast<uint32_t>(size.y), 1 },
        .format = WGPUTextureFormat_RGBA8Unorm,
        .mipLevelCount = 1,
        .sampleCount = 1,
        .viewFormatCount = 0,
        .viewFormats = nullptr,
    };
    texture = wgpuDeviceCreateTexture(Renderer::get().wgpu.device, &textureDescriptor);

    const WGPUImageCopyTexture destination =
    {
        .texture = texture,
        .mipLevel = 0,
        .origin = { 0, 0, 0 },
        .aspect = WGPUTextureAspect_All,
    };

    const WGPUTextureDataLayout source =
    {
        .offset = 0,
        .bytesPerRow = 4 * textureDescriptor.size.width,
        .rowsPerImage = textureDescriptor.size.height,
    };

    // * 4 because RGBA
    wgpuQueueWriteTexture(wgpuDeviceGetQueue(Renderer::get().wgpu.device), &destination, data, static_cast<uint32_t>(size.x * size.y * 4), &source, &textureDescriptor.size);

    constexpr WGPUTextureViewDescriptor textureViewDescriptor =
    {
        .format = WGPUTextureFormat_RGBA8Unorm,
        .dimension = WGPUTextureViewDimension_2D,
        .baseMipLevel = 0,
        .mipLevelCount = 1,
        .baseArrayLayer = 0,
        .arrayLayerCount = 1,
        .aspect = WGPUTextureAspect_All,
    };
    textureView = wgpuTextureCreateView(texture, &textureViewDescriptor);
#endif
    endLoad(data, size, bFreeImageData, freeFunc);
}

void* UImGui::WebGPUTexture::get() noexcept
{
#ifdef __EMSCRIPTEN__
    return textureView;
#else
    return nullptr;
#endif
}

void UImGui::WebGPUTexture::clear() noexcept
{
#ifdef __EMSCRIPTEN__
    wgpuTextureViewRelease(textureView);
    wgpuTextureDestroy(texture);
    wgpuTextureRelease(texture);
#endif
    defaultClear();
}

UImGui::WebGPUTexture::~WebGPUTexture() noexcept
{
    clear();
}
