#pragma once
#include <GenericRenderer/GenericRenderer.hpp>

#include <Renderer/Vulkan/Components/VKInstance.hpp>
#include <Renderer/Vulkan/Components/VKDevice.hpp>
#include <Renderer/Vulkan/Components/VKDraw.hpp>

namespace UImGui
{
    class UIMGUI_PUBLIC_API VulkanRenderer final : public GenericRenderer
    {
    public:
        VulkanRenderer() = default;

        virtual void parseCustomConfig(YAML::Node&) noexcept override;

        virtual void setupWindowIntegration() noexcept override;
        virtual void setupPostWindowCreation() noexcept override;

        virtual void init(RendererInternalMetadata& metadata) noexcept override;
        virtual void renderStart(double deltaTime) noexcept override;
        virtual void renderEnd(double deltaTime) noexcept override;
        virtual void destroy() noexcept override;

        virtual void ImGuiNewFrame() noexcept override;
        virtual void ImGuiShutdown() noexcept override;
        virtual void ImGuiInit() noexcept override;
        virtual void ImGuiRenderData() noexcept override;

        virtual void waitOnGPU() noexcept override;
    private:
        friend class WindowInternal;
        friend class VulkanTexture;

#ifndef __EMSCRIPTEN__
        VKInstance instance{};
        VKDevice device{ instance };
        VKDraw draw{ instance, device };
#endif
    };
}