#pragma once
#include <C/CDefines.h>

#ifdef __cplusplus
extern "C"
{
#endif
    // Keep in sync with the strings in Renderer.cpp
    typedef enum UImGui_RendererType
    {
        UIMGUI_RENDERER_TYPE_OPENGL,
        UIMGUI_RENDERER_TYPE_VULKAN_WEBGPU,
        UIMGUI_RENDERER_TYPE_CUSTOM,
        UIMGUI_RENDERER_TYPE_COUNT,
        UIMGUI_RENDERER_TYPE_ALT_NAMES_COUNT
    } UImGui_RendererType;

    /**
     * @brief Renderer data struct
     * @var rendererType - The current selected renderer
     * @var bUsingVSync - Whether the application uses VSync(sync the application framerate with monitor refresh rate)
     * @var msaaSamples - Number of samples for MSAA antialiasing
     * @var bEnablePowerSavingMode - Whether to enable power saving(rendering with a reduce frame rate when the
     * application sits idle). Note: do not use for highly dynamic applications with plots or animations
     * @var idleFrameRate - The number of frames to render per second when idle
     */
    typedef struct UIMGUI_PUBLIC_API UImGui_RendererData
    {
        UImGui_RendererType rendererType;
        bool bUsingVSync;
        uint32_t msaaSamples;

        bool bEnablePowerSavingMode;
        float idleFrameRate;
    } UImGui_RendererData;
#ifdef __cplusplus
}
#endif