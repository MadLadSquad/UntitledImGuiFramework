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
    class WebGPUTexture final : public GenericTexture
    {
    public:
        WebGPUTexture() noexcept = default;
        explicit WebGPUTexture(String location) noexcept;

        // Event Safety - Any time
        virtual void init(String location) noexcept override;

        virtual void load(void* data, FVector2 size, uint32_t depth, bool bFreeImageData,
                                const std::function<void(void*)>& freeFunc) noexcept override;

        // Event Safety - Post-begin
        virtual void* get() noexcept override;

        // Cleans up the image data
        // Event Safety - All initiated
        virtual void clear() noexcept override;
        virtual ~WebGPUTexture() noexcept override;
    private:
#ifdef __EMSCRIPTEN__
        WGPUTextureDescriptor textureDescriptor{};
        WGPUTexture texture = nullptr;
        WGPUTextureView textureView = nullptr;

#endif
    };

}
