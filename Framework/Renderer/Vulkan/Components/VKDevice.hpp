#pragma once
#ifndef __EMSCRIPTEN__
#include "VKInstance.hpp"
#include "VKUtility.hpp"
#include <Types.hpp>

namespace UImGui
{
    class VKDevice
    {
    public:
        VKDevice() = default;
        explicit VKDevice(VKInstance& inst) noexcept;

        void createDevice() noexcept;
        void destroyDevice() const noexcept;

        void createPhysicalDevice() noexcept;

        ~VKDevice() = default;
    private:
        friend class VKSwapchain;
        friend struct SwapchainImage;

        VKInstance* instance = nullptr;

        vk::Queue queue{};
        vk::Queue presentationQueue{};
        vk::Device device{};
        vk::PhysicalDevice physicalDevice{};

        vk::PhysicalDeviceProperties deviceProperties{};

        void setMSAASamples() const noexcept;
        QueueFamilyIndices indices;
    };
}
#endif