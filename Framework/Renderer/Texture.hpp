#pragma once
#include <OpenGL/OpenGLTexture.hpp>
#include <WebGPU/WebGPUTexture.hpp>
#include <Vulkan/VulkanTexture.hpp>

#include "Interfaces/RendererInterface.hpp"

#define TEX_RUN(x) return textures[static_cast<int>(Renderer::data().rendererType)]->x;

namespace UImGui
{
    class UIMGUI_PUBLIC_API Texture
    {
    public:
        typedef UImGui_Texture_CustomSaveFunction CustomSaveFunction;

        Texture() noexcept = default;
        // Event Safety - Post-begin
        Texture(String location, bool bFiltered = true) noexcept;
        // Event Safety - Post-begin
        void init(String location, bool bFiltered = true) noexcept;

        // Event Safety - Post-begin
        void load(void* data = nullptr,
                FVector2 size = { 0.0f, 0.0f },
                uint32_t depth = 0,
                bool bFreeImageData = false,
                const TFunction<void(void*)>& freeFunc = UImGui_Texture_defaultFreeFunc) noexcept;

        // Event Safety - Post-begin
        [[nodiscard]] uintptr_t get() noexcept;

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
            TEX_RUN(saveToFile<format>(location, fmt, jpegQuality));
        }

        // Set a function for saving custom image file formats
        // Event Safety - All initiated
        void setCustomSaveFunction(CustomSaveFunction f) noexcept;

        // Returns the size of the image
        // Event Safety - Any time
        [[nodiscard]] const FVector2& size() const noexcept;

        // Cleans up the image data
        // Event Safety - All initiated
        void clear() noexcept;
        ~Texture() noexcept;
    private:
        bool bCleared = false;

        OpenGLTexture opengl{};
#ifdef __EMSCRIPTEN__
        WebGPUTexture webgpu{};
#else
        VulkanTexture vulkan{};
#endif
        GenericTexture* custom = nullptr;

        GenericTexture* textures[UIMGUI_RENDERER_TYPE_COUNT] =
        {
            &opengl,
#ifdef __EMSCRIPTEN__
            &webgpu,
#else
            &vulkan,
#endif
            custom
        };
    };
}
