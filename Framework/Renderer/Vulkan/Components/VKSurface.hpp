#pragma once
#ifndef __EMSCRIPTEN__
#include "VKInstance.hpp"
#include "VKUtility.hpp"

namespace UImGui
{
    class VKSurface
    {
    public:
        VKSurface() noexcept = default;

        void create(VKInstance& instance) noexcept;
        void destroy(VKInstance& instance) const noexcept;

        bool getPhysicalDeviceSurfaceSupport(const vk::PhysicalDevice& device, const QueueFamilyIndices& indices) noexcept;

        vk::SurfaceKHR& get() noexcept;
    private:
        vk::SurfaceKHR surface{};
        SwapchainDetails details{};
    };
}
#endif