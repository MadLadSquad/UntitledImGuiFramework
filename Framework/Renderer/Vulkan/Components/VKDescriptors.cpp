#include "VKDescriptors.hpp"
#ifndef __EMSCRIPTEN__
#include "VKDevice.hpp"

UImGui::VKDescriptorPools::VKDescriptorPools(VKDevice& dev) noexcept
{
    device = &dev;
}

void UImGui::VKDescriptorPools::allocate() noexcept
{
    constexpr vk::DescriptorPoolSize descriptorPoolSizes[] =
    {
        {
            .type = vk::DescriptorType::eCombinedImageSampler,
            .descriptorCount = 1
        },
    };
    constexpr vk::DescriptorPoolCreateInfo descriptorPoolCreateInfo =
    {
        .flags = vk::DescriptorPoolCreateFlagBits::eFreeDescriptorSet,
        .maxSets = 1,
        .poolSizeCount = CARRAY_SIZE(descriptorPoolSizes),
        .pPoolSizes = descriptorPoolSizes,
    };
    pool = device->get().createDescriptorPool(descriptorPoolCreateInfo, nullptr);
    Logger::log("Allocated Vulkan descriptor pools!", UVK_LOG_TYPE_NOTE);
}

void UImGui::VKDescriptorPools::destroy() const noexcept
{
    device->get().destroyDescriptorPool(pool, nullptr);
}
#endif
