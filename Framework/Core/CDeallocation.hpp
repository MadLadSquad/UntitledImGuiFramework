#pragma once
#include <Types.hpp>
#include <C/Internal/CMonitor.h>
#include <C/Interfaces/CPluginInterface.h>
#include <Renderer/Texture.hpp>

namespace UImGui
{
    // A struct for storing variables for the C API, that will be deallocated when the application closes
    struct UIMGUI_PUBLIC_API CDeallocationStruct
    {
        TVector<FString> keyStrings;
        TVector<UImGui_CMonitorData> monitors;
        TVector<Texture> textures;
        TVector<UImGui_CPlugin> plugins;
    };
}