#pragma once
#include <C/CDefines.h>
#include <C/CTypes.h>

#ifdef __cplusplus
extern "C"
{
#endif
    struct UIMGUI_PUBLIC_API UImGui_RendererData_I
    {
        bool bVulkan;
        bool bUsingVSync;
        uint32_t msaaSamples;
        bool bSampleRateShading;
        float sampleRateShadingMult;
    };
    typedef struct UImGui_RendererData_I UImGui_RendererData;
#ifdef __cplusplus
}
#endif