#pragma once
#include <GenericRenderer/GenericTexture.hpp>

namespace UImGui
{
    class UIMGUI_PUBLIC_API OpenGLTexture final : public GenericTexture
    {
    public:
        OpenGLTexture() noexcept = default;
        explicit OpenGLTexture(String location) noexcept;

        // Event Safety - Any time
        virtual void init(String location) noexcept override;

        virtual void load(void* data, FVector2 size, uint32_t depth, bool bFreeImageData,
                                const TFunction<void(void*)>& freeFunc) noexcept override;

        // Event Safety - Post-begin
        virtual uintptr_t get() noexcept override;

        // Cleans up the image data
        // Event Safety - All initiated
        virtual void clear() noexcept override;
        virtual ~OpenGLTexture() noexcept override;
    private:
        uint32_t id = 0;
    };
}