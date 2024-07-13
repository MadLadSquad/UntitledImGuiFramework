#include "VKInstance.hpp"
#ifndef __EMSCRIPTEN__

#include "Core/Core.hpp"
#include "Generated/BuildDef.hpp"
#include "ThirdParty/glfw/include/GLFW/glfw3.h"
#include <cstring>

#define VK_LAYER_KHRONOS_VALIDATION "VK_LAYER_KHRONOS_validation"
#define VK_DESTROY_DEBUG_REPORT_CALLBACK_EXT_NAME "vkDestroyDebugReportCallbackEXT"
#define VK_CREATE_DEBUG_REPORT_CALLBACK_EXT_NAME "vkCreateDebugReportCallbackEXT"

void UImGui::VKInstance::init() noexcept
{
    constexpr vk::ApplicationInfo applicationInfo
    {
        .pApplicationName = "UntitledImGuiFramework",
        .applicationVersion = VK_MAKE_VERSION(1, 0, 0),
        .pEngineName = "UntitledImGuiFramework",
        .engineVersion = VK_MAKE_VERSION(1, 0, 0),
        .apiVersion = VK_API_VERSION_1_3
    };

    uint32_t glfwExtensionCount = 0;
    const char** glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

    std::vector<const char*> instanceExtensions;
    std::vector<const char*> instanceLayers;

    instanceExtensions.resize(glfwExtensionCount);
    for (size_t i = 0; i < glfwExtensionCount; i++)
        instanceExtensions[i] = glfwExtensions[i];

#ifdef DEVELOPMENT
    instanceExtensions.push_back(VK_EXT_DEBUG_REPORT_EXTENSION_NAME);
    instanceLayers.push_back(VK_LAYER_KHRONOS_VALIDATION);
#endif

    // Fixes inability to create an instance on macOS
#ifdef VK_KHR_PORTABILITY_ENUMERATION_EXTENSION_NAME
    instanceExtensions.push_back(VK_KHR_PORTABILITY_ENUMERATION_EXTENSION_NAME);
#endif

    if (!checkInstanceExtensionsSupport(instanceExtensions))
    {
        Logger::log("Couldn't load all required extensions!", UVK_LOG_TYPE_ERROR);
        std::terminate();
    }

    const vk::InstanceCreateInfo instanceCreateInfo
    {
#ifdef VK_KHR_PORTABILITY_ENUMERATION_EXTENSION_NAME
        .flags = vk::InstanceCreateFlagBits::eEnumeratePortabilityKHR,
#endif
        .pApplicationInfo = &applicationInfo,
        .enabledLayerCount = static_cast<uint32_t>(instanceLayers.size()),
        .ppEnabledLayerNames = instanceLayers.data(),
        .enabledExtensionCount = static_cast<uint32_t>(instanceExtensions.size()),
        .ppEnabledExtensionNames = instanceExtensions.data()
    };

    if (!checkValidationLayerSupport(instanceLayers))
    {
        Logger::log("Couldn't create validation layers!", UVK_LOG_TYPE_ERROR);
        std::terminate();
    }

    auto result = createInstance(&instanceCreateInfo, nullptr, &instance);
    if (VK_NOT_SUCCESS(result))
    {
        Logger::log("Couldn't create a Vulkan Instance! Error code: ", UVK_LOG_TYPE_ERROR, result);
        std::terminate();
    }
    createDebugCallback();
    Logger::log("Created a Vulkan instance successfully!", UVK_LOG_TYPE_SUCCESS);
}

void UImGui::VKInstance::destroy() const noexcept
{
#ifdef DEVELOPMENT
    const auto destroyDebugCallback = reinterpret_cast<PFN_vkDestroyDebugReportCallbackEXT>(instance.getProcAddr(VK_DESTROY_DEBUG_REPORT_CALLBACK_EXT_NAME));
    destroyDebugCallback(instance, callback, nullptr);
#endif
    instance.destroy();
}

vk::Instance& UImGui::VKInstance::data() noexcept
{
    return instance;
}

bool UImGui::VKInstance::checkInstanceExtensionsSupport(const std::vector<const char*>& extensions) noexcept
{
    auto extensionProperties = vk::enumerateInstanceExtensionProperties(nullptr);
    for (auto& a : extensions)
    {
        bool bHasExtension = false;

        for (auto& f : extensionProperties)
        {
            if (strcmp(a, f.extensionName) == 0)
            {
                bHasExtension = true;
                break;
            }
        }
        if (!bHasExtension)
            return false;
    }
    return true;
}

bool UImGui::VKInstance::checkValidationLayerSupport(const std::vector<const char*>& validationLayers) noexcept
{
    auto availableLayers = vk::enumerateInstanceLayerProperties();
    for (auto& a : validationLayers)
    {
        bool bHasLayer = false;
        for (auto& f : availableLayers)
        {
            if (strcmp(a, f.layerName) == 0)
            {
                bHasLayer = true;
                break;
            }
        }
        if (!bHasLayer)
            return false;
    }
    return true;
}

void UImGui::VKInstance::createDebugCallback() noexcept
{
#ifdef DEVELOPMENT
    constexpr VkDebugReportCallbackCreateInfoEXT callbackCreateInfoExt
    {
        .sType = VK_STRUCTURE_TYPE_DEBUG_REPORT_CALLBACK_CREATE_INFO_EXT,
        .flags = VK_DEBUG_REPORT_ERROR_BIT_EXT | VK_DEBUG_REPORT_WARNING_BIT_EXT,
        .pfnCallback = debugCallback
    };
    const auto createDebugReportCallback = reinterpret_cast<PFN_vkCreateDebugReportCallbackEXT>(instance.getProcAddr(VK_CREATE_DEBUG_REPORT_CALLBACK_EXT_NAME));
    const auto result = createDebugReportCallback(instance, &callbackCreateInfoExt, nullptr, &callback);
    if (result != VK_SUCCESS)
    {
        Logger::log("Failed to create a debug callback! Error code: ", UVK_LOG_TYPE_ERROR, result);
        std::terminate();
    }
#endif
}

VkBool32 UImGui::VKInstance::debugCallback(const VkDebugReportFlagsEXT flags, const VkDebugReportObjectTypeEXT objType, const uint64_t obj,
                                           const size_t location, const int32_t code, const char* layerPrefix, const char* message, void* userData) noexcept
{
    UNUSED(objType); UNUSED(obj); UNUSED(location); UNUSED(code); UNUSED(layerPrefix); UNUSED(userData);

    if (flags & VK_DEBUG_REPORT_ERROR_BIT_EXT)
    {
        Logger::log("Vulkan Validation error: ", UVK_LOG_TYPE_ERROR, message);
        return VK_TRUE;
    }

    if (flags & VK_DEBUG_REPORT_WARNING_BIT_EXT)
    {
        Logger::log("Vulkan Validation warning: ", UVK_LOG_TYPE_WARNING, message);
        return VK_TRUE;
    }

    if (flags & VK_DEBUG_REPORT_INFORMATION_BIT_EXT)
    {
        Logger::log("Vulkan Validation info: ", UVK_LOG_TYPE_NOTE, message);
        return VK_TRUE;
    }

    return VK_FALSE;
}
#endif