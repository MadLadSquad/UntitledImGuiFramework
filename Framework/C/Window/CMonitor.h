#pragma once
#include <C/CTypes.h>
#include <C/CDefines.h>

#ifdef __cplusplus
extern "C"
{
#endif
    typedef void UImGui_CGenericMonitor;

    // Do not create this manually!!! This should be fetched using the UImGui_Window_get*Monitor(s) functions
    typedef struct UIMGUI_PUBLIC_API UImGui_MonitorData
    {
        uintptr_t id;
        void* additionalData;
        size_t additionalDataSize;
    } UImGui_MonitorData;

    // Get the monitor bounds as FVector4 where x = x position, y = y position, z = width, w = height
    // Event safety - begin, style, post-begin
    UIMGUI_PUBLIC_API UImGui_FVector4 UImGui_Monitor_getWorkArea(UImGui_MonitorData* data);

    // Get the monitor's content scale
    // Event safety - begin, style, post-begin
    UIMGUI_PUBLIC_API double UImGui_Monitor_getContentScale(UImGui_MonitorData* data);

    // Get the monitor's name in UTF-8 encoding
    // Event safety - begin, style, post-begin
    UIMGUI_PUBLIC_API UImGui_String UImGui_Monitor_getName(UImGui_MonitorData* data);

    // Get the monitor's size
    // Event safety - begin, style, post-begin
    UIMGUI_PUBLIC_API UImGui_FVector2 UImGui_Monitor_getSize(UImGui_MonitorData* data);

    // Get the monitor's pixel density
    // Event safety - begin, style, post-begin
    UIMGUI_PUBLIC_API float UImGui_Monitor_getPixelDensity(UImGui_MonitorData* data);

    // Allocate a GenericMonitor instance to be used together with a corresponding GenericWindow
    // Event safety - Any time
    UIMGUI_PUBLIC_API UImGui_CGenericMonitor* UImGui_CGenericMonitor_allocate(
        UImGui_FVector4(*getWorkArea)(UImGui_MonitorData*),
        double(*getContentScale)(UImGui_MonitorData*),
        UImGui_String(*getName)(UImGui_MonitorData*),
        UImGui_FVector2(*getSize)(UImGui_MonitorData*),
        float(*getPixelDensity)(UImGui_MonitorData*)
    );

    // CGenericWindow instances automatically call this function in their destructor, but it is given for convenience
    // Event safety - Any time
    UIMGUI_PUBLIC_API void UImGui_CGenericMonitor_free(UImGui_CGenericMonitor* monitor);

#ifdef __cplusplus
}
#endif