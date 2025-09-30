#include "VKDraw.hpp"
#ifndef __EMSCRIPTEN__
#include <Interfaces/WindowInterface.hpp>
#include <Interfaces/RendererInterface.hpp>
#include <Window/WindowUtils.hpp>
#include <Defines.hpp>

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

    VkPresentModeKHR presentationModes[] = { VK_PRESENT_MODE_FIFO_KHR, VK_PRESENT_MODE_MAILBOX_KHR, VK_PRESENT_MODE_IMMEDIATE_KHR };
    size_t presentationModesSize = CARRAY_SIZE(presentationModes);
    if (!Renderer::data().bUsingVSync)
    {
        presentationModesSize = 1;
        presentationModes[0] = VK_PRESENT_MODE_IMMEDIATE_KHR; // Free the frame rate
    }
    window.PresentMode = ImGui_ImplVulkanH_SelectPresentMode(device->physicalDevice, window.Surface, &presentationModes[0], CAST(int, presentationModesSize));

    // Create Swapchain, RenderPass, Framebuffer, etc.
    ImGui_ImplVulkanH_CreateOrResizeWindow(
        instance->data(),
        device->physicalDevice,
        device->device,
        &window,
        device->indices.graphicsFamily,
        nullptr,
        CAST(int, Window::getWindowSize().x),
        CAST(int, Window::getWindowSize().y),
        minimalImageCount,
        VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT,
        CAST(VkSampleCountFlagBits, Renderer::data().msaaSamples)
    );
    Logger::log("Started Vulkan renderer!", ULOG_LOG_TYPE_SUCCESS);
}

void UImGui::VKDraw::destroy() noexcept
{
    device->queue.waitIdle();
    ImGui_ImplVulkanH_DestroyWindow(instance->data(), device->device, &window, nullptr);
}

void UImGui::VKDraw::ImGuiInit() const noexcept
{
    RendererUtils::Vulkan::ImGuiInit();
    ImGui_ImplVulkan_InitInfo initInfo =
    {
        .ApiVersion = VK_API_VERSION_1_3,
        .Instance = instance->data(),
        .PhysicalDevice = device->physicalDevice,
        .Device = device->device,
        .QueueFamily = CAST(uint32_t, device->indices.graphicsFamily),
        .Queue = device->queue,
        .DescriptorPool = device->descriptorPools.pool,
        .MinImageCount = CAST(uint32_t, minimalImageCount),
        .ImageCount = window.ImageCount,
        .PipelineCache = VK_NULL_HANDLE,
        .PipelineInfoMain =
        {
            .RenderPass = window.RenderPass,
            .Subpass = 0,
            .MSAASamples = CAST(VkSampleCountFlagBits, Renderer::data().msaaSamples),
        },
        .PipelineInfoForViewports =
        {
            .RenderPass = window.RenderPass,
            .Subpass = 0,
            .MSAASamples = CAST(VkSampleCountFlagBits, Renderer::data().msaaSamples),
        },
        .Allocator = nullptr,
        .CheckVkResultFn = [](VkResult result) -> void
        {
            if (result != VK_SUCCESS)
            {
                Logger::log("Dear imgui Vulkan rendering failure. Error code: ", ULOG_LOG_TYPE_ERROR, result);
                std::terminate();
            }
        }
    };
    ImGui_ImplVulkan_Init(&initInfo);
}

void UImGui::VKDraw::ImGuiPreDraw() noexcept
{
    auto size = Window::getWindowSize();
    auto width = CAST(int, size.x);
    auto height = CAST(int, size.y);

    if (bRebuildSwapchain || window.Width != width || window.Height != height)
    {
        while (width <= 0 || height <= 0)
        {
            size = Window::getWindowSize();
            width = CAST(int, size.x);
            height = CAST(int, size.y);
            WindowUtils::waitEvents();
        }

        device->device.waitIdle();
        ImGui_ImplVulkan_SetMinImageCount(minimalImageCount);
        ImGui_ImplVulkanH_CreateOrResizeWindow(
            instance->data(),
            device->physicalDevice,
            device->device,
            &window,
            device->indices.graphicsFamily,
            nullptr,
            width,
            height,
            minimalImageCount,
            VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT,
            CAST(VkSampleCountFlagBits, Renderer::data().msaaSamples)
        );
        window.FrameIndex = 0;
        bRebuildSwapchain = false;
    }
}

void UImGui::VKDraw::ImGuiDraw(void* drawData) noexcept
{
    VkSemaphore imageAcquired = window.FrameSemaphores[CAST(int, window.SemaphoreIndex)].ImageAcquiredSemaphore;
    VkSemaphore renderComplete = window.FrameSemaphores[CAST(int, window.SemaphoreIndex)].RenderCompleteSemaphore;
    VkResult result;

    result = vkAcquireNextImageKHR(device->device, window.Swapchain, UINT64_MAX, imageAcquired, VK_NULL_HANDLE, &window.FrameIndex);
    if (bRebuildSwapchain || result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR)
    {
        bRebuildSwapchain = true;
        ImGuiPreDraw();
        return;
    }

    const ImGui_ImplVulkanH_Frame* fd = &window.Frames[CAST(int, window.FrameIndex)];
    result = vkWaitForFences(device->device, 1, &fd->Fence, VK_TRUE, UINT64_MAX);
    if (result != VK_SUCCESS)
    {
        Logger::log("Couldn't wait on fences. Error code: ", ULOG_LOG_TYPE_ERROR, result);
        std::terminate();
    }

    result = vkResetFences(device->device, 1, &fd->Fence);
    if (result != VK_SUCCESS)
    {
        Logger::log("Couldn't reset fences. Error code: ", ULOG_LOG_TYPE_ERROR, result);
        std::terminate();
    }

    recordCommands(drawData, imageAcquired, renderComplete);
    present();
}

void UImGui::VKDraw::waitOnGPU() const noexcept
{
    device->device.waitIdle();
    device->queue.waitIdle();
}

void UImGui::VKDraw::recordCommands(void* drawData, VkSemaphore& imageAcquired, VkSemaphore& renderComplete) noexcept
{
    const ImGui_ImplVulkanH_Frame* fd = &window.Frames[window.FrameIndex];

    VkResult result = vkResetCommandPool(device->device, fd->CommandPool, 0);
    if (result != VK_SUCCESS)
    {
        Logger::log("Couldn't reset command pool. Error code: ", ULOG_LOG_TYPE_ERROR, result);
        std::terminate();
    }

    constexpr VkCommandBufferBeginInfo commandBufferBeginInfo =
    {
        .sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO,
        .flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT,
    };
    result = vkBeginCommandBuffer(fd->CommandBuffer, &commandBufferBeginInfo);
    if (result != VK_SUCCESS)
    {
        Logger::log("Couldn't open the command buffer. Error code: ", ULOG_LOG_TYPE_ERROR, result);
        std::terminate();
    }

    const VkRenderPassBeginInfo renderPassBeginInfo =
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
    vkCmdBeginRenderPass(fd->CommandBuffer, &renderPassBeginInfo, VK_SUBPASS_CONTENTS_INLINE);

    // Record dear imgui primitives into command buffer
    ImGui_ImplVulkan_RenderDrawData(CAST(ImDrawData*, drawData), fd->CommandBuffer);

    // Submit command buffer
    vkCmdEndRenderPass(fd->CommandBuffer);

    constexpr VkPipelineStageFlags waitPipelineStage = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
    const VkSubmitInfo submitInfo =
    {
        .sType = VK_STRUCTURE_TYPE_SUBMIT_INFO,
        .waitSemaphoreCount = 1,
        .pWaitSemaphores = &imageAcquired,
        .pWaitDstStageMask = &waitPipelineStage,
        .commandBufferCount = 1,
        .pCommandBuffers = &fd->CommandBuffer,
        .signalSemaphoreCount = 1,
        .pSignalSemaphores = &renderComplete,
    };

    result = vkEndCommandBuffer(fd->CommandBuffer);
    if (result != VK_SUCCESS)
    {
        Logger::log("Couldn't close the command buffer. Error code: ", ULOG_LOG_TYPE_ERROR, result);
        std::terminate();
    }
    result = vkQueueSubmit(device->queue, 1, &submitInfo, fd->Fence);
    if (result != VK_SUCCESS)
    {
        Logger::log("Couldn't submit to the queue. Error code: ", ULOG_LOG_TYPE_ERROR, result);
        std::terminate();
    }
}

void UImGui::VKDraw::present() noexcept
{
    // Present frame
    if (bRebuildSwapchain)
        return;

    VkSemaphore renderComplete = window.FrameSemaphores[CAST(int, window.SemaphoreIndex)].RenderCompleteSemaphore;
    const VkPresentInfoKHR info =
    {
        .sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR,
        .waitSemaphoreCount = 1,
        .pWaitSemaphores = &renderComplete,
        .swapchainCount = 1,
        .pSwapchains = &window.Swapchain,
        .pImageIndices = &window.FrameIndex
    };

    const VkResult result = vkQueuePresentKHR(device->queue, &info);
    if (result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR)
    {
        bRebuildSwapchain = true;
        ImGuiPreDraw();
        return;
    }
    window.SemaphoreIndex = (window.SemaphoreIndex + 1) % window.SemaphoreCount;
}
#endif
