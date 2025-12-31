#pragma once
#include <Types.hpp>
#include <C/Renderer/CGenericRenderer.h>

namespace UImGui
{
    class RendererInternal;
    struct RendererInternalMetadata;

    typedef UImGui_RendererAPITypeHint RendererAPITypeHint;

    class UIMGUI_PUBLIC_API GenericRenderer
    {
    public:
        GenericRenderer() noexcept = default;

        virtual void parseCustomConfig(const ryml::ConstNodeRef& config) noexcept = 0;
        virtual void saveCustomConfig(ryml::NodeRef& config) noexcept = 0;

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

        RendererAPITypeHint type = UIMGUI_RENDERER_API_TYPE_HINT_OTHER;
    };
}