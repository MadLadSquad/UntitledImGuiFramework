#pragma once

namespace UImGui
{
    class RendererInternal;

    class GenericInternalRenderer
    {
    public:
        GenericInternalRenderer() = default;

        virtual void init(RendererInternal& renderer) noexcept = 0;
        virtual void renderStart(double deltaTime) noexcept = 0;
        virtual void renderEnd(double deltaTime) noexcept = 0;
        virtual void destroy() noexcept = 0;

        virtual void ImGuiNewFrame() noexcept = 0;
        virtual void ImGuiShutdown() noexcept = 0;
        virtual void ImGuiInit() noexcept = 0;
        virtual void ImGuiRenderData() noexcept = 0;
    };

}