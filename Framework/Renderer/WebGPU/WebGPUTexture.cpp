#include <WebGPU/WebGPUTexture.hpp>
#include <Renderer/RendererUtils.hpp>
#include <Interfaces/RendererInterface.hpp>

void UImGui::WebGPUTexture::init(TextureData& dt, const String location, const bool bFiltered) noexcept
{
    defaultInit(dt, location, bFiltered);
#ifdef __EMSCRIPTEN__
    dt.context = new WebGPUTextureData{};
    dt.contextSize = sizeof(WebGPUTextureData);
#endif
}

void UImGui::WebGPUTexture::load(TextureData& dt, void* data, FVector2 size, uint32_t depth, const bool bFreeImageData,
    const TFunction<void(void*)>& freeFunc) noexcept
{
    beginLoad(dt, &data, size);
#ifdef __EMSCRIPTEN__
    auto* texDt = static_cast<WebGPUTextureData*>(dt.context);

    texDt->textureDescriptor = WGPUTextureDescriptor
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
    auto* renderer = dynamic_cast<WebGPURenderer*>(RendererUtils::getRenderer());
    texDt->texture = wgpuDeviceCreateTexture(renderer->device, &texDt->textureDescriptor);

    const WGPUImageCopyTexture destination =
    {
        .texture = texDt->texture,
        .mipLevel = 0,
        .origin = { 0, 0, 0 },
        .aspect = WGPUTextureAspect_All,
    };

    const WGPUTextureDataLayout source =
    {
        .offset = 0,
        .bytesPerRow = 4 * texDt->textureDescriptor.size.width,
        .rowsPerImage = texDt->textureDescriptor.size.height,
    };

    // * 4 because RGBA
    wgpuQueueWriteTexture(wgpuDeviceGetQueue(renderer->device), &destination, data, static_cast<uint32_t>(size.x * size.y * 4), &source, &texDt->textureDescriptor.size);

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
    texDt->textureView = wgpuTextureCreateView(texDt->texture, &textureViewDescriptor);
    texDt->bCreated = true;
#endif
    endLoad(dt, data, bFreeImageData, freeFunc);
}

uintptr_t UImGui::WebGPUTexture::get(TextureData& dt) noexcept
{
#ifdef __EMSCRIPTEN__
    return reinterpret_cast<uintptr_t>(static_cast<WebGPUTextureData*>(dt.context)->textureView);
#else
    return 0;
#endif
}

void UImGui::WebGPUTexture::clear(TextureData& dt) noexcept
{
#ifdef __EMSCRIPTEN__
    auto* texDt = static_cast<WebGPUTextureData*>(dt.context);
    if (Renderer::data().textureRendererType == UIMGUI_RENDERER_TYPE_VULKAN_WEBGPU && texDt->bCreated)
    {
        wgpuTextureViewRelease(texDt->textureView);
        wgpuTextureDestroy(texDt->texture);
        wgpuTextureRelease(texDt->texture);
        texDt->bCreated = false;
    }
#endif
    defaultClear(dt);
}
