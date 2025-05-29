#pragma once
#include <Types.hpp>

namespace UImGui
{
    class RendererInternal;
    struct RendererInternalMetadata;

    class UIMGUI_PUBLIC_API GenericRenderer
    {
    public:
        GenericRenderer() noexcept = default;

        virtual void parseCustomConfig(YAML::Node& config) noexcept = 0;

        virtual void setupWindowIntegration() noexcept = 0;
        virtual void setupPostWindowCreation() noexcept = 0;

        virtual void init(RendererInternalMetadata& metadata) noexcept = 0;
        virtual void renderStart(double deltaTime) noexcept = 0;
        virtual void renderEnd(double deltaTime) noexcept = 0;
        virtual void destroy() noexcept = 0;

        virtual void ImGuiNewFrame() noexcept = 0;
        virtual void ImGuiShutdown() noexcept = 0;
        virtual void ImGuiInit() noexcept = 0;
        virtual void ImGuiRenderData() noexcept = 0;

        // Only called on Vulkan, because there we need to wait for resources to be used before freeing resources,
        // like textures
        virtual void waitOnGPU() noexcept = 0;

        virtual ~GenericRenderer() noexcept = default;
    };
}