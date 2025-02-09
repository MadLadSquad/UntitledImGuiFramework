#pragma once
#include <C/CDefines.h>

#ifdef __cplusplus
extern "C"
{
#endif
    /**
     * @brief Renderer data struct
     * @var bVulkan - Whether the application uses the vulkan renderer
     * @var bUsingVSync - Whether the application uses VSync(sync the application framerate with monitor refresh rate)
     * @var msaaSamples - Number of samples for MSAA antialiasing
     * @var bEnablePowerSavingMode - Whether to enable power saving(rendering with a reduce frame rate when the
     * application sits idle). Note: do not use for highly dynamic applications with plots or animations
     * @var idleFrameRate - The number of frames to render per second when idle
     */
    typedef struct UIMGUI_PUBLIC_API UImGui_RendererData
    {
        bool bVulkan;
        bool bUsingVSync;
        uint32_t msaaSamples;

        bool bEnablePowerSavingMode;
        float idleFrameRate;
    } UImGui_RendererData;
#ifdef __cplusplus
}
#endif