#pragma once
#include <C/CTypes.h>
#include <C/CDefines.h>

#ifdef __cplusplus
extern "C"
{
#endif
struct UImGui_CMonitorData;

typedef enum UImGui_MonitorState
{
    UIMGUI_MONITOR_STATE_CONNECTED = 0x00040001,
    UIMGUI_MONITOR_STATE_DISCONNECTED = 0x00040002
} UImGui_MonitorState;

typedef void(*UImGui_Monitor_EventsFun)(struct UImGui_CMonitorData*, UImGui_MonitorState);
typedef struct GLFWmonitor GLFWmonitor;

// Do not create this manually!!! this should be fetched using the UImGui_Window_getWindowMonitor or
// UImGui_Window_getMonitors functions
typedef struct UIMGUI_PUBLIC_API UImGui_CMonitorData
{
    void* additionalData;
    size_t additionalDataSize;

    // Do not touch
    GLFWmonitor* monitor;
} UImGui_CMonitorData;

typedef void(*UImGui_Window_pushGlobalMonitorCallbackFun)(UImGui_CMonitorData*, UImGui_MonitorState);

// Event safety - any time
UIMGUI_PUBLIC_API void UImGui_Monitor_init(UImGui_CMonitorData* data);
// Event safety - any time
UIMGUI_PUBLIC_API void UImGui_Monitor_initWithMonitor_Internal(UImGui_CMonitorData* data, GLFWmonitor* monitor);

// Event safety - begin, style, post-begin
UIMGUI_PUBLIC_API UImGui_FVector2 UImGui_Monitor_getPhysicalSize(const UImGui_CMonitorData* data);

// Event safety - begin, style, post-begin
UIMGUI_PUBLIC_API UImGui_FVector2 UImGui_Monitor_getContentScale(const UImGui_CMonitorData* data);

// Event safety - begin, style, post-begin
UIMGUI_PUBLIC_API UImGui_FVector2 UImGui_Monitor_getVirtualPosition(const UImGui_CMonitorData* data);

// Event safety - begin, style, post-begin
// Returns work area as FVector4 where x = x position, y = y position, z = width, w = height
UIMGUI_PUBLIC_API UImGui_FVector4 UImGui_Monitor_getWorkArea(const UImGui_CMonitorData* data);

// Event safety - begin, style, post-begin
// May not be unique
UIMGUI_PUBLIC_API UImGui_String UImGui_Monitor_getName(const UImGui_CMonitorData* data);

// Event safety - begin, style, post-begin
UIMGUI_PUBLIC_API void UImGui_Monitor_pushEvent(UImGui_CMonitorData* data, UImGui_Monitor_EventsFun f);

#ifdef __cplusplus
}
#endif