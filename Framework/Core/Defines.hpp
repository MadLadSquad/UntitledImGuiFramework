#pragma once
// This header only contains C++ code. Check out the C header for a lot more defines.
#include <C/CDefines.h>

// Define a macro for accessing std::filesystem
#ifndef __MINGW32__
    #if __has_include(<filesystem>)
        #include <filesystem>
        #define std_filesystem std::filesystem
    #else
        #include <experimental/filesystem>
        #define std_filesystem std::experimental::filesystem
    #endif
#else
    #error "Compiling against MinGW is not supported!"
#endif

#ifdef PRODUCTION
    #define UIMGUI_START(x) std::ios_base::sync_with_stdio(!(x));   \
    UNUSED(UImGui::AllocatorFuncs::get());                                  \
    UNUSED(UImGui::Global::get());                                          \
    logger.setCrashOnError(true);                                   \
    UImGui::Utility::removeConsole()
#else
    #define UIMGUI_START(x) std::ios_base::sync_with_stdio(!(x));   \
    UNUSED(UImGui::AllocatorFuncs::get());                                  \
    UNUSED(UImGui::Global::get())
#endif

#define CAST(x, y) static_cast<x>(y)
#define FCAST(x, y) (x)y

namespace UImGui
{
    /**
     * @brief The ComponentState enum defines 3 fields that represent the event state of the given component, the given
     * component can then check its own state(if in PAUSED or RUNNING state) and call specific components of its event
     * functions. The OFF state is there to make it easy to fully shut down a component until the program closes
     */
    typedef UImGui_ComponentState ComponentState;

    /**
     * @brief An enum that defines component types to be used by various functions
     * @var UIMGUI_COMPONENT_TYPE_INLINE - Defines an inline component
     * @var UIMGUI_COMPONENT_TYPE_TITLEBAR - Defines a titlebar component
     * @var UIMGUI_COMPONENT_PYE_WINDOW - Defines a window component
     */
    typedef UImGui_ComponentType ComponentType;
}