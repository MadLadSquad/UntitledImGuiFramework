#pragma once
#include <array>
#include <vector>

#ifndef __EMSCRIPTEN__
#include <vulkan/vulkan.h>

namespace UImGui
{
    class VKDevice;

    constexpr std::array<const char*, 2> deviceExtensions =
    {
        VK_KHR_SWAPCHAIN_EXTENSION_NAME,
        VK_EXT_CUSTOM_BORDER_COLOR_EXTENSION_NAME
    };

    struct SwapchainDetails
    {
        VkSurfaceCapabilitiesKHR surfaceCapabilities;
        std::vector<VkSurfaceFormatKHR> surfaceFormats;
        std::vector<VkPresentModeKHR> presentationModes;
    };
}
#endif