#pragma once
#include <GenericRenderer/GenericTexture.hpp>

namespace UImGui
{
    class UIMGUI_PUBLIC_API OpenGLTexture final : public GenericTexture
    {
    public:
        OpenGLTexture() noexcept = default;

        // Event Safety - Any time
        virtual void init(TextureData& dt, String location, bool bFiltered) noexcept override;

        virtual void load(TextureData& dt, void* data, FVector2 size, uint32_t depth, bool bFreeImageData,
                                const TFunction<void(void*)>& freeFunc) noexcept override;

        // Event Safety - Post-begin
        virtual uintptr_t get(TextureData& dt) noexcept override;

        // Cleans up the image data
        // Event Safety - All initiated
        virtual void clear(TextureData& dt) noexcept override;
        virtual ~OpenGLTexture() noexcept override = default;
    };
}