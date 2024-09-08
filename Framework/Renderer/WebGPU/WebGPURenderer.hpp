#pragma once
#include <GenericRenderer/GenericRenderer.hpp>
#ifdef __EMSCRIPTEN__
    #include <webgpu/webgpu.h>
    #include <webgpu/webgpu_cpp.h>
#endif

namespace UImGui
{
    class UIMGUI_PUBLIC_API WebGPURenderer final : public GenericInternalRenderer
    {
    public:
        WebGPURenderer() noexcept = default;

        virtual void init(RendererInternal& renderer) noexcept override;
        virtual void renderStart(double deltaTime) noexcept override;
        virtual void renderEnd(double deltaTime) noexcept override;
        virtual void destroy() noexcept override;

        virtual void ImGuiNewFrame() noexcept override;
        virtual void ImGuiShutdown() noexcept override;
        virtual void ImGuiInit() noexcept override;
        virtual void ImGuiRenderData() noexcept override;

        virtual ~WebGPURenderer() noexcept = default;
    private:
        friend class WebGPUTexture;
#ifdef __EMSCRIPTEN__
        WGPUInstance instance = nullptr;
        WGPUDevice device = nullptr;
        WGPUSurface surface = nullptr;
        WGPUSwapChain swapchain = nullptr;
        WGPUTextureFormat preferredFormat = WGPUTextureFormat_RGBA8Unorm;
        uint32_t swapchainWidth = 800;
        uint32_t swapchainHeight = 600;

        void createSwapchain() noexcept;
#endif
    };
}