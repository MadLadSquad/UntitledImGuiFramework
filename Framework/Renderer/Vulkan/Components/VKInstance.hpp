#pragma once
#ifndef __EMSCRIPTEN__
#include <vulkan/vulkan.hpp>
#include <vector>

#define VK_NOT_SUCCESS(x) x != vk::Result::eSuccess

namespace UImGui
{
    class VKInstance
    {
    public:
        VKInstance() = default;
        ~VKInstance() = default;

        void init() noexcept;
        void destroy() const noexcept;

        vk::Instance& data() noexcept;
    private:
        static bool checkInstanceExtensionsSupport(const std::vector<const char*>& extensions) noexcept;
        static bool checkValidationLayerSupport(const std::vector<const char*>& validationLayers) noexcept;

        vk::Instance instance;
        VkDebugReportCallbackEXT callback;

        static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugReportFlagsEXT flags, VkDebugReportObjectTypeEXT objType, uint64_t obj,
                                                            size_t location, int32_t code, const char* layerPrefix, const char* message, void* userData) noexcept;

        void createDebugCallback() noexcept;
    };
}
#endif