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