#pragma once
#include <Core/Types.hpp>
#include "Window/Window.hpp"
#include <C/Interfaces/CWindowInterface.h>
#include <Core/Components/Instance.hpp>

namespace UImGui
{
    class UIMGUI_PUBLIC_API Window
    {
    public:
        Window() = delete;
        Window(const Window&) = delete;
        void operator=(Window const&) = delete;

        // Event Safety - begin, style, post-begin
        static void setTitle(String name) noexcept;
        // Event Safety - begin, style, post-begin
        static String getTitle() noexcept;
        // Event Safety - begin, style, post-begin
        static void setTitleSetting(String name) noexcept;
        // Event Safety - begin, style, post-begin
        static String getTitleSetting() noexcept;

        // Event Safety - begin, style, post-begin
        static void setIcon(String name) noexcept;
        // Event Safety - begin, style, post-begin
        static String getIconLocation() noexcept;
        // Event Safety - begin, style, post-begin
        static String getIconLocationSetting() noexcept;
        // Event Safety - begin, style, post-begin
        static void setIconLocationSetting(String location) noexcept;

        // Event Safety - begin, style, post-begin
        static float getAspectRatio() noexcept;

        // Event Safety - begin, style, post-begin
        static FVector2 getCurrentWindowPosition() noexcept;
        // Event Safety - begin, style, post-begin
        static FVector2 getLastWindowPosition() noexcept;
        // Event Safety - begin, style, post-begin
        static FVector2 getWindowPositionChange() noexcept;

        // Event Safety - begin, style, post-begin
        static void setCurrentWindowPosition(FVector2 pos) noexcept;
        // Event Safety - begin, style, post-begin
        static void pushWindowPositionChangeCallback(const TFunction<void(FVector2)>& f) noexcept;

        // Event Safety - begin, style, post-begin
        static FVector2 getWindowSize() noexcept;
        // Event Safety - begin, style, post-begin
        static FVector2& getWindowSizeSetting() noexcept;

        // Event Safety - begin, style, post-begin
        static bool getWindowFullscreen() noexcept;
        // Event Safety - begin, style, post-begin
        static bool& getWindowFullscreenSetting() noexcept;
        // Event Safety - begin, style, post-begin
        static void setWindowFullscreen(bool bFullscreen) noexcept;

        // Event Safety - begin, style, post-begin
        static void saveSettings(bool bSaveKeybinds) noexcept;

        // Event Safety - post-style, post-begin
        static void refreshSettings() noexcept;

        // Event Safety - begin, style, post-begin
        static void close() noexcept;
        // Event Safety - begin, style, post-begin
        static void pushWindowCloseCallback(const TFunction<void(void)>& f) noexcept;

        class Platform
        {
        public:
            Platform() = delete;
            Platform(const Platform&) = delete;
            void operator=(Platform const&) = delete;

            // Event Safety - begin, style, post-begin
            // Available for platforms - X11, Win32, macOS
            static void setWindowAlwaysOnTop() noexcept;

            // Event Safety - begin, style, post-begin
            // Available for platforms - X11, Win32, macOS
            static void setWindowAlwaysOnBottom() noexcept;

            // Event Safety - begin, style, post-begin
            // Platform note: On Win32 "setWindowShowingOnPager" and "setWindowShowingOnTaskbar" run the same code,
            // as it is not possible to disable the window from showing on both the taskbar and window switcher
            // Available for platforms - X11, Win32
            static void setWindowShowingOnPager(bool bShowInPager) noexcept;
            // Event Safety - begin, style, post-begin
            // Available for platforms - X11, Win32
            static bool getWindowShowingOnPager() noexcept;

            // Event Safety - begin, style, post-begin
            // Available for platforms - X11, Win32
            static void setWindowShowingOnTaskbar(bool bShowOnTaskbar) noexcept;
            // Event Safety - begin, style, post-begin
            // Available for platforms - X11, Win32
            static bool getWindowShowingOnTaskbar() noexcept;

            // Event Safety - begin, style, post-begin
            // Available for platforms - X11
            // Sets the X11 window type
            static void setWindowType(String type) noexcept;

            // Event Safety - begin, style, post-begin
            // Available for platforms - X11, Win32, macOS
            // Returns the window ID as a size_t. On macOS this is the integer representation of the window pointer
            static size_t getWindowID() noexcept;
        };

        // Event safety - begin, style, post-begin
        static void setWindowSizeInScreenCoords(FVector2 sz) noexcept;
        // Event safety - begin, style, post-begin
        static FVector2 getWindowSizeInScreenCoords() noexcept;
        // Event safety - begin, style, post-begin
        // Pushes a new callback to the event list
        static void pushWindowResizedInScreenCoordsCallback(const TFunction<void(int, int)>& f) noexcept;
        // Event safety - begin, style, post-begin
        // Changes resize-ability of the window, not the setting
        static void setWindowResizeable(bool bResizeable) noexcept;
        // Event safety - begin, style, post-begin
        // Returns the setting, doesn't modify the window
        static bool& getWindowResizeableSetting() noexcept;
        // Event safety - begin, style, post-begin
        // Returns the current resize state of the window
        static bool getWindowCurrentlyResizeable() noexcept;

        // Event safety - begin, style, post-begin
        // Pushes a new callback to the event list
        static void pushWindowResizeCallback(const TFunction<void(int, int)>& f) noexcept;

        // Event safety - begin, style, post-begin
        // x = left; y = top; z = right; w = bottom
        static FVector4 getWindowDecorationFrameDistances() noexcept;

        // Event safety - begin, style, post-begin
        static void requestWindowAttention() noexcept;

        // Event safety - begin, style, post-begin
        // This doesn't change the "hidden" setting, use the `getWindowHidden` function to change it
        static void hideWindow() noexcept;
        // Event safety - begin, style, post-begin
        // This doesn't change the "hidden" setting, use the `getWindowHidden` function to change it
        static void showWindow() noexcept;
        // Event safety - begin, style, post-begin
        // Used to change the "hidden" setting, doesn't modify the current hidden state
        static bool& getWindowHiddenSetting() noexcept;
        // Event safety - begin, style, post-begin
        // Used to get the current window hidden state
        static bool getWindowCurrentlyHidden() noexcept;

        // Event safety - begin, style, post-begin
        static bool& windowSurfaceTransparentSetting() noexcept;

        // Event safety - begin, style, post-begin
        // This doesn't change the "focused" setting, use the `getWindowFocused` function
        static void focusWindow() noexcept;
        // Event safety - begin, style, post-begin
        // Used to change the "focused" setting, doesn't modify the current focused state
        static bool& getWindowFocusedSetting() noexcept;
        // Event safety - begin, style, post-begin
        // Used to get the current window focus state
        static bool getWindowCurrentlyFocused() noexcept;
        // Event safety - begin, style, post-begin
        static void pushWindowFocusCallback(const TFunction<void(bool)>& f) noexcept;

        // Event safety - begin, style, post-begin
        static void iconifyWindow() noexcept;
        // Event safety - begin, style, post-begin
        // Restores window from iconification and maximisation
        static void restoreWindowState() noexcept;
        // Event safety - begin, style, post-begin
        static void pushWindowIconifyCallback(const TFunction<void(bool)>& f) noexcept;
        // Event safety - begin, style, post-begin
        static bool getWindowIconified() noexcept;

        // Event safety - begin, style, post-begin
        static FVector2 getWindowContentScale() noexcept;
        // Event safety - begin, style, post-begin
        static void pushWindowContentScaleCallback(const TFunction<void(FVector2)>& f) noexcept;

        // Event safety - begin, style, post-begin
        // Calling without arguments resets to the default state
        static void setSizeLimits(FVector2 min = { -1, -1 }, FVector2 max = { -1, -1 }) noexcept;
        // Event safety - begin, style, post-begin
        // Calling without an argument resets to the default state
        static void setSizeLimitByAspectRatio(FVector2 ratio = { -1, -1 }) noexcept;
        // Event safety = begin, style, post-begin
        // Returns the settings value for the size limits, doesn't edit them
        static FVector4& getSizeLimits() noexcept;
        // Event safety = begin, style, post-begin
        // Returns the settings value for the aspect ratio size limits, doesn't edit them
        static FVector2& getAspectRatioSizeLimits() noexcept;

        // Event safety - begin, style, post-begin
        // Returns the current state of the window, not the setting
        static bool getCurrentWindowDecoratedState() noexcept;
        // Event safety - begin, style, post-begin
        // Returns the setting, not the current state of the window
        static bool& getWindowDecoratedSetting() noexcept;
        // Event safety - begin, style, post-begin
        // Sets the decoration state of the window
        static void setWindowDecorated(bool bDecorated) noexcept;

        // Event safety - begin, style, post-begin
        static void pushWindowRefreshCallback(const TFunction<void(void)>& f) noexcept;

        // Event safety - begin, style, post-begin
        // This changes the current window maximisation state but doesn't change the setting
        static void maximiseWindow() noexcept;
        // Event Safety - begin, style, post-begin
        // This changes the setting but doesn't change the current window maximisation state
        static bool& getWindowMaximisedSetting() noexcept;
        // Event safety - begin, style, post-begin
        static void pushWindowMaximiseCallback(const TFunction<void(bool)>& f) noexcept;
        // Event safety - begin, style, post-begin
        static bool getWindowCurrentlyMaximised() noexcept;

        // Event safety - begin, style, post-begin
        // Returns the monitor of the current window.
        static Monitor getWindowMonitor() noexcept;

        // Event safety - begin, style, post-begin
        // Returns the primary monitor
        static Monitor getPrimaryMonitor() noexcept;

        // Event safety - begin, style, post-begin
        // Returns a list of monitors, first monitor is the primary monitor, i.e. the monitor where global UI elements
        // like the taskbar spawns.
        static const TVector<Monitor>& getMonitors() noexcept;

        // Event safety - begin, style, post-begin
        static void pushWindowOSDragDropCallback(const TFunction<void(const FString&)>& f) noexcept;

        // Event safety - begin, style, post-begin
        // This is the internal window instance, DO NOT TOUCH IT
        static void* getInternal() noexcept;

        // Event safety - begin, style, post-begin
        // Returns the current window instance
        static GenericWindow* get() noexcept;
    };
}