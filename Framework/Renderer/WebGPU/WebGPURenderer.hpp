#pragma once
#include <GenericRenderer/GenericRenderer.hpp>
#ifdef __EMSCRIPTEN__
    #include <webgpu/webgpu.h>
    #include <webgpu/webgpu_cpp.h>
#endif

namespace UImGui
{
    class UIMGUI_PUBLIC_API WebGPURenderer final : public GenericRenderer
    {
    public:
        WebGPURenderer() noexcept = default;

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

        WGPUTextureDescriptor multisampledTextureDescriptor{};
        WGPUTexture multisampledTexture = nullptr;
        WGPUTextureView multisampledTextureView = nullptr;
        uint32_t multisampledTextureWidth = 800;
        uint32_t multisampledTextureHeight = 600;

        void createSwapchain() noexcept;
#endif
    };
}