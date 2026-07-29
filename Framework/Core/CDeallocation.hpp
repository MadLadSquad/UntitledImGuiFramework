#pragma once
#include <Types.hpp>
#include <C/Window/CMonitor.h>
#include <C/Interfaces/CPluginInterface.h>
#include <Renderer/Texture.hpp>

namespace UImGui
{
    // A struct for storing variables for the C API, that will be deallocated when the application closes
    struct UIMGUI_PUBLIC_API CDeallocationStruct
    {
        TVector<FString> keyStrings;
        TVector<UImGui_MonitorData> monitors;
        // TList, not TVector: Texture is non-copyable and non-movable(it owns GPU state and an internal dispatch table
        // pointing at its own members), and a list never relocates its elements. That also makes the UImGui_CTexture*
        // handles handed out to C callers stable - with a vector, every texture created after one was handed out could
        // reallocate the storage and dangle it
        TList<Texture> textures;
        TVector<UImGui_CPlugin> plugins;
    };
}