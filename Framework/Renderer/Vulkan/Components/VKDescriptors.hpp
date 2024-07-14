#pragma once
#ifndef __EMSCRIPTEN__
#include "VKInstance.hpp"

namespace UImGui
{
    class VKDevice;
    class VKDescriptorPools
    {
    public:
        VKDescriptorPools() noexcept = default;
        explicit VKDescriptorPools(VKDevice& dev) noexcept;

        void allocate() noexcept;
        void destroy() const noexcept;
    private:
        friend class VKDraw;

        VKDevice* device = nullptr;
        vk::DescriptorPool pool{};
    };
}
#endif