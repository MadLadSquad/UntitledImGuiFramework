#pragma once
#include <Defines.hpp>
#include <Types.hpp>

namespace UImGui
{
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
        void load() noexcept;
        // Loads the image for dear imgui OpenGL/Vulkan usage
        // Event Safety - Post-begin
        void loadImGui() noexcept;

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
        FString filename{};
        uint32_t id = 0;
        FVector2 sz = { 0.0f, 0.0f };
        int channels = 0;
    };
}