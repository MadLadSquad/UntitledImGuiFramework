#pragma once
#ifdef __cplusplus
extern "C"
{
#endif

#include <C/CTypes.h>
#include <C/CDefines.h>
#include <C/Window/CMonitor.h>

    typedef enum UImGui_WindowPlatform
    {
        UIMGUI_WINDOW_PLATFORM_WIN32,
        UIMGUI_WINDOW_PLATFORM_COCOA,
        UIMGUI_WINDOW_PLATFORM_X11,
        UIMGUI_WINDOW_PLATFORM_WAYLAND,
        UIMGUI_WINDOW_PLATFORM_EMSCRIPTEN,
        UIMGUI_WINDOW_PLATFORM_OTHER
    } UImGui_WindowPlatform;

    typedef void(*UImGui_Window_pushWindowPositionChangeCallbackFun)(UImGui_FVector2);
    typedef void(*UImGui_Window_pushWindowCloseCallbackFun)();
    typedef void(*UImGui_Window_pushWindowResizedInScreenCoordsCallbackFun)(int, int);

    typedef void(*UImGui_Window_pushWindowFocusCallbackFun)(bool);
    typedef UImGui_Window_pushWindowFocusCallbackFun UImGui_Window_pushWindowIconifyCallbackFun;

    typedef void(*UImGui_Window_pushWindowContentScaleCallbackFun)(UImGui_FVector2);
    typedef void(*UImGui_Window_pushWindowRefreshCallbackFun)();
    typedef void(*UImGui_Window_pushWindowMaximiseCallbackFun)(bool);

    typedef void(*UImGui_Window_pushWindowErrorCallbackFun)(int, UImGui_String);

    typedef void(*UImGui_Window_pushWindowOSDragDropCallbackFun)(UImGui_String);

    // Event Safety - begin, style, post-begin
    UIMGUI_PUBLIC_API void UImGui_Window_setTitle(UImGui_String name);
    // Event Safety - begin, style, post-begin
    UIMGUI_PUBLIC_API UImGui_String UImGui_Window_getTitle();
    // Event Safety - begin, style, post-begin
    UIMGUI_PUBLIC_API void UImGui_Window_setTitleSetting(UImGui_String name);
    // Event Safety - begin, style, post-begin
    UIMGUI_PUBLIC_API UImGui_String UImGui_Window_getTitleSetting();

    // Event Safety - begin, style, post-begin
    UIMGUI_PUBLIC_API void UImGui_Window_setIcon(UImGui_String name);
    // Event Safety - begin, style, post-begin
    UIMGUI_PUBLIC_API UImGui_String UImGui_Window_getIconLocation();
    // Event Safety - begin, style, post-begin
    UIMGUI_PUBLIC_API UImGui_String UImGui_Window_getIconLocationSetting();
    // Event Safety - begin, style, post-begin
    UIMGUI_PUBLIC_API void UImGui_Window_setIconLocationSetting(UImGui_String location);

    // Event Safety - begin, style, post-begin
    UIMGUI_PUBLIC_API float UImGui_Window_getAspectRatio();

    // Event Safety - begin, style, post-begin
    UIMGUI_PUBLIC_API UImGui_FVector2 UImGui_Window_getCurrentWindowPosition();
    // Event Safety - begin, style, post-begin
    UIMGUI_PUBLIC_API UImGui_FVector2 UImGui_Window_getLastWindowPosition();
    // Event Safety - begin, style, post-begin
    UIMGUI_PUBLIC_API UImGui_FVector2 UImGui_Window_getWindowPositionChange();

    // Event Safety - begin, style, post-begin
    UIMGUI_PUBLIC_API void UImGui_Window_setCurrentWindowPosition(UImGui_FVector2 pos);
    // Event Safety - begin, style, post-begin
    UIMGUI_PUBLIC_API void UImGui_Window_pushWindowPositionChangeCallback(UImGui_Window_pushWindowPositionChangeCallbackFun f);

    // Event Safety - begin, style, post-begin
    UIMGUI_PUBLIC_API UImGui_FVector2 UImGui_Window_getWindowSize();
    // Event Safety - begin, style, post-begin
    UIMGUI_PUBLIC_API UImGui_FVector2* UImGui_Window_getWindowSizeSetting();

    // Event Safety - begin, style, post-begin
    UIMGUI_PUBLIC_API bool UImGui_Window_getWindowFullscreen();
    // Event Safety - begin, style, post-begin
    UIMGUI_PUBLIC_API bool* UImGui_Window_getWindowFullscreenSetting();
    // Event Safety - begin, style, post-begin
    UIMGUI_PUBLIC_API void UImGui_Window_setWindowFullscreen(bool bFullscreen);

    // Event Safety - begin, style, post-begin
    UIMGUI_PUBLIC_API void UImGui_Window_saveSettings(bool bSaveKeybinds);

    // Event Safety - begin, style, post-begin
    UIMGUI_PUBLIC_API void UImGui_Window_refreshSettings();

    // Event Safety - begin, style, post-begin
    UIMGUI_PUBLIC_API void UImGui_Window_close();
    // Event Safety - begin, style, post-begin
    UIMGUI_PUBLIC_API void UImGui_Window_pushWindowCloseCallback(UImGui_Window_pushWindowCloseCallbackFun f);
    
    // Event Safety - begin, style, post-begin
    // Available for GLFW platforms - X11, Win32 & macOS
    UIMGUI_PUBLIC_API void UImGui_Window_Platform_setWindowAlwaysOnTop();

    // Event Safety - begin, style, post-begin
    // Available for GLFW platforms - X11, Win32 & macOS
    UIMGUI_PUBLIC_API void UImGui_Window_Platform_setWindowAlwaysOnBottom();

    // Event Safety - begin, style, post-begin
    // Available for GLFW platforms - X11, Win32
    UIMGUI_PUBLIC_API void UImGui_Window_Platform_setWindowShowingOnPager(bool bShowInPager);
    // Event Safety - begin, style, post-begin
    // Available for GLFW platforms - X11, Win32
    UIMGUI_PUBLIC_API bool UImGui_Window_Platform_getWindowShowingOnPager();

    // Event Safety - begin, style, post-begin
    // Available for GLFW platforms - X11, Win32
    UIMGUI_PUBLIC_API void UImGui_Window_Platform_setWindowShowingOnTaskbar(bool bShowOnTaskbar);
    // Event Safety - begin, style, post-begin
    // Available for GLFW platforms - X11, Win32
    UIMGUI_PUBLIC_API bool UImGui_Window_Platform_getWindowShowingOnTaskbar();

    // Event Safety - begin, style, post-begin
    // Available for GLFW platforms - X11
    // Sets the X11 window type
    UIMGUI_PUBLIC_API void UImGui_Window_Platform_setWindowType(UImGui_String type);

    // Event Safety - begin, style, post-begin
    // Available for GLFW platforms - X11, Win32 & macOS
    // Returns the window ID as a size_t. On macOS, it returns the memory address to the window as its integer representation
    UIMGUI_PUBLIC_API size_t UImGui_Window_Platform_getWindowID();

    // Event Safety - begin, style, post-begin
    // Available for GLFW platforms - Win32, macOS, Emscripten, X11 & Wayland
    // Returns the native window handle as a void*
    UIMGUI_PUBLIC_API void* UImGui_Window_Platform_getNativeWindowHandle();

    // Event Safety - begin, style, post-begin
    // Available for GLFW platforms - Win32, macOS, Emscripten, X11 & Wayland
    // Returns the native window handle as a void*
    UIMGUI_PUBLIC_API UImGui_WindowPlatform UImGui_Window_Platform_getCurrentWindowPlatform();

    // Event Safety - begin, style, post-begin
    // Available for GLFW platforms - X11 & Wayland. The other platforms return null. Cross-platform libraries
    // should handle null values without any issues though.
    UIMGUI_PUBLIC_API void* UImGui_Window_Platform_getNativeDisplay();

    // Event safety - begin, style, post-begin
    UIMGUI_PUBLIC_API void UImGui_Window_setWindowSizeInScreenCoords(UImGui_FVector2 sz);
    // Event safety - begin, style, post-begin
    UIMGUI_PUBLIC_API UImGui_FVector2 UImGui_Window_getWindowSizeInScreenCoords();
    // Event safety - begin, style, post-begin
    // Pushes a new callback to the event list
    UIMGUI_PUBLIC_API void UImGui_Window_pushWindowResizedInScreenCoordsCallback(UImGui_Window_pushWindowResizedInScreenCoordsCallbackFun f);
    // Event safety - begin, style, post-begin
    // Changes resize-ability of the window, not the setting
    UIMGUI_PUBLIC_API void UImGui_Window_setWindowResizeable(bool bResizeable);
    // Event safety - begin, style, post-begin
    // Returns the setting, doesn't modify the window
    UIMGUI_PUBLIC_API bool* UImGui_Window_getWindowResizeableSetting();
    // Event safety - begin, style, post-begin
    // Returns the current resize state of the window
    UIMGUI_PUBLIC_API bool UImGui_Window_getWindowCurrentlyResizeable();

    // Event safety - begin, style, post-begin
    // Pushes a new callback to the event list
    UIMGUI_PUBLIC_API void UImGui_Window_pushWindowResizeCallback(UImGui_Window_pushWindowResizedInScreenCoordsCallbackFun f);

    // Event safety - begin, style, post-begin
    // x = left; y = top; z = right; w = bottom
    UIMGUI_PUBLIC_API UImGui_FVector4 UImGui_Window_getWindowDecorationFrameDistances();

    // Event safety - begin, style, post-begin
    UIMGUI_PUBLIC_API void UImGui_Window_requestWindowAttention();

    // Event safety - begin, style, post-begin
    // This doesn't change the "hidden" setting, use the `getWindowHidden` function to change it
    UIMGUI_PUBLIC_API void UImGui_Window_hideWindow();
    // Event safety - begin, style, post-begin
    // This doesn't change the "hidden" setting, use the `getWindowHidden` function to change it
    UIMGUI_PUBLIC_API void UImGui_Window_showWindow();
    // Event safety - begin, style, post-begin
    // Used to change the "hidden" setting, doesn't modify the current hidden state
    UIMGUI_PUBLIC_API bool* UImGui_Window_getWindowHiddenSetting();
    // Event safety - begin, style, post-begin
    // Used to get the current window hidden state
    UIMGUI_PUBLIC_API bool UImGui_Window_getWindowCurrentlyHidden();

    // Event safety - begin, style, post-begin
    UIMGUI_PUBLIC_API bool UImGui_Window_getWindowSurfaceTransparent();
    // Event safety - begin, style, post-begin
    UIMGUI_PUBLIC_API void UImGui_Window_setWindowSurfaceTransparent(bool bTransparent);
    // Event safety - begin, style, post-begin
    UIMGUI_PUBLIC_API bool* UImGui_Window_getWindowSurfaceTransparentSetting();

    // Event safety - begin, style, post-begin
    // This doesn't change the "focused" setting, use the `getWindowFocused` function
    UIMGUI_PUBLIC_API void UImGui_Window_focusWindow();
    // Event safety - begin, style, post-begin
    // Used to change the "focused" setting, doesn't modify the current focused state
    UIMGUI_PUBLIC_API bool* UImGui_Window_getWindowFocusedSetting();
    // Event safety - begin, style, post-begin
    // Used to get the current window focus state
    UIMGUI_PUBLIC_API bool UImGui_Window_getWindowCurrentlyFocused();
    // Event safety - begin, style, post-begin
    UIMGUI_PUBLIC_API void UImGui_Window_pushWindowFocusCallback(UImGui_Window_pushWindowFocusCallbackFun f);

    // Event safety - begin, style, post-begin
    UIMGUI_PUBLIC_API void UImGui_Window_iconifyWindow();
    // Event safety - begin, style, post-begin
    // Restores window from iconification and maximisation
    UIMGUI_PUBLIC_API void UImGui_Window_restoreWindowState();
    // Event safety - begin, style, post-begin
    UIMGUI_PUBLIC_API void UImGui_Window_pushWindowIconifyCallback(UImGui_Window_pushWindowIconifyCallbackFun f);
    // Event safety - begin, style, post-begin
    UIMGUI_PUBLIC_API bool UImGui_Window_getWindowIconified();

    // Event safety - begin, style, post-begin
    UIMGUI_PUBLIC_API UImGui_FVector2 UImGui_Window_getWindowContentScale();
    // Event safety - begin, style, post-begin
    UIMGUI_PUBLIC_API void UImGui_Window_pushWindowContentScaleCallback(UImGui_Window_pushWindowContentScaleCallbackFun f);

    // Event safety - begin, style, post-begin
    // -1 is the default value a.k.a no size limit
    UIMGUI_PUBLIC_API void UImGui_Window_setSizeLimits(UImGui_FVector2 min, UImGui_FVector2 max);
    // Event safety - begin, style, post-begin
    // -1 is the default value a.k.a. no size limit
    UIMGUI_PUBLIC_API void UImGui_Window_setSizeLimitByAspectRatio(UImGui_FVector2 ratio);
    // Event safety = begin, style, post-begin
    // Returns the settings value for the size limits, doesn't edit them
    UIMGUI_PUBLIC_API UImGui_FVector4* UImGui_Window_getSizeLimits();
    // Event safety = begin, style, post-begin
    // Returns the settings value for the aspect ratio size limits, doesn't edit them
    UIMGUI_PUBLIC_API UImGui_FVector2* UImGui_Window_getAspectRatioSizeLimits();

    // Event safety - begin, style, post-begin
    // Returns the current state of the window, not the setting
    UIMGUI_PUBLIC_API bool UImGui_Window_getCurrentWindowDecoratedState();
    // Event safety - begin, style, post-begin
    // Returns the setting, not the current state of the window
    UIMGUI_PUBLIC_API bool* UImGui_Window_getWindowDecoratedSetting();
    // Event safety - begin, style, post-begin
    // Sets the decoration state of the window
    UIMGUI_PUBLIC_API void UImGui_Window_setWindowDecorated(bool bDecorated);

    // Event safety - begin, style, post-begin
    UIMGUI_PUBLIC_API void UImGui_Window_pushWindowRefreshCallback(UImGui_Window_pushWindowRefreshCallbackFun f);

    // Event safety - begin, style, post-begin
    // This changes the current window maximisation state but doesn't change the setting
    UIMGUI_PUBLIC_API void UImGui_Window_maximiseWindow();
    // Event Safety - begin, style, post-begin
    // This changes the setting but doesn't change the current window maximisation state
    UIMGUI_PUBLIC_API bool* UImGui_Window_getWindowMaximisedSetting();
    // Event safety - begin, style, post-begin
    UIMGUI_PUBLIC_API void UImGui_Window_pushWindowMaximiseCallback(UImGui_Window_pushWindowMaximiseCallbackFun f);
    // Event safety - begin, style, post-begin
    UIMGUI_PUBLIC_API bool UImGui_Window_getWindowCurrentlyMaximised();

    // A "UImGui_Window_getWindowMonitor" function should be here, but because it has to access private class variables,
    // it's defined under the C++ interface's Monitor's private section.
    // Event safety - begin, style, post-begin
    UIMGUI_PUBLIC_API UImGui_MonitorData UImGui_Window_getWindowMonitor();

    // Returns the primary monitor
    // Event safety - begin, style, post-begin
    UIMGUI_PUBLIC_API UImGui_MonitorData UImGui_Window_getPrimaryMonitor();

    // Event safety - begin, style, post-begin
    // Returns a list of monitors, first monitor is the primary monitor, i.e. the monitor where global UI elements
    // like the taskbar spawns.
    UIMGUI_PUBLIC_API UImGui_MonitorData* UImGui_Window_getMonitors(size_t* size);
    
    // Event safety - begin, style, post-begin
    UIMGUI_PUBLIC_API void UImGui_Window_pushWindowOSDragDropCallback(UImGui_Window_pushWindowOSDragDropCallbackFun f);

    // Event safety - begin, style, post-begin
    UIMGUI_PUBLIC_API void* UImGui_Window_getInternal();
#ifdef __cplusplus
};
#endif