#pragma once
#include "GenericRenderer/GenericRenderer.hpp"

namespace UImGui
{
    class OpenGLRenderer final : public GenericInternalRenderer
    {
    public:
        OpenGLRenderer() noexcept = default;

        virtual void init(RendererInternal& renderer) noexcept override;
        virtual void renderStart(double deltaTime) noexcept override;
        virtual void renderEnd(double deltaTime) noexcept override;
        virtual void destroy() noexcept override;

        virtual void ImGuiNewFrame() noexcept override;
        virtual void ImGuiShutdown() noexcept override;
        virtual void ImGuiInit() noexcept override;
        virtual void ImGuiRenderData() noexcept override;

        virtual ~OpenGLRenderer() noexcept override = default;
    private:

    };
}