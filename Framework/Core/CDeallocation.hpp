#pragma once
#include <Types.hpp>
#include <C/Internal/CMonitor.h>

namespace UImGui
{
    // A struct for storing strings, which will be deallocated when the application closes
    struct UIMGUI_PUBLIC_API CDeallocationStruct
    {
        std::vector<FString> keyStrings;
        std::vector<UImGui_CMonitorData> monitors;
    };
}