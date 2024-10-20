#pragma once
#include <Core/Types.hpp>

#ifndef __EMSCRIPTEN__
#include <vulkan/vulkan.hpp>

namespace UImGui
{
    class VKDevice;

    struct UIMGUI_PUBLIC_API SwapchainDetails
    {
        vk::SurfaceCapabilitiesKHR surfaceCapabilities;
        TVector<vk::SurfaceFormatKHR> surfaceFormats;
        TVector<vk::PresentModeKHR> presentationModes;
    };

    struct QueueFamilyIndices
    {
        int graphicsFamily = -1;
        int presentationFamily = -1;

        [[nodiscard]] bool valid() const noexcept;
    };
}
#endif