#include "CMonitor.h"
#include <Interfaces/WindowInterface.hpp>
#include <Utils/Window.hpp>
#include <GLFW/glfw3.h>

void UImGui_Monitor_init(UImGui_CMonitorData* data)
{
    data->monitor = nullptr;

    data->additionalData = nullptr;
    data->additionalDataSize = 0;
}

void UImGui_Monitor_initWithMonitor_Internal(UImGui_CMonitorData* data, GLFWmonitor* monitor)
{
    UImGui_Monitor_init(data);
    data->monitor = monitor;
}

UImGui_FVector2 UImGui_Monitor_getPhysicalSize(UImGui_CMonitorData* data)
{
    UImGui::Monitor monitor(data->monitor);
    return monitor.getPhysicalSize();
}

UImGui_FVector2 UImGui_Monitor_getContentScale(UImGui_CMonitorData* data)
{
    UImGui::Monitor monitor(data->monitor);
    return monitor.getContentScale();
}

UImGui_FVector2 UImGui_Monitor_getVirtualPosition(UImGui_CMonitorData* data)
{
    UImGui::Monitor monitor(data->monitor);
    return monitor.getVirtualPosition();
}

UImGui_FVector4 UImGui_Monitor_getWorkArea(UImGui_CMonitorData* data)
{
    UImGui::Monitor monitor(data->monitor);
    return monitor.getWorkArea();
}

UImGui_String UImGui_Monitor_getName(UImGui_CMonitorData* data)
{
    // Use glfw here, instead of the getName function, as we're skipping up to 2 re-allocations, since the internal glfw
    // const char*, will be allocated into an FString, which will then have to be pushed to the
    // CDeallocationStruct (another copy), and then the const char* data will be returned from the function. Using this,
    // we're only using the internal const char*.
    return glfwGetMonitorName(data->monitor);
}

void UImGui_Monitor_pushEvent(UImGui_CMonitorData* data, UImGui_Monitor_EventsFun f)
{
    UImGui::Monitor::CInternalGetMonitorClassDoNotTouch::UImGui_Monitor_pushEvent(data, f);
}