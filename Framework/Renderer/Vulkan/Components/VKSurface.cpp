#include "VKSurface.hpp"
#ifndef __EMSCRIPTEN__
#include <GLFW/glfw3.h>
#include <Types.hpp>
#include <Interfaces/WindowInterface.hpp>

void UImGui::VKSurface::create(VKInstance& instance) noexcept
{
    VkSurfaceKHR surf;
    const auto result = glfwCreateWindowSurface(instance.data(), Window::get().data(), nullptr, &surf);
    if (result != VK_SUCCESS)
    {
        Logger::log("Failed to create a window surface! Error code: ", UVK_LOG_TYPE_ERROR, result);
        std::terminate();
    }
    surface = surf;
    Logger::log("Created Vulkan render surface!", UVK_LOG_TYPE_NOTE);
}

bool UImGui::VKSurface::getPhysicalDeviceSurfaceSupport(const vk::PhysicalDevice& device, const QueueFamilyIndices& indices) noexcept
{
    const auto result = device.getSurfaceSupportKHR(indices.graphicsFamily, surface);
    if (result == VK_FALSE)
        return false;

    details.surfaceCapabilities = device.getSurfaceCapabilitiesKHR(surface);
    details.surfaceFormats = device.getSurfaceFormatsKHR(surface);
    if (details.surfaceFormats.empty())
        return false;

    details.presentationModes = device.getSurfacePresentModesKHR(surface);
    return !details.presentationModes.empty();
}

vk::SurfaceKHR& UImGui::VKSurface::get() noexcept
{
    return surface;
}
#endif
