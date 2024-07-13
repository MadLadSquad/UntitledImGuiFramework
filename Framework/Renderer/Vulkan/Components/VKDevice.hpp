#pragma once
#ifndef __EMSCRIPTEN__
#include "VKInstance.hpp"
#include "VKSurface.hpp"
#include "VKUtility.hpp"
#include <Types.hpp>

namespace UImGui
{
    class VKDevice
    {
    public:
        VKDevice() = default;
        explicit VKDevice(VKInstance& inst) noexcept;

        void create() noexcept;
        void destroy() const noexcept;

        ~VKDevice() = default;
    private:
        friend class VKSwapchain;
        friend struct SwapchainImage;

        void createPhysicalDevice() noexcept;
        void setMSAASamples() const noexcept;

        VKInstance* instance = nullptr;

        VKSurface surface{};
        QueueFamilyIndices indices;

        vk::Queue queue{};
        vk::Queue presentationQueue{};

        vk::Device device{};

        vk::PhysicalDevice physicalDevice{};
        vk::PhysicalDeviceProperties deviceProperties{};
    };
}
#endif