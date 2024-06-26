#pragma once
#ifndef __EMSCRIPTEN__
#include "VKInstance.hpp"

namespace UImGui
{
    class VKDevice
    {
    public:
        VKDevice() = default;
        explicit VKDevice(VKInstance& inst) noexcept;
        ~VKDevice() = default;
    private:
        VKInstance* instance = nullptr;

        VkQueue queue{};
        VkQueue presentationQueue{};
        VkDevice device{};
        VkPhysicalDevice physicalDevice{};
        //QueueFamilyIndices indices;
    };
}
#endif