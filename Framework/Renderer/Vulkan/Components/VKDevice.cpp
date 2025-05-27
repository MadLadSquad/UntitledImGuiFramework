#include "VKDevice.hpp"
#ifndef __EMSCRIPTEN__
#include <Interfaces/RendererInterface.hpp>
#include <Renderer.hpp>
#include <Defines.hpp>

#define VK_KHR_PORTABILITY_SUBSET_NAME "VK_KHR_portability_subset"

inline UImGui::TVector<const char*> deviceExtensions =
{
    VK_KHR_SWAPCHAIN_EXTENSION_NAME,
#if defined(VK_KHR_PORTABILITY_ENUMERATION_EXTENSION_NAME) && defined(__APPLE__)
    VK_KHR_PORTABILITY_SUBSET_NAME
#endif
};

UImGui::VKDevice::VKDevice(VKInstance& inst) noexcept
{
    instance = &inst;
}

void UImGui::VKDevice::create(RendererInternalMetadata& metadata) noexcept
{
    surface.create(*instance);
    createPhysicalDevice();
    auto queueFamilyList = physicalDevice.getQueueFamilyProperties();

    const auto properties = physicalDevice.getProperties();
    metadata.gpuName = properties.deviceName.data();
    metadata.apiVersion = std::to_string(VK_VERSION_MAJOR(properties.apiVersion)) + "."
                        + std::to_string(VK_VERSION_MINOR(properties.apiVersion)) + "."
                        + std::to_string(VK_VERSION_PATCH(properties.apiVersion));
    metadata.driverVersion = std::to_string(VK_VERSION_MAJOR(properties.driverVersion)) + "."
                           + std::to_string(VK_VERSION_MINOR(properties.driverVersion)) + "."
                           + std::to_string(VK_VERSION_PATCH(properties.driverVersion));
    metadata.vendorString = properties.deviceName.data();

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
    constexpr vk::PhysicalDeviceFeatures deviceFeatures =
    {
        .sampleRateShading = VK_FALSE,
        .samplerAnisotropy = VK_TRUE,           // We're using Anisotropy
    };

    const uint32_t queueInfoCount = indices.graphicsFamily == indices.presentationFamily ? 1 : 2;
    const vk::DeviceCreateInfo deviceCreateInfo =
    {
        .pNext = nullptr,
        .queueCreateInfoCount = queueInfoCount,
        .pQueueCreateInfos = createInfos,
        .enabledExtensionCount = static_cast<uint32_t>(deviceExtensions.size()),
        .ppEnabledExtensionNames = deviceExtensions.data(),
        .pEnabledFeatures = &deviceFeatures
    };

    // Create the logical device
    const auto result = physicalDevice.createDevice(&deviceCreateInfo, nullptr, &device);
    if (VK_NOT_SUCCESS(result))
    {
        Logger::log("Failed to create a logical device! Error code: ", ULOG_LOG_TYPE_ERROR, result);
        std::terminate();
    }
    // Get the queues
    queue = device.getQueue(indices.graphicsFamily, 0);
    presentationQueue = device.getQueue(indices.presentationFamily, 0);

    Logger::log("Created Vulkan logical device!", ULOG_LOG_TYPE_NOTE);

    descriptorPools.allocate();
}

const vk::Device& UImGui::VKDevice::get() const noexcept
{
    return device;
}

void UImGui::VKDevice::destroy() const noexcept
{
    descriptorPools.destroy();
    device.destroy();
    // One would usually destroy the surface here, but imgui takes care of it.
}

void UImGui::VKDevice::createPhysicalDevice() noexcept
{
    const auto devices = instance->data().enumeratePhysicalDevices();
    if (devices.empty())
    {
        Logger::log("Could not find any graphics devices on this system!", ULOG_LOG_TYPE_ERROR);
        std::terminate();
    }

    bool bFoundDiscreteDevice = false;
    uint32_t largestMemorySizeFoundIndex = 0;
    uint64_t largestMemorySize = 0;
    QueueFamilyIndices lastSavedIndex = { 0, 0 };

    for (size_t i = 0; i < devices.size(); i++)
    {
        // If it is not discrete skip this iteration
        if (devices[i].getProperties().deviceType == vk::PhysicalDeviceType::eDiscreteGpu)
            bFoundDiscreteDevice = true;
        else
            continue;

        uint64_t size = 0;

        // Set the size of the memory for the given GPU
        for (const auto& a : devices[i].getMemoryProperties().memoryHeaps)
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

        // Select the queue family
        for (int j = 0; j < queueFamilyList.size(); j++)
        {
            const auto& a = queueFamilyList[j];
            if (a.queueCount > 0 && a.queueFlags & vk::QueueFlagBits::eGraphics)
            {
                families.graphicsFamily = j;
                vk::Bool32 bSupportsPresentation = false;

                const auto result = devices[i].getSurfaceSupportKHR(j, surface.get(), &bSupportsPresentation);
                if (bSupportsPresentation && result == vk::Result::eSuccess)
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

        if (!surface.getPhysicalDeviceSurfaceSupport(devices[i], indices))
            continue;

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

    Logger::log("Loaded Vulkan device - ", ULOG_LOG_TYPE_NOTE, deviceProperties.deviceName);
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
