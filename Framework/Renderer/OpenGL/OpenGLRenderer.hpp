#pragma once
#include "GenericRenderer/GenericRenderer.hpp"

namespace UImGui
{
    class UIMGUI_PUBLIC_API OpenGLRenderer final : public GenericRenderer
    {
    public:
        OpenGLRenderer() noexcept;

        virtual void parseCustomConfig(const ryml::ConstNodeRef&) noexcept override;
        virtual void saveCustomConfig(ryml::NodeRef& config) noexcept override;

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

        virtual ~OpenGLRenderer() noexcept override = default;
    private:

    };
}