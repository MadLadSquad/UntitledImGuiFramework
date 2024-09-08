#pragma once
#ifndef __EMSCRIPTEN__
#include "VKInstance.hpp"
#include "VKSurface.hpp"
#include "VKDescriptors.hpp"
#include "VKUtility.hpp"

namespace UImGui
{
    class RendererInternal;
    class UIMGUI_PUBLIC_API VKDevice
    {
    public:
        VKDevice() = default;
        explicit VKDevice(VKInstance& inst) noexcept;

        void create(RendererInternal& renderer) noexcept;
        [[nodiscard]] const vk::Device& get() const noexcept;
        void destroy() const noexcept;

        ~VKDevice() = default;
    private:
        friend class VKDraw;

        void createPhysicalDevice() noexcept;
        void setMSAASamples() const noexcept;

        VKInstance* instance = nullptr;

        VKSurface surface{};
        VKDescriptorPools descriptorPools{ *this };
        QueueFamilyIndices indices;

        vk::Queue queue{};
        vk::Queue presentationQueue{};

        vk::Device device{};

        vk::PhysicalDevice physicalDevice{};
        vk::PhysicalDeviceProperties deviceProperties{};
    };
}
#endif