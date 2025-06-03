#pragma once
#include <GenericRenderer/GenericTexture.hpp>
#ifndef __EMSCRIPTEN__
    #include <vulkan/vulkan.hpp>
#endif

namespace UImGui
{
    class UIMGUI_PUBLIC_API VulkanTexture final : public GenericTexture
    {
    public:
        VulkanTexture() noexcept = default;

        // Event Safety - Any time
        virtual void init(TextureData& dt, String location, bool bFiltered) noexcept override;

        virtual void load(TextureData& dt, void* data, FVector2 size, uint32_t depth, bool bFreeImageData,
                                const TFunction<void(void*)>& freeFunc) noexcept override;

        // Event Safety - Post-begin
        virtual uintptr_t get(TextureData& dt) noexcept override;

        // Cleans up the image data
        // Event Safety - All initiated
        virtual void clear(TextureData& dt) noexcept override;
        virtual ~VulkanTexture() noexcept override = default;
    private:
#ifndef __EMSCRIPTEN__
        struct VulkanTextureData
        {
            bool bCreated = false;
            VkDescriptorSet descriptorSet = nullptr;

            vk::ImageView imageView{};
            vk::Image image{};
            vk::DeviceMemory imageMemory{};
            vk::Sampler sampler{};
            vk::Buffer uploadBuffer{};
            vk::DeviceMemory uploadBufferMemory{};
        };
#endif
    };
}