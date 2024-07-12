#include "VKDevice.hpp"
#ifndef __EMSCRIPTEN__
#include <Interfaces/RendererInterface.hpp>

constexpr std::array<const char*, 2> deviceExtensions =
{
    VK_KHR_SWAPCHAIN_EXTENSION_NAME,
    VK_EXT_CUSTOM_BORDER_COLOR_EXTENSION_NAME
};

void UImGui::VKDevice::createDevice() noexcept
{
    createPhysicalDevice();
    auto queueFamilyList = physicalDevice.getQueueFamilyProperties();

    constexpr float priority = 1.0f;

    const vk::DeviceQueueCreateInfo createInfos[] =
    {
        {
            .queueFamilyIndex = static_cast<uint32_t>(indices.graphicsFamily),
            .queueCount = 1,
            .pQueuePriorities = &priority
        },
        {
            .queueFamilyIndex = static_cast<uint32_t>(indices.presentationFamily),
            .queueCount = 1,
            .pQueuePriorities = &priority
        }
    };

    // Enable physical device features
    const vk::PhysicalDeviceFeatures deviceFeatures =
    {
        .sampleRateShading = static_cast<VkBool32>(Renderer::data().bSampleRateShading),
        .samplerAnisotropy = VK_TRUE,           // We're using Anisotropy
    };
    constexpr vk::PhysicalDeviceCustomBorderColorFeaturesEXT physicalDeviceCustomBorderColorFeaturesExt
    {
        .customBorderColors = VK_TRUE,                                                  // Enable custom texture border colours
        .customBorderColorWithoutFormat = VK_FALSE,                                     // Require format for the custom border colours
    };

    const uint32_t queueInfoCount = indices.graphicsFamily == indices.presentationFamily ? 1 : 2;

    const vk::DeviceCreateInfo deviceCreateInfo =
    {
        //.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,
        .pNext = &physicalDeviceCustomBorderColorFeaturesExt,   // Set the pNext pointer to point to the custom border colours struct
        .queueCreateInfoCount = queueInfoCount,
        .pQueueCreateInfos = createInfos,
        .enabledExtensionCount = deviceExtensions.size(),
        .ppEnabledExtensionNames = deviceExtensions.data(),
        .pEnabledFeatures = &deviceFeatures
    };

    // Create the logical device
    const auto result = physicalDevice.createDevice(&deviceCreateInfo, nullptr, &device);
    if (VK_NOT_SUCCESS(result))
    {
        Logger::log("Failed to create a logical device! Error code: ", UVK_LOG_TYPE_ERROR, result);
        std::terminate();
    }
    // Get the queues
    queue = device.getQueue(indices.graphicsFamily, 0);
    presentationQueue = device.getQueue(indices.presentationFamily, 0);
}

void UImGui::VKDevice::destroyDevice() const noexcept
{
    device.destroy();
}

void UImGui::VKDevice::createPhysicalDevice() noexcept
{
    const auto devices = instance->data().enumeratePhysicalDevices();
    if (devices.empty())
    {
        Logger::log("Could not find any graphics devices on this system!", UVK_LOG_TYPE_ERROR);
        std::terminate();
    }

    bool bFoundDiscreteDevice = false;
    uint32_t largestMemorySizeFoundIndex = 0;
    uint64_t largestMemorySize = 0;
    QueueFamilyIndices lastSavedIndex = {};

    for (size_t i = 0; i < devices.size(); i++)
    {
        // If it is not discrete skip this iteration
        if (devices[i].getProperties().deviceType == vk::PhysicalDeviceType::eDiscreteGpu)
            bFoundDiscreteDevice = true;
        else
            continue;

        uint64_t size = 0;

        // Set the size of the memory for the given GPU
        for (auto& a : devices[i].getMemoryProperties().memoryHeaps)
        {
            if (a.flags & vk::MemoryHeapFlagBits::eDeviceLocal)
            {
                size += a.size;
                break;
            }
        }

        QueueFamilyIndices families = {};

        // Get the queue families
        auto queueFamilyList = devices[i].getQueueFamilyProperties();

        int j = 0;
        // Select the queue family
        for (; j < queueFamilyList.size(); j++)
        {
            const auto& a = queueFamilyList[j];
            if (a.queueCount > 0 && a.queueFlags & vk::QueueFlagBits::eGraphics)
            {
                families.graphicsFamily = j;
                vk::Bool32 bSupportsPresentation = false;
                // TODO: Implement
                //physicalDevice.getSurfaceSupportKHR(j, swapchain.surface, &bSupportsPresentation);

                if (bSupportsPresentation)
                    families.presentationFamily = j;
                break;
            }
        }

        // If invalid skip
        if (!families.valid())
            continue;

        // Get the list of device extensions
        auto extensions = devices[i].enumerateDeviceExtensionProperties();
        if (extensions.empty())
            continue;

        // Iterate the list and make sure the device supports all
        for (const auto& a : deviceExtensions)
        {
            bool bHasExtension = false;
            for (const auto& f : extensions)
            {
                if (strcmp(a, f.extensionName) == 0)
                {
                    bHasExtension = true;
                    break;
                }
            }
            // If it doesn't have the extension, skip
            if (!bHasExtension)
                goto continue_to_other_device_in_list;
        }

        // TODO: Implement
        //if (!swapchain.getSwapchainDetails(devices[i], families))
        //    continue;

        // If the size is larger set the index of the device to this since it's the best one so far
        if (size > largestMemorySize)
        {
            largestMemorySize = size;
            largestMemorySizeFoundIndex = i;
            lastSavedIndex = families;
        }
continue_to_other_device_in_list:;
    }

    // Set device[0] if we couldn't find it lol
    if (!bFoundDiscreteDevice || largestMemorySizeFoundIndex == 0)
        physicalDevice = devices[0];
    else
        physicalDevice = devices[largestMemorySizeFoundIndex];

    // Set the device properties variable real quick
    deviceProperties = physicalDevice.getProperties();
    setMSAASamples();
    indices = lastSavedIndex;

    Logger::log("Loaded Vulkan device ", UVK_LOG_TYPE_SUCCESS, deviceProperties.deviceName);
}

void UImGui::VKDevice::setMSAASamples() const noexcept
{
    // Set the MSAA sample level given the hardware supports it and is defined in the config file
    auto& samples = Renderer::data().msaaSamples;
    
    const vk::SampleCountFlags counts = deviceProperties.limits.framebufferColorSampleCounts & deviceProperties.limits.framebufferDepthSampleCounts;
    if ((counts & vk::SampleCountFlagBits::e64) && samples > 32)
        samples = FCAST(uint32_t, vk::SampleCountFlagBits::e64);
    else if ((counts & vk::SampleCountFlagBits::e32) && samples > 16)
        samples = FCAST(uint32_t, vk::SampleCountFlagBits::e32);
    else if ((counts & vk::SampleCountFlagBits::e16) && samples > 8)
        samples = FCAST(uint32_t, vk::SampleCountFlagBits::e16);
    else if ((counts & vk::SampleCountFlagBits::e8) && samples > 4)
        samples = FCAST(uint32_t, vk::SampleCountFlagBits::e8);
    else if ((counts & vk::SampleCountFlagBits::e4) && samples > 2)
        samples = FCAST(uint32_t, vk::SampleCountFlagBits::e4);
    else if ((counts & vk::SampleCountFlagBits::e2) && samples > 1)
        samples = FCAST(uint32_t, vk::SampleCountFlagBits::e2);
    else if ((counts & vk::SampleCountFlagBits::e1) && samples >= 0)
        samples = FCAST(uint32_t, vk::SampleCountFlagBits::e1);
}

#endif
