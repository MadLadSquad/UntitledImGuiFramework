#pragma once
#include <GenericRenderer/GenericTexture.hpp>
#ifdef __EMSCRIPTEN__
    #include <emscripten/html5.h>
    #include <webgpu/webgpu.h>
    #include <webgpu/webgpu_cpp.h>
#endif

namespace UImGui
{
    class UIMGUI_PUBLIC_API WebGPUTexture : public GenericTexture
    {
    public:
        void init(TextureData& dt, String location, bool bFiltered) noexcept override;
        void load(TextureData& dt, void* data, FVector2 size, uint32_t depth, bool bFreeImageData, const std::function<void(void*)>& freeFunc) noexcept override;

        uintptr_t get(TextureData& dt) noexcept override;

        void clear(TextureData& dt) noexcept override;
    private:
#ifdef __EMSCRIPTEN__
        struct WebGPUTextureData
        {
            WGPUTexture texture{};
            WGPUTextureView textureView{};

            bool bCreated = false;
        };
#endif
    };
}