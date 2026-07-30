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
        CDeallocationStruct() noexcept = default;

        /**
         * @brief The struct is neither copyable nor movable, and the deletions are load-bearing on Windows.
         *
         * It holds a TList<Texture>, and Texture deletes all four of its copy and move operations. On Unix that alone
         * is enough, since the implicit copy assignment of this struct would simply never be instantiated. MSVC's
         * __declspec(dllexport), which UIMGUI_PUBLIC_API expands to, instead forces every implicitly declared member of
         * an exported class to be defined, so the copy assignment gets instantiated whether anything calls it or not
         * and fails inside std::list with "attempting to reference a deleted function".
         *
         * Declaring them deleted means dllexport has nothing left to define. This is not a limitation to work around:
         * the struct is a single long-lived member of Global and hands out raw pointers into its own textures list to C
         * callers, so copying it was never valid to begin with
         */
        CDeallocationStruct(const CDeallocationStruct&) = delete;
        CDeallocationStruct& operator=(const CDeallocationStruct&) = delete;
        CDeallocationStruct(CDeallocationStruct&&) = delete;
        CDeallocationStruct& operator=(CDeallocationStruct&&) = delete;

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