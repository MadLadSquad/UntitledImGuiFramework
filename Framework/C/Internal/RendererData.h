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
     * @var msaaSamples - Number of samples for MSAA anti-aliasing
     * @var bSampleRateShading - Apply anti-aliasing on shaders
     * @var sampleRateShadingMult - Shader anti-aliasing multiplier
     */
    typedef struct UIMGUI_PUBLIC_API UImGui_RendererData
    {
        bool bVulkan;
        bool bUsingVSync;
        uint32_t msaaSamples;
        bool bSampleRateShading;
        float sampleRateShadingMult;
    } UImGui_RendererData;
#ifdef __cplusplus
}
#endif