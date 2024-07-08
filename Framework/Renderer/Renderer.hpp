#pragma once
#include <Core/Defines.hpp>
#include <Core/Types.hpp>

// C API, contains the renderer data header, since it is shared between the 2 APIs
#include <C/Internal/RendererData.h>

// Renderers
#include <OpenGL/OpenGLRenderer.hpp>
#include <Vulkan/VulkanRenderer.hpp>
#include <WebGPU/WebGPURenderer.hpp>

namespace UImGui
{
    typedef UImGui_RendererData RendererData;

    class UIMGUI_PUBLIC_API RendererInternal
    {
    public:
        RendererInternal() = default;

        void start();
        void stop() const noexcept;
    private:
        friend class Renderer;
        friend class OpenGLRenderer;
        friend class WebGPURenderer;
        friend class Texture;
        friend class WebGPUTexture;

        static void tick(void* rendererInstance) noexcept;

        OpenGLRenderer opengl{};
        VulkanRenderer vulkan{};
        WebGPURenderer wgpu{};

        GenericInternalRenderer* renderer = nullptr;

        FString vendorString;
        FString apiVersion;
        FString driverVersion;
        FString gpuName;

        void loadConfig() noexcept;
        void saveConfig() const noexcept;

        double lastTime = 0.0f;

        RendererData data =
        {
            .bVulkan = false,
            .bUsingVSync = true,
            .msaaSamples = 8,
            .bSampleRateShading = false,
            .sampleRateShadingMult = 0.0f,
        };
    };

}