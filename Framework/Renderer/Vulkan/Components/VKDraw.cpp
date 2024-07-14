#include "VKDraw.hpp"
#ifndef __EMSCRIPTEN__
#include <Interfaces/WindowInterface.hpp>
#include <Interfaces/RendererInterface.hpp>

#include <imgui_impl_glfw.h>

UImGui::VKDraw::VKDraw(VKInstance& inst, VKDevice& dev) noexcept
{
    instance = &inst;
    device = &dev;
}

void UImGui::VKDraw::init() noexcept
{
    window.Surface = device->surface.get();
    constexpr VkFormat requestSurfaceImageFormat[] =
    {
        VK_FORMAT_R8G8B8A8_UNORM,
        VK_FORMAT_B8G8R8A8_UNORM,
        VK_FORMAT_R8G8B8_UNORM,
        VK_FORMAT_B8G8R8_UNORM,
    };
    constexpr VkColorSpaceKHR requestSurfaceColorSpace = VK_COLORSPACE_SRGB_NONLINEAR_KHR;
    window.SurfaceFormat = ImGui_ImplVulkanH_SelectSurfaceFormat(device->physicalDevice, window.Surface, requestSurfaceImageFormat, CARRAY_SIZE(requestSurfaceImageFormat), requestSurfaceColorSpace);

    VkPresentModeKHR presentationModes[] = { VK_PRESENT_MODE_MAILBOX_KHR, VK_PRESENT_MODE_FIFO_KHR, VK_PRESENT_MODE_IMMEDIATE_KHR };
    size_t presentationModesSize = CARRAY_SIZE(presentationModes);
    if (!Renderer::data().bUsingVSync)
    {
        presentationModesSize = 1;
        presentationModes[0] = VK_PRESENT_MODE_IMMEDIATE_KHR; // Free the frame rate
    }
    window.PresentMode = ImGui_ImplVulkanH_SelectPresentMode(device->physicalDevice, window.Surface, &presentationModes[0], CAST(int, presentationModesSize));

    // Create Swapchain, RenderPass, Framebuffer, etc.
    ImGui_ImplVulkanH_CreateOrResizeWindow(instance->data(), device->physicalDevice, device->device, &window, device->indices.graphicsFamily, nullptr, CAST(int, Window::windowSize().x), CAST(int, Window::windowSize().y), minimalImageCount);
    Logger::log("Started Vulkan renderer!", UVK_LOG_TYPE_SUCCESS);
}

void UImGui::VKDraw::destroy() noexcept
{
    ImGui_ImplVulkanH_DestroyWindow(instance->data(), device->device, &window, nullptr);
}

void UImGui::VKDraw::ImGuiInit() const noexcept
{
    ImGui_ImplGlfw_InitForVulkan(Window::get().data(), true);
    ImGui_ImplVulkan_InitInfo initInfo =
    {
        .Instance = instance->data(),
        .PhysicalDevice = device->physicalDevice,
        .Device = device->device,
        .QueueFamily = CAST(uint32_t, device->indices.graphicsFamily),
        .Queue = device->queue,
        .PipelineCache = VK_NULL_HANDLE,
        .DescriptorPool = device->descriptorPools.pool,
        .RenderPass = window.RenderPass,
        .Subpass = 0,
        .MinImageCount = CAST(uint32_t, minimalImageCount),
        .ImageCount = window.ImageCount,
        .MSAASamples = VK_SAMPLE_COUNT_1_BIT,//CAST(VkSampleCountFlagBits, Renderer::data().msaaSamples),
        .Allocator = nullptr,
        .CheckVkResultFn = [](VkResult result) -> void
        {
            if (result != VK_SUCCESS)
            {
                Logger::log("Dear imgui Vulkan rendering failure. Error code: ", UVK_LOG_TYPE_ERROR, result);
                std::terminate();
            }
        }
    };
    ImGui_ImplVulkan_Init(&initInfo);
}

void UImGui::VKDraw::ImGuiPreDraw() noexcept
{
    const auto size = Window::windowSize();
    const auto width = CAST(int, size.x);
    const auto height = CAST(int, size.y);

    if (width > 0 && height > 0 && (bRebuildSwapchain || window.Width != width || window.Height != height))
    {
        ImGui_ImplVulkan_SetMinImageCount(minimalImageCount);
        ImGui_ImplVulkanH_CreateOrResizeWindow(instance->data(), device->physicalDevice, device->device,
                                               &window, device->indices.graphicsFamily, nullptr, width, height,
                                               minimalImageCount);
        window.FrameIndex = 0;
        bRebuildSwapchain = false;
    }
}

void UImGui::VKDraw::ImGuiDraw(void* drawData) noexcept
{
    VkSemaphore image_acquired_semaphore  = window.FrameSemaphores[window.SemaphoreIndex].ImageAcquiredSemaphore;
    VkSemaphore render_complete_semaphore = window.FrameSemaphores[window.SemaphoreIndex].RenderCompleteSemaphore;
    VkResult result = vkAcquireNextImageKHR(device->device, window.Swapchain, UINT64_MAX, image_acquired_semaphore, VK_NULL_HANDLE, &window.FrameIndex);
    if (result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR)
    {
        bRebuildSwapchain = true;
        return;
    }

    const ImGui_ImplVulkanH_Frame* fd = &window.Frames[window.FrameIndex];
    {
        result = vkWaitForFences(device->device, 1, &fd->Fence, VK_TRUE, UINT64_MAX);
        if (result != VK_SUCCESS)
        {
            Logger::log("Couldn't wait on fences. Error code: ", UVK_LOG_TYPE_ERROR, result);
            std::terminate();
        }

        result = vkResetFences(device->device, 1, &fd->Fence);
        if (result != VK_SUCCESS)
        {
            Logger::log("Couldn't reset fences. Error code: ", UVK_LOG_TYPE_ERROR, result);
            std::terminate();
        }
    }
    {
        result = vkResetCommandPool(device->device, fd->CommandPool, 0);
        if (result != VK_SUCCESS)
        {
            Logger::log("Couldn't reset command pool. Error code: ", UVK_LOG_TYPE_ERROR, result);
            std::terminate();
        }

        constexpr VkCommandBufferBeginInfo info =
        {
            .sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO,
            .flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT,
        };
        result = vkBeginCommandBuffer(fd->CommandBuffer, &info);
        if (result != VK_SUCCESS)
        {
            Logger::log("Couldn't open the command buffer. Error code: ", UVK_LOG_TYPE_ERROR, result);
            std::terminate();
        }
    }
    {
        const VkRenderPassBeginInfo info =
        {
            .sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO,
            .renderPass = window.RenderPass,
            .framebuffer = fd->Framebuffer,
            .renderArea =
            {
                .extent =
                {
                    .width = CAST(uint32_t, window.Width),
                    .height = CAST(uint32_t, window.Height),
                }
            },
            .clearValueCount = 1,
            .pClearValues = &window.ClearValue,
        };
        vkCmdBeginRenderPass(fd->CommandBuffer, &info, VK_SUBPASS_CONTENTS_INLINE);
    }

    // Record dear imgui primitives into command buffer
    ImGui_ImplVulkan_RenderDrawData(CAST(ImDrawData*, drawData), fd->CommandBuffer);

    // Submit command buffer
    vkCmdEndRenderPass(fd->CommandBuffer);
    {
        constexpr VkPipelineStageFlags wait_stage = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
        const VkSubmitInfo info =
        {
            .sType = VK_STRUCTURE_TYPE_SUBMIT_INFO,
            .waitSemaphoreCount = 1,
            .pWaitSemaphores = &image_acquired_semaphore,
            .pWaitDstStageMask = &wait_stage,
            .commandBufferCount = 1,
            .pCommandBuffers = &fd->CommandBuffer,
            .signalSemaphoreCount = 1,
            .pSignalSemaphores = &render_complete_semaphore,
        };

        result = vkEndCommandBuffer(fd->CommandBuffer);
        if (result != VK_SUCCESS)
        {
            Logger::log("Couldn't close the command buffer. Error code: ", UVK_LOG_TYPE_ERROR, result);
            std::terminate();
        }
        result = vkQueueSubmit(device->queue, 1, &info, fd->Fence);
        if (result != VK_SUCCESS)
        {
            Logger::log("Couldn't submit to the queue. Error code: ", UVK_LOG_TYPE_ERROR, result);
            std::terminate();
        }
    }

    // Present frame
    if (bRebuildSwapchain)
        return;

    VkSemaphore renderComplete = window.FrameSemaphores[window.SemaphoreIndex].RenderCompleteSemaphore;
    const VkPresentInfoKHR info =
    {
        .sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR,
        .waitSemaphoreCount = 1,
        .pWaitSemaphores = &renderComplete,
        .swapchainCount = 1,
        .pSwapchains = &window.Swapchain,
        .pImageIndices = &window.FrameIndex
    };

    result = vkQueuePresentKHR(device->queue, &info);
    if (result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR)
    {
        bRebuildSwapchain = true;
        return;
    }
    window.SemaphoreIndex = (window.SemaphoreIndex + 1) % window.SemaphoreCount;
}
#endif
