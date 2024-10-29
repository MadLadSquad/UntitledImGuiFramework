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
        VulkanTexture(String location, bool bFiltered) noexcept;

        // Event Safety - Any time
        virtual void init(String location, bool bFiltered) noexcept override;

        virtual void load(void* data, FVector2 size, uint32_t depth, bool bFreeImageData,
                                const TFunction<void(void*)>& freeFunc) noexcept override;

        // Event Safety - Post-begin
        virtual uintptr_t get() noexcept override;

        // Cleans up the image data
        // Event Safety - All initiated
        virtual void clear() noexcept override;
        virtual ~VulkanTexture() noexcept override;
    private:
#ifndef __EMSCRIPTEN__
        VkDescriptorSet descriptorSet = nullptr;

        vk::ImageView imageView{};
        vk::Image image{};
        vk::DeviceMemory imageMemory{};
        vk::Sampler sampler{};
        vk::Buffer uploadBuffer{};
        vk::DeviceMemory uploadBufferMemory{};
#endif
    };
}