#pragma once
#include <C/CDefines.h>
#include <C/CTypes.h>

#ifdef __cplusplus
extern "C"
{
#endif
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