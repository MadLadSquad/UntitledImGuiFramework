#include "WebGPUTexture.hpp"
#include "WebGPURenderer.hpp"
#include "RendererUtils.hpp"
#include <Interfaces/RendererInterface.hpp>
#include <Defines.hpp>

void UImGui::WebGPUTexture::init(TextureData& dt, const String location, const bool bFiltered) noexcept
{
    defaultInit(dt, location, bFiltered);
#ifdef __EMSCRIPTEN__
    dt.context = new WebGPUTextureData{};
    dt.contextSize = sizeof(WebGPUTextureData);
#endif
}

void UImGui::WebGPUTexture::load(TextureData& dt, void* data, FVector2 size, uint32_t depth, const bool bFreeImageData, const std::function<void(void*)>& freeFunc) noexcept
{
    beginLoad(dt, &data, size);
#ifdef __EMSCRIPTEN__
    auto* renderer = static_cast<WebGPURenderer*>(UImGui::RendererUtils::getRenderer());
    auto* texData = static_cast<WebGPUTextureData*>(dt.context);

    const WGPUTextureDescriptor texDesc
    {
        .usage = WGPUTextureUsage_TextureBinding | WGPUTextureUsage_CopyDst,
        .dimension = WGPUTextureDimension_2D,
        .size = { CAST(uint32_t, size.x), CAST(uint32_t, size.y), 1 },
        .format = WGPUTextureFormat_RGBA8Unorm,
        .mipLevelCount = 1,
        .sampleCount = 1,
    };

    texData->texture = wgpuDeviceCreateTexture(renderer->device, &texDesc);

    const WGPUTexelCopyTextureInfo dst
    {
        .texture = texData->texture,
        .mipLevel = 0,
        .origin = { 0, 0, 0 },
        .aspect = WGPUTextureAspect_All,
    };

    const WGPUTexelCopyBufferLayout layout
    {
        .offset = 0,
        .bytesPerRow = CAST(uint32_t, size.x) * 4,
        .rowsPerImage = CAST(uint32_t, size.y),
    };

    const WGPUExtent3D extent
    {
        .width = CAST(uint32_t, size.x),
        .height = CAST(uint32_t, size.y),
        .depthOrArrayLayers = 1,
    };

    wgpuQueueWriteTexture(renderer->queue, &dst, data, CAST(uint32_t, size.x) * CAST(uint32_t, size.y) * 4, &layout, &extent);

    static constexpr WGPUTextureViewDescriptor viewDesc
    {
        .format = WGPUTextureFormat_RGBA8Unorm,
        .dimension = WGPUTextureViewDimension_2D,
        .baseMipLevel = 0,
        .mipLevelCount = 1,
        .baseArrayLayer = 0,
        .arrayLayerCount = 1,
    };

    texData->textureView = wgpuTextureCreateView(texData->texture, &viewDesc);
    texData->bCreated = true;
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
