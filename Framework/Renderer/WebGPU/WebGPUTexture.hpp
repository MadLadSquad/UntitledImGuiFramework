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
        WebGPUTexture(String location, bool bFiltered) noexcept;

        // Event Safety - Any time
        virtual void init(String location, bool bFiltered) noexcept override;

        virtual void load(void* data, FVector2 size, uint32_t depth, bool bFreeImageData,
                                const TFunction<void(void*)>& freeFunc) noexcept override;

        // Event Safety - Post-begin
        virtual uintptr_t get() noexcept override;

        // Cleans up the image data
        // Event Safety - All initiated
        virtual void clear() noexcept override;
        virtual ~WebGPUTexture() noexcept override;
    private:
#ifdef __EMSCRIPTEN__
        WGPUTextureDescriptor textureDescriptor{};
        WGPUTexture texture = nullptr;
        WGPUTextureView textureView = nullptr;
        bool bCreated = false;
#endif
    };

}
