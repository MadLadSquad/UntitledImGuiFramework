#pragma once
#include <GenericRenderer/GenericRenderer.hpp>
#ifdef __EMSCRIPTEN__
    #include <emscripten/html5.h>
    #include <webgpu/webgpu.h>
    #include <webgpu/webgpu_cpp.h>
#endif

namespace UImGui
{
    class UIMGUI_PUBLIC_API WebGPURenderer : public GenericRenderer
    {
    public:
        WebGPURenderer() noexcept;

        void parseCustomConfig(const ryml::ConstNodeRef& config) noexcept override;
        void saveCustomConfig(ryml::NodeRef& config) noexcept override;

        void setupWindowIntegration() noexcept override;
        void setupPostWindowCreation() noexcept override;

        void init(RendererInternalMetadata& metadata) noexcept override;

        void renderStart(double deltaTime) noexcept override;
        void renderEnd(double deltaTime) noexcept override;

        void destroy() noexcept override;

        void ImGuiNewFrame() noexcept override;
        void ImGuiShutdown() noexcept override;
        void ImGuiInit() noexcept override;
        void ImGuiRenderData() noexcept override;

        void waitOnGPU() noexcept override;
    private:
#ifdef __EMSCRIPTEN__
        friend class WebGPUTexture;

        WGPUInstance instance = nullptr;
        WGPUDevice device = nullptr;
        WGPUSurface surface = nullptr;
        WGPUQueue queue = nullptr;
        WGPUSurfaceConfiguration surfaceConfiguration = {};

        WGPUSurfaceTexture surfaceTexture;

        WGPUTexture msaaTexture = nullptr;
        WGPUTextureView msaaTextureView = nullptr;

        uint32_t width = 800;
        uint32_t height = 600;
#endif
        FString gpuName{};
        FString vendorString{};

        void resizeSurface(uint32_t width, uint32_t height) noexcept;
    };
}