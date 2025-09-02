#pragma once
#include <Core/Core.hpp>
#include <C/Internal/Keys.h>

namespace UImGui
{
    class UIMGUI_PUBLIC_API GenericWindow
    {
    public:
        GenericWindow() noexcept = default;
        virtual ~GenericWindow() noexcept = default;

        // -------------------------------------------------------------------------------------------------------------
        // ---------------------------------------- Renderer and UI integration ----------------------------------------
        // -------------------------------------------------------------------------------------------------------------

        // Corresponds to your platform backend's ImGui_ImplPlatform_InitForAPI() functions. These are only here to
        // accommodate out-of-the-box support for the built-in graphics APIs. For any other graphics API, you'll need
        // to build a custom renderer anyway so you can cast up to your custom window pointer as well
        virtual void ImGuiInitFor_Vulkan() noexcept = 0;
        virtual void ImGuiInitFor_OpenGL() noexcept = 0;
        virtual void ImGuiInitFor_Other() noexcept = 0;

        // Corresponds to your platform backend's ImGui_ImplPlatform_NewFrame() function
        virtual void ImGuiNewFrame() noexcept = 0;

        // Corresponds to your platform backend's ImGui_ImplPlatform_Shutdown() function
        virtual void ImGuiShutdown() noexcept = 0;

        // -------------------------------------------------------------------------------------------------------------
        // --------------------------------------------- Input integration ---------------------------------------------
        // -------------------------------------------------------------------------------------------------------------

        /**
         * Internal API: This is used by the Input interface to resolve a standard key's state, which means that you
         * need to implement a proper conversion between the CKeys enum and your platform's input system
         * @param key - The key to check against
         * @return The state of the key
         * @note Event safety -
         */
        virtual CKeyState getKey(CKeys key) noexcept = 0;

        // -------------------------------------------------------------------------------------------------------------
        // ---------------------------------------------- Window interface ---------------------------------------------
        // -------------------------------------------------------------------------------------------------------------

        // Event Safety - begin, style, post-begin
        virtual void setTitle(String name) noexcept = 0;

        // Event Safety - begin, style, post-begin
        virtual void setIcon(String name) noexcept = 0;

        // Event Safety - begin, style, post-begin
        virtual float aspectRatio() noexcept = 0;

        // Event Safety - begin, style, post-begin
        virtual FVector2 getCurrentWindowPosition() noexcept = 0;
        // Event Safety - begin, style, post-begin
        virtual FVector2 getLastWindowPosition() noexcept = 0;
        // Event Safety - begin, style, post-begin
        virtual FVector2 getWindowPositionChange() noexcept = 0;

        // Event Safety - begin, style, post-begin
        virtual void setCurrentWindowPosition(FVector2 pos) noexcept = 0;
        // Event Safety - begin, style, post-begin
        virtual void pushWindowPositionChangeCallback(const TFunction<void(FVector2)>& f) noexcept = 0;

        // Event Safety - begin, style, post-begin
        virtual FVector2& windowSize() noexcept = 0;
        // Event Safety - begin, style, post-begin
        virtual bool& fullscreen() noexcept = 0;

        // Event Safety - begin, style, post-begin
        virtual FString& name() noexcept = 0;
        // Event Safety - begin, style, post-begin
        virtual FString& iconLocation() noexcept = 0;

        // Event Safety - begin, style, post-begin
        virtual void saveSettings(bool bSaveKeybinds) noexcept = 0;

        // Event Safety - begin, style, post-begin
        virtual void refreshSettings() noexcept = 0;

        // Event Safety - begin, style, post-begin
        virtual void close() noexcept = 0;
        // Event Safety - begin, style, post-begin
        virtual void pushWindowCloseCallback(const TFunction<void(void)>& f) noexcept = 0;

        // Event Safety - begin, style, post-begin
        // Available for platforms - X11, Win32, macOS
        virtual void Platform_setWindowAlwaysOnTop() noexcept = 0;

        // Event Safety - begin, style, post-begin
        // Available for platforms - X11, Win32, macOS
        virtual void Platform_setWindowAlwaysOnBottom() noexcept = 0;

        // Event Safety - begin, style, post-begin
        // Platform note: On Win32 "setWindowShowingOnPager" and "setWindowShowingOnTaskbar" run the same code,
        // as it is not possible to disable the window from showing on both the taskbar and window switcher
        // Available for platforms - X11, Win32
        virtual void Platform_setWindowShowingOnPager(bool bShowInPager) noexcept = 0;
        // Event Safety - begin, style, post-begin
        // Available for platforms - X11, Win32
        virtual bool Platform_getWindowShowingOnPager() noexcept = 0;

        // Event Safety - begin, style, post-begin
        // Available for platforms - X11, Win32
        virtual void Platform_setWindowShowingOnTaskbar(bool bShowOnTaskbar) noexcept = 0;
        // Event Safety - begin, style, post-begin
        // Available for platforms - X11, Win32
        virtual bool Platform_getWindowShowingOnTaskbar() noexcept = 0;

        // Event Safety - begin, style, post-begin
        // Available for platforms - X11
        // Sets the X11 window type
        virtual void Platform_setWindowType(String type) noexcept = 0;

        // Event Safety - begin, style, post-begin
        // Available for platforms - X11, Win32, macOS
        // Returns the window ID as a size_t. On macOS this is the integer representation of the window pointer
        virtual size_t Platform_getWindowID() noexcept = 0;

        // Event safety - begin, style, post-begin
        virtual void setWindowSizeInScreenCoords(FVector2 sz) noexcept = 0;
        // Event safety - begin, style, post-begin
        virtual FVector2& getWindowSizeInScreenCoords() noexcept = 0;
        // Event safety - begin, style, post-begin
        // Pushes a new callback to the event list
        virtual void pushWindowResizedInScreenCoordsCallback(const TFunction<void(int, int)>& f) noexcept = 0;
        // Event safety - begin, style, post-begin
        // Changes resize-ability of the window, not the setting
        virtual void setWindowResizeable(bool bResizeable) noexcept = 0;
        // Event safety - begin, style, post-begin
        // Returns the setting, doesn't modify the window
        virtual bool& getWindowResizeableSetting() noexcept = 0;
        // Event safety - begin, style, post-begin
        // Returns the current resize state of the window
        virtual bool getWindowCurrentlyResizeable() noexcept = 0;

        // Event safety - begin, style, post-begin
        // Pushes a new callback to the event list
        virtual void pushWindowResizeCallback(const TFunction<void(int, int)>& f) noexcept = 0;

        // Event safety - begin, style, post-begin
        // x = left; y = top; z = right; w = bottom
        virtual FVector4 getWindowDecorationFrameDistances() noexcept = 0;

        // Event safety - begin, style, post-begin
        virtual void requestWindowAttention() noexcept = 0;

        // Event safety - begin, style, post-begin
        // This doesn't change the "hidden" setting, use the `getWindowHidden` function to change it
        virtual void hideWindow() noexcept = 0;
        // Event safety - begin, style, post-begin
        // This doesn't change the "hidden" setting, use the `getWindowHidden` function to change it
        virtual void showWindow() noexcept = 0;
        // Event safety - begin, style, post-begin
        // Used to change the "hidden" setting, doesn't modify the current hidden state
        virtual bool& getWindowHiddenSetting() noexcept = 0;
        // Event safety - begin, style, post-begin
        // Used to get the current window hidden state
        virtual bool getWindowCurrentlyHidden() noexcept = 0;

        // Event safety - begin, style, post-begin
        virtual bool& windowSurfaceTransparent() noexcept = 0;

        // Event safety - begin, style, post-begin
        // This doesn't change the "focused" setting, use the `getWindowFocused` function
        virtual void focusWindow() noexcept = 0;
        // Event safety - begin, style, post-begin
        // Used to change the "focused" setting, doesn't modify the current focused state
        virtual bool& getWindowFocusedSetting() noexcept = 0;
        // Event safety - begin, style, post-begin
        // Used to get the current window focus state
        virtual bool getWindowCurrentlyFocused() noexcept = 0;
        // Event safety - begin, style, post-begin
        virtual void pushWindowFocusCallback(const TFunction<void(bool)>& f) noexcept = 0;

        // Event safety - begin, style, post-begin
        virtual void iconifyWindow() noexcept = 0;
        // Event safety - begin, style, post-begin
        // Restores window from iconification and maximisation
        virtual void restoreWindowState() noexcept = 0;
        // Event safety - begin, style, post-begin
        virtual void pushWindowIconifyCallback(const TFunction<void(bool)>& f) noexcept = 0;
        // Event safety - begin, style, post-begin
        virtual bool getWindowIconified() noexcept = 0;

        // Event safety - begin, style, post-begin
        virtual FVector2 getWindowContentScale() noexcept = 0;
        // Event safety - begin, style, post-begin
        virtual void pushWindowContentScaleCallback(const TFunction<void(FVector2)>& f) noexcept = 0;

        // Event safety - begin, style, post-begin
        // Calling without arguments resets to the default state
        virtual void setSizeLimits(FVector2 min = { -1, -1 }, FVector2 max = { -1, -1 }) noexcept = 0;
        // Event safety - begin, style, post-begin
        // Calling without an argument resets to the default state
        virtual void setSizeLimitByAspectRatio(FVector2 ratio = { -1, -1 }) noexcept = 0;
        // Event safety = begin, style, post-begin
        // Returns the settings value for the size limits, doesn't edit them
        virtual FVector4& getSizeLimits() noexcept = 0;
        // Event safety = begin, style, post-begin
        // Returns the settings value for the aspect ratio size limits, doesn't edit them
        virtual FVector2& getAspectRatioSizeLimits() noexcept = 0;

        // Event safety - begin, style, post-begin
        // Returns the current state of the window, not the setting
        virtual bool getCurrentWindowDecoratedState() noexcept = 0;
        // Event safety - begin, style, post-begin
        // Returns the setting, not the current state of the window
        virtual bool& getWindowDecoratedSetting() noexcept = 0;
        // Event safety - begin, style, post-begin
        // Sets the decoration state of the window
        virtual void setWindowDecorated(bool bDecorated) noexcept = 0;

        // Event safety - begin, style, post-begin
        virtual void pushWindowRefreshCallback(const TFunction<void(void)>& f) noexcept = 0;

        // Event safety - begin, style, post-begin
        // This changes the current window maximisation state but doesn't change the setting
        virtual void maximiseWindow() noexcept = 0;
        // Event Safety - begin, style, post-begin
        // This changes the setting but doesn't change the current window maximisation state
        virtual bool& getWindowMaximisedSetting() noexcept = 0;
        // Event safety - begin, style, post-begin
        virtual void pushWindowMaximiseCallback(const TFunction<void(bool)>& f) noexcept = 0;
        // Event safety - begin, style, post-begin
        virtual bool getWindowCurrentlyMaximised() noexcept = 0;

#ifndef __EMSCRIPTEN__

        // Event safety - begin, style, post-begin
        // Returns the monitor of the current window.
        //virtual Monitor getWindowMonitor() noexcept = 0;

        // Event safety - begin, style, post-begin
        // Sets the window to the provided monitor. When moving the window, the window will be moved to coordinates
        // (0;0) of the new monitor, while preserving the width and height and using the new monitor's refresh rate
        //virtual void setWindowMonitor(const Monitor& monitor) noexcept = 0;

        // Event safety - begin, style, post-begin
        // Returns a list of monitors, first monitor is the primary monitor, i.e. the monitor where global UI elements
        // like the taskbar spawns.
        //virtual TVector<Monitor>& getMonitors() noexcept = 0;

        // Event safety - begin, style, post-begin
        //virtual void pushGlobalMonitorCallback(const TFunction<void(Monitor&, MonitorState)>& f) noexcept = 0;
#endif

        // Event safety - begin, style, post-begin
        // Returns all the strings acquired by the application when the user drags in a file or an array of files
        virtual TVector<FString>& getOSDragDropStrings() noexcept = 0;
        // Event safety - begin, style, post-begin
        virtual void pushWindowOSDragDropCallback(const TFunction<void(TVector<FString>&)>& f) noexcept = 0;

        // Event safety - begin, style, post-begin
        virtual void pushWindowErrorCallback(const TFunction<void(int, String)>& f) noexcept = 0;

        // Event safety - begin, style, post-begin
        // This is the internal window instance, DO NOT TOUCH IT
        virtual void* getInternal() noexcept = 0;

        // Event safety - begin, style, post-begin
        // This is the current window class
        virtual GenericWindow* get() noexcept = 0;
    };
}