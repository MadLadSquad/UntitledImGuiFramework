#include "VKInstance.hpp"
#ifndef __EMSCRIPTEN__

#include "Core/Core.hpp"
#include "Generated/BuildDef.hpp"
#include "ThirdParty/glfw/include/GLFW/glfw3.h"
#include <cstring>

#define VK_LAYER_KHRONOS_VALIDATION "VK_LAYER_KHRONOS_validation"

void UImGui::VKInstance::init() noexcept
{
    constexpr const VkApplicationInfo applicationInfo
    {
        .sType = VK_STRUCTURE_TYPE_APPLICATION_INFO,
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

    if (!checkInstanceExtensionsSupport(instanceExtensions))
    {
        Logger::log("Couldn't load all required extensions!", UVK_LOG_TYPE_ERROR);
        std::terminate();
    }

    const VkInstanceCreateInfo instanceCreateInfo
    {
        .sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
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

    auto result = vkCreateInstance(&instanceCreateInfo, nullptr, &instance);
    if (result != VK_SUCCESS)
    {
        Logger::log("Couldn't create a Vulkan Instance! Error code: ", UVK_LOG_TYPE_ERROR, result);
        std::terminate();
    }
    createDebugCallback();
}

void UImGui::VKInstance::destroy() noexcept
{
#ifdef DEVELOPMENT
    auto destroyDebugCallback = (PFN_vkDestroyDebugReportCallbackEXT)vkGetInstanceProcAddr(instance,"vkDestroyDebugReportCallbackEXT");
    destroyDebugCallback(instance, callback, nullptr);
#endif
    vkDestroyInstance(instance, nullptr);
}

VkInstance& UImGui::VKInstance::data() noexcept
{
    return instance;
}

bool UImGui::VKInstance::checkInstanceExtensionsSupport(const std::vector<const char*>& extensions) noexcept
{
    uint32_t extensionsNum = 0;
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionsNum, nullptr);

    std::vector<VkExtensionProperties> extensionProperties(extensionsNum);
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionsNum, extensionProperties.data());

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
    uint32_t layerCount;
    vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

    std::vector<VkLayerProperties> availableLayers(layerCount);
    vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

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
    constexpr const VkDebugReportCallbackCreateInfoEXT callbackCreateInfoExt
    {
        .sType = VK_STRUCTURE_TYPE_DEBUG_REPORT_CALLBACK_CREATE_INFO_EXT,
        .flags = VK_DEBUG_REPORT_ERROR_BIT_EXT | VK_DEBUG_REPORT_WARNING_BIT_EXT,
        .pfnCallback = debugCallback
    };

    auto createDebugReportCallback = (PFN_vkCreateDebugReportCallbackEXT)vkGetInstanceProcAddr(instance, "vkCreateDebugReportCallbackEXT");
    auto result = createDebugReportCallback(instance, &callbackCreateInfoExt, nullptr, &callback);
    if (result != VK_SUCCESS)
    {
        Logger::log("Failed to create a debug callback! Error code: ", UVK_LOG_TYPE_ERROR, result);
        std::terminate();
    }
#endif
}

VkBool32 UImGui::VKInstance::debugCallback(VkDebugReportFlagsEXT flags, VkDebugReportObjectTypeEXT objType, uint64_t obj,
                                           size_t location, int32_t code, const char* layerPrefix, const char* message, void* userData) noexcept
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