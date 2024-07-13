#pragma once
#include <GenericRenderer/GenericRenderer.hpp>

#include <Renderer/Vulkan/Components/VKInstance.hpp>
#include <Renderer/Vulkan/Components/VKDevice.hpp>

namespace UImGui
{
    class VulkanRenderer final : public GenericInternalRenderer
    {
    public:
        VulkanRenderer() = default;

        virtual void init(RendererInternal& renderer) noexcept override;
        virtual void renderStart(double deltaTime) noexcept override;
        virtual void renderEnd(double deltaTime) noexcept override;
        virtual void destroy() noexcept override;

        virtual void ImGuiNewFrame() noexcept override;
        virtual void ImGuiShutdown() noexcept override;
        virtual void ImGuiInit() noexcept override;
        virtual void ImGuiRenderData() noexcept override;
    private:
#ifndef __EMSCRIPTEN__
        VKInstance instance{};
        VKDevice device{ instance };
#endif
    };
}