#pragma once
#include <Types.hpp>
#include <stb_image_write.h>

// Imports the C Texture API, defines the TextureData struct.
#include <C/Rendering/CTexture.h>

namespace UImGui
{
    typedef UImGui_TextureData TextureData;
    typedef UImGui_TextureFormat TextureFormat;

    class UIMGUI_PUBLIC_API Texture
    {
    public:
        typedef UImGui_Texture_CustomSaveFunction CustomSaveFunction;

        // Event Safety - Any time
        Texture() = default;
        /**
         * @brief Saves the name of a file for the texture to load
         * @param file - The name of the image file to be loaded
         * @note Event Safety - Any time
         */
        explicit Texture(String file) noexcept;
        /**
         * @brief Equivalent to calling the constructor
         * @note Event Safety - Any time
         */
        void init(String file) noexcept;

        // Loads the image for regular OpenGL/Vulkan usage.
        // Event Safety - Post-begin
        void load(void* data = nullptr, uint32_t x = 0, uint32_t y = 0, uint32_t depth = 0, bool bFreeImageData = true,
                  const std::function<void(void*)>& freeFunc = UImGui_Texture_defaultFreeFunc) noexcept;
        // Loads the image for dear imgui OpenGL/Vulkan usage
        // Event Safety - Post-begin
        void loadImGui(void* data = nullptr, uint32_t x = 0, uint32_t y = 0, uint32_t depth = 0, bool bFreeImageData = true,
                       const std::function<void(void*)>& freeFunc = UImGui_Texture_defaultFreeFunc) noexcept;

        // Returns the image buffer
        // Event Safety - Any time
        [[nodiscard]] const uint32_t& get() const noexcept;

        // Use the regular OpenGL/Vulkan image
        // Event Safety - All initiated
        void use() const noexcept;

        // Returns the size of the image
        // Event Safety - Any time
        [[nodiscard]] const FVector2& size() const noexcept;

        // Outputs an image with a given format to a file. Only works if the image buffer is not freed automatically
        // when loading the image.
        // jpegQuality is set to 100 by default in the C++ API. 0 = lowest quality, 100 = highest quality
        // Even Safety - Post-begin

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
        bool saveToFile(String location, TextureFormat fmt = format, uint8_t jpegQuality = 100) noexcept
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
                    else if (fmt == UIMGUI_TEXTURE_FORMAT_BMP)
                        return stbi_write_bmp(location, static_cast<int>(dt.size.x), static_cast<int>(dt.size.y),
                                              dt.channels, dt.data);
                    else if (fmt == UIMGUI_TEXTURE_FORMAT_TGA)
                        return stbi_write_tga(location, static_cast<int>(dt.size.x), static_cast<int>(dt.size.y),
                                              dt.channels, dt.data);
                    else if (fmt == UIMGUI_TEXTURE_FORMAT_JPEG)
                        return stbi_write_jpg(location, static_cast<int>(dt.size.x), static_cast<int>(dt.size.y),
                                              dt.channels, dt.data, jpegQuality);
                    else
                        return dt.customSaveFunction(&dt, location);
                }
            }
            return false;
        }

        // Set a function for saving custom image file formats
        // Event Safety - All initiated
        void setCustomSaveFunction(CustomSaveFunction f) noexcept;

        // Cleans up the image data
        // Event Safety - All initiated
        void clear() noexcept;
        // Same as calling clear
        // Event Safety - All initiated
        ~Texture() noexcept;
    private:
        TextureData dt{};
    };
}