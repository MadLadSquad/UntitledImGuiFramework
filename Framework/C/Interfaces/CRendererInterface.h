#pragma once
#include <C/CTypes.h>
#include <C/CDefines.h>
#include <C/Window/RendererData.h>

#ifdef __cplusplus
extern "C"
{
#endif
    // Event Safety - Any time
    UIMGUI_PUBLIC_API UImGui_RendererData* UImGui_Renderer_data();
    // Event Safety - Any time
    UIMGUI_PUBLIC_API void UImGui_Renderer_saveSettings();

    // Event Safety - begin, post-begin
    UIMGUI_PUBLIC_API UImGui_String UImGui_Renderer_getVendorString();
    // Event Safety - begin, post-begin
    UIMGUI_PUBLIC_API UImGui_String UImGui_Renderer_getAPIVersion();
    // Event Safety - begin, post-begin
    UIMGUI_PUBLIC_API UImGui_String UImGui_Renderer_getGPUName();
    // Event Safety - begin, post-begin
    UIMGUI_PUBLIC_API UImGui_String UImGui_Renderer_getDriverVersion();

    // Event Safety - post-startup
    UIMGUI_PUBLIC_API void UImGui_RendererInternalMetadata_setVendorString(UImGui_String str);
    // Event Safety - post-startup
    UIMGUI_PUBLIC_API void UImGui_RendererInternalMetadata_setApiVersion(UImGui_String str);
    // Event Safety - post-startup
    UIMGUI_PUBLIC_API void UImGui_RendererInternalMetadata_setDriverVersion(UImGui_String str);
    // Event Safety - post-startup
    UIMGUI_PUBLIC_API void UImGui_RendererInternalMetadata_setGPUName(UImGui_String str);

    // Event Safety - begin, post-begin
    UIMGUI_PUBLIC_API void UImGui_Renderer_forceUpdate();
#ifdef __cplusplus
}
#endif
