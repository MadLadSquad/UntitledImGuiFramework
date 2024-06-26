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

    enum class VKShaderType
    {
        VK_SHADER_TYPE_NONE = 0,
        VK_SHADER_TYPE_VERTEX = 0x00000001,
        VK_SHADER_TYPE_FRAGMENT = 0x00000010,
        VK_SHADER_TYPE_GEOMETRY = 0x00000008,
        VK_SHADER_TYPE_COMPUTE = 0x00000020,
        VK_SHADER_TYPE_TESSELLATION_CONTROL = 0x00000002,
        VK_SHADER_TYPE_TESSELLATION_EVALUATION = 0x00000004,
    };


}
#endif