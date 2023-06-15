#pragma once
#include <Defines.hpp>
#include <Types.hpp>

// Imports the C Texture API, defines the TextureData struct.
#include <C/Rendering/CTexture.h>

namespace UImGui
{
    typedef UImGui_TextureData TextureData;

    class UIMGUI_PUBLIC_API Texture
    {
    public:
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