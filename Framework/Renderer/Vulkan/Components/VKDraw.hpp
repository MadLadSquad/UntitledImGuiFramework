#pragma once
#ifndef __EMSCRIPTEN__
#include "VKInstance.hpp"
#include "VKDevice.hpp"
#include <imgui_impl_vulkan.h>

namespace UImGui
{
    // Struct that combines framebuffers, swapchains, render passes, etc. in one package
    class UIMGUI_PUBLIC_API VKDraw
    {
    public:
        VKDraw() noexcept = default;
        VKDraw(VKInstance& inst, VKDevice& dev) noexcept;

        void init() noexcept;
        void destroy() noexcept;

        void ImGuiInit() const noexcept;
        void ImGuiPreDraw() noexcept;
        void ImGuiDraw(void* drawData) noexcept;

        void waitOnGPU() const noexcept;
    private:
        friend class WindowInternal;
        friend class VulkanTexture;

        VKInstance* instance = nullptr;
        VKDevice* device = nullptr;

        ImGui_ImplVulkanH_Window window{};
        bool bRebuildSwapchain = false;
        int minimalImageCount = 2;

        void recordCommands(void* drawData, VkSemaphore& imageAcquired, VkSemaphore& renderComplete) noexcept;
        void present() noexcept;
    };
}
#endif