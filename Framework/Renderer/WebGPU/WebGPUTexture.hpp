#pragma once
#include <GenericRenderer/GenericTexture.hpp>
#ifdef __EMSCRIPTEN__
    #include "imgui_impl_wgpu.h"
    #include <emscripten.h>
    #include <emscripten/html5.h>
    #include <emscripten/html5_webgpu.h>
#endif

namespace UImGui
{
    class UIMGUI_PUBLIC_API WebGPUTexture final : public GenericTexture
    {
    public:
        WebGPUTexture() noexcept = default;

        // Event Safety - Any time
        virtual void init(TextureData& dt, String location, bool bFiltered) noexcept override;

        virtual void load(TextureData& dt, void* data, FVector2 size, uint32_t depth, bool bFreeImageData,
                                const TFunction<void(void*)>& freeFunc) noexcept override;

        // Event Safety - Post-begin
        virtual uintptr_t get(TextureData& dt) noexcept override;

        // Cleans up the image data
        // Event Safety - All initiated
        virtual void clear(TextureData& dt) noexcept override;
        virtual ~WebGPUTexture() noexcept override = default;
    private:
#ifdef __EMSCRIPTEN__
        struct WebGPUTextureData
        {
            WGPUTextureDescriptor textureDescriptor{};
            WGPUTexture texture = nullptr;
            WGPUTextureView textureView = nullptr;
            bool bCreated = false;
        };
#endif
    };

}
