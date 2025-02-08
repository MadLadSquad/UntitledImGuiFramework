#pragma once
#include <Types.hpp>
#include <C/Rendering/CTexture.h>
#include <stb_image_write.h>

namespace UImGui
{
    typedef UImGui_TextureData TextureData;
    typedef UImGui_TextureFormat TextureFormat;

    class UIMGUI_PUBLIC_API GenericTexture
    {
    public:
        typedef UImGui_Texture_CustomSaveFunction CustomSaveFunction;

        // Event Safety - Any time
        GenericTexture() noexcept = default;
        // Event Safety - Any time
        virtual void init(String location, bool bFiltered) noexcept = 0;

        // Event Safety - Post-begin
        virtual uintptr_t get() noexcept = 0;

        virtual void load(void* data, FVector2 size, uint32_t depth, bool bFreeImageData,
                                const TFunction<void(void*)>& freeFunc) noexcept = 0;
        /**
         * @brief Outputs an image with a given format to a file. Only works if the image buffer is not freed
         * automatically when loading the image.
         * @tparam format - The format of an image
         * @param location -
         * @param fmt - Format of the image, defaults to the value of the template argument. If template argument is set
         * to UIMGUI_TEXTURE_FORMAT_OTHER, it will check this value. If it reaches OTHER again, the custom save function
         * is called
         * @param jpegQuality - Quality of the output of the JPEG image from 0(lowest) and 100(highest). Default
         * argument sets it to 100
         */
        template<TextureFormat format>
        bool saveToFile(const String location, const TextureFormat fmt = format, const uint8_t jpegQuality = 100) noexcept
        {
            if (dt.data != nullptr)
            {
                if constexpr (format == UIMGUI_TEXTURE_FORMAT_PNG)
                    return stbi_write_png(location, static_cast<int>(dt.size.x), static_cast<int>(dt.size.y),
                                          dt.channels, dt.data, static_cast<int>(dt.size.x) * dt.channels);
                else if constexpr (format == UIMGUI_TEXTURE_FORMAT_BMP)
                    return stbi_write_bmp(location, static_cast<int>(dt.size.x), static_cast<int>(dt.size.y),
                                          dt.channels, dt.data);
                else if constexpr (format == UIMGUI_TEXTURE_FORMAT_TGA)
                    return stbi_write_tga(location, static_cast<int>(dt.size.x), static_cast<int>(dt.size.y),
                                          dt.channels, dt.data);
                else if constexpr (format == UIMGUI_TEXTURE_FORMAT_JPEG)
                    return stbi_write_jpg(location, static_cast<int>(dt.size.x), static_cast<int>(dt.size.y),
                                          dt.channels, dt.data, jpegQuality);
                else
                {
                    if (fmt == UIMGUI_TEXTURE_FORMAT_PNG)
                        return stbi_write_png(location, static_cast<int>(dt.size.x), static_cast<int>(dt.size.y),
                                              dt.channels, dt.data, static_cast<int>(dt.size.x) * dt.channels);
                    if (fmt == UIMGUI_TEXTURE_FORMAT_BMP)
                        return stbi_write_bmp(location, static_cast<int>(dt.size.x), static_cast<int>(dt.size.y),
                                              dt.channels, dt.data);
                    if (fmt == UIMGUI_TEXTURE_FORMAT_TGA)
                        return stbi_write_tga(location, static_cast<int>(dt.size.x), static_cast<int>(dt.size.y),
                                              dt.channels, dt.data);
                    if (fmt == UIMGUI_TEXTURE_FORMAT_JPEG)
                        return stbi_write_jpg(location, static_cast<int>(dt.size.x), static_cast<int>(dt.size.y),
                                              dt.channels, dt.data, jpegQuality);
                    return dt.customSaveFunction(&dt, location);
                }
            }
            return false;
        }

        // Set a function for saving custom image file formats
        // Event Safety - All initiated
        void setCustomSaveFunction(CustomSaveFunction f) noexcept;

        // Returns the size of the image
        // Event Safety - Any time
        [[nodiscard]] const FVector2& size() const noexcept;

        // Cleans up the image data
        // Event Safety - All initiated
        virtual void clear() noexcept = 0;
        virtual ~GenericTexture() noexcept = default;
    protected:
        friend class Texture;

        void beginLoad(void** data, FVector2& size) noexcept;
        void endLoad(void* data, bool bFreeImageData, const TFunction<void(void*)>& freeFunc) noexcept;

        void defaultInit(String location, bool bFiltered) noexcept;
        void defaultClear() noexcept;
        TextureData dt{};
    };
}
