#pragma once
#include <Core/Defines.hpp>
#include <Core/Types.hpp>
#include "Utils/Window.hpp"

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
        static void setIcon(String name) noexcept;

        // Event Safety - begin, style, post-begin
        static float aspectRatio() noexcept;

        // Event Safety - begin, style, post-begin
        static FVector2 getCurrentWindowPosition() noexcept;
        // Event Safety - begin, style, post-begin
        static FVector2 getLastWindowPosition() noexcept;
        // Event Safety - begin, style, post-begin
        static FVector2 getWindowPositionChange() noexcept;

        // Event Safety - begin, style, post-begin
        static void setCurrentWindowPosition(FVector2 pos) noexcept;
        // Event Safety - begin, style, post-begin
        static void pushWindowPositionChangeCallback(const std::function<void(FVector2)>& f) noexcept;

        // Event Safety - begin, style, post-begin
        static FVector2& windowSize() noexcept;
        // Event Safety - begin, style, post-begin
        static bool& fullscreen() noexcept;

        // Event Safety - begin, style, post-begin
        static FString& name() noexcept;
        // Event Safety - begin, style, post-begin
        static FString& iconLocation() noexcept;
        // Event Safety - begin, style, post-begin
        static FString& layoutLocation() noexcept;

        // Event Safety - begin, style, post-begin
        static void saveSettings(bool bSaveKeybinds) noexcept;

        // Event Safety - begin, style, post-begin
        static void refreshSettings() noexcept;

        // Event Safety - begin, style, post-begin
        static void close() noexcept;
        // Event Safety - begin, style, post-begin
        static void pushWindowCloseCallback(const std::function<void(void)>& f) noexcept;

        class Platform
        {
        public:
            Platform() = delete;
            Platform(const Platform&) = delete;
            void operator=(Platform const&) = delete;

            // Event Safety - begin, style, post-begin
            // Available for platforms - X11
            // Platforms to be supported - Wayland, Win32
            static void setWindowAlwaysOnTop() noexcept;

            // Event Safety - begin, style, post-begin
            // Available for platforms - X11
            // Platforms to be supported - Wayland, Win32
            static void setWindowAlwaysOnBottom() noexcept;

            // Event Safety - begin, style, post-begin
            // Available for platforms - X11
            // Platforms to be supported - Wayland, Win32
            static void disableWindowMovement() noexcept;

            // Event Safety - begin, style, post-begin
            // Available for platforms - X11
            // Platforms to be supported - Wayland, Win32
            static void setWindowShowingOnPager(bool bShowInPager) noexcept;
            // Event Safety - begin, style, post-begin
            // Available for platforms - X11
            // Platforms to be supported - Wayland, Win32
            static bool getWindowShowingOnPager() noexcept;

            // Event Safety - begin, style, post-begin
            // Available for platforms - X11
            // Platforms to be supported - Wayland, Win32
            static void setWindowShowingOnTaskbar(bool bShowOnTaskbar) noexcept;
            // Event Safety - begin, style, post-begin
            // Available for platforms - X11
            // Platforms to be supported - Wayland, Win32
            static bool getWindowShowingOnTaskbar() noexcept;

            // Event Safety - begin, style, post-begin
            // Available for platforms - X11
            // Platforms to be supported - Wayland, Win32
            // Sets the X11 window type
            static void setWindowType(String type) noexcept;
        };

        // Event safety - begin, style, post-begin
        static void setWindowSizeInScreenCoords(FVector2 sz) noexcept;
        // Event safety - begin, style, post-begin
        static FVector2& getWindowSizeInScreenCoords() noexcept;
        // Event safety - begin, style, post-begin
        // Pushes a new callback to the event list
        static void pushWindowResizedInScreenCoordsCallback(const std::function<void(int, int)>& f) noexcept;
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
        static void pushWindowResizeCallback(const std::function<void(int, int)>& f) noexcept;

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
        static bool& windowSurfaceTransparent() noexcept;

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
        static void pushWindowFocusCallback(const std::function<void(bool)>& f) noexcept;

        // Event safety - begin, style, post-begin
        static void iconifyWindow() noexcept;
        // Event safety - begin, style, post-begin
        // Restores window from iconification and maximisation
        static void restoreWindowState() noexcept;
        // Event safety - begin, style, post-begin
        static void pushWindowIconifyCallback(const std::function<void(bool)>& f) noexcept;
        // Event safety - begin, style, post-begin
        static bool getWindowIconified() noexcept;

        // Event safety - begin, style, post-begin
        static FVector2 getWindowContentScale() noexcept;
        // Event safety - begin, style, post-begin
        static void pushWindowContentScaleCallback(const std::function<void(FVector2)>& f) noexcept;

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
        static void pushWindowRefreshCallback(const std::function<void(void)>& f) noexcept;

        // Event safety - begin, style, post-begin
        // This changes the current window maximisation state but doesn't change the setting
        static void maximiseWindow() noexcept;
        // Event Safety - begin, style, post-begin
        // This changes the setting but doesn't change the current window maximisation state
        static bool& getWindowMaximisedSetting() noexcept;
        // Event safety - begin, style, post-begin
        static void pushWindowMaximiseCallback(const std::function<void(bool)>& f) noexcept;
        // Event safety - begin, style, post-begin
        static bool getWindowCurrentlyMaximised() noexcept;

        // Event safety - begin, style, post-begin
        // Returns the monitor of the current window.
        static Monitor getWindowMonitor() noexcept;

        // Event safety - begin, style, post-begin
        // Sets the window to the provided monitor. When moving the window, the window will be moved to coordinates
        // (0;0) of the new monitor, while preserving the width and height and using the new monitor's refresh rate
        static void setWindowMonitor(const Monitor& monitor) noexcept;

        // Event safety - begin, style, post-begin
        // Returns a list of monitors, first monitor is the primary monitor, i.e. the monitor where global UI elements
        // like the taskbar spawns.
        static std::vector<Monitor>& getMonitors() noexcept;

        // Event safety - begin, style, post-begin
        static void pushGlobalMonitorCallback(const std::function<void(Monitor&, MonitorState)>& f) noexcept;

        // Event safety - begin, style, post-begin
        // Returns all the strings acquired by the application when the user drags in a file or an array of files
        static std::vector<FString>& getOSDragDropStrings() noexcept;
        // Event safety - begin, style, post-begin
        static void pushWindowOSDragDropCallback(const std::function<void(std::vector<FString>&)>& f) noexcept;

        // Event safety - begin, style, post-begin
        static void pushWindowErrorCallback(const std::function<void(int, String)>& f) noexcept;
    private:
        friend class Input;
        friend class Instance;
        friend class RendererInternal;
        friend class WindowInternal;

        static WindowInternal& get() noexcept;
    };
}