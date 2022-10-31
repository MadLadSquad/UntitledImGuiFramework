#pragma once
// Dll macro magic
#ifdef _WIN32
    #ifdef UIMGUI_COMPILE_LIB
        #define UIMGUI_PUBLIC_API __declspec(dllexport)
    #else
        #define UIMGUI_PUBLIC_API __declspec(dllimport)
    #endif
#else
    #define UIMGUI_PUBLIC_API
#endif

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
    #define UIMGUI_START(x) std::ios_base::sync_with_stdio(!(x)); \
    logger.setCrashOnError(true); \
    UVK::Utility::removeConsole()
#else
    #define UIMGUI_START(x) std::ios_base::sync_with_stdio(!(x))
#endif

namespace UImGui
{
    /**
     * @brief The ComponentState enum defines 3 fields that represent the event state of the given component, the given
     * component can then check its own state(if in PAUSED or RUNNING state) and call specific components of its event
     * functions. The OFF state is there to make it easy to fully shut down a component until the program closes
     */
    enum ComponentState
    {
        // The component is not running but its events are still running
        UIMGUI_COMPONENT_STATE_PAUSED,
        // The component is running
        UIMGUI_COMPONENT_STATE_RUNNING,
        // The component is not running and its events are not running, only the constructor and destructor are called
        UIMGUI_COMPONENT_STATE_OFF,
    };
}