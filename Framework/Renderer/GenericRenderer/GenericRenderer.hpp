#pragma once
#include <Types.hpp>

namespace UImGui
{
    class RendererInternal;

    class GenericInternalRenderer
    {
    public:
        GenericInternalRenderer() noexcept = default;

        virtual void init(RendererInternal& renderer) noexcept = 0;
        virtual void renderStart(double deltaTime) noexcept = 0;
        virtual void renderEnd(double deltaTime) noexcept = 0;
        virtual void destroy() noexcept = 0;

        virtual void ImGuiNewFrame() noexcept = 0;
        virtual void ImGuiShutdown() noexcept = 0;
        virtual void ImGuiInit() noexcept = 0;
        virtual void ImGuiRenderData() noexcept = 0;

        virtual void loadTexture(intptr_t id, uint32_t x, uint32_t y, uint32_t depth, const void* data) noexcept = 0;
        virtual void loadTextureImGui(intptr_t id, uint32_t x, uint32_t y, uint32_t depth, const void* data) noexcept = 0;
        virtual void useTexture(intptr_t id) noexcept = 0;
        virtual void clearTexture(intptr_t id) noexcept = 0;

        virtual ~GenericInternalRenderer() noexcept = default;
    };

}