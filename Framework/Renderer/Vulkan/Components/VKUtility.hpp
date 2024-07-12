#pragma once
#include <array>
#include <vector>

#ifndef __EMSCRIPTEN__
#include <vulkan/vulkan.hpp>

namespace UImGui
{
    class VKDevice;

    struct SwapchainDetails
    {
        vk::SurfaceCapabilitiesKHR surfaceCapabilities;
        std::vector<vk::SurfaceFormatKHR> surfaceFormats;
        std::vector<vk::PresentModeKHR> presentationModes;
    };

    struct QueueFamilyIndices
    {
        int graphicsFamily = -1;
        int presentationFamily = -1;

        [[nodiscard]] bool valid() const noexcept;
    };
}
#endif