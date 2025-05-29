#pragma once
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
    typedef UImGui_RendererType RendererType;

    struct UIMGUI_PUBLIC_API RendererInternalMetadata
    {
        FString vendorString;
        FString apiVersion;
        FString driverVersion;
        FString gpuName;
    };

    class UIMGUI_PUBLIC_API RendererInternal
    {
    public:
        RendererInternal() = default;

        void start();
        void stop() const noexcept;
    private:
        friend class Renderer;
        friend class RendererUtils;

        static void tick(void* rendererInstance) noexcept;

        void loadConfig() noexcept;
        void saveConfig() const noexcept;

        OpenGLRenderer opengl{};
#ifdef __EMSCRIPTEN__
        WebGPURenderer wgpu{};
#else
        VulkanRenderer vulkan{};
#endif
        GenericRenderer* custom = nullptr;

        GenericRenderer* renderers[UIMGUI_RENDERER_TYPE_COUNT] =
        {
            &opengl,
#ifdef __EMSCRIPTEN__
            &wgpu,
#else
            &vulkan,
#endif
            custom
        };

        GenericRenderer* renderer = nullptr;

        RendererInternalMetadata metadata;
        RendererData data =
        {
            .rendererType = UIMGUI_RENDERER_TYPE_OPENGL,
            .bUsingVSync = true,
            .msaaSamples = 1,
            .bEnablePowerSavingMode = false,
            .idleFrameRate = 9.0f
        };

        YAML::Node customConfig;

        double lastTime = 0.0f;
        bool bIdling = false;
    };

}