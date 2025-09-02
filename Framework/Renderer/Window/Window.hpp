#pragma once
#include <Core/Interfaces/Input.hpp>
#include <array>
#include <C/Internal/CMonitor.h>
#include <C/Interfaces/CWindowInterface.h>

struct GLFWwindow;
namespace UImGui
{
    struct UIMGUI_PUBLIC_API WindowData
    {
        FString name = "UntitledImGuiFramework Application";
        FString iconLocation = "example-icon.png";
        FString layoutLocation = "DefaultLayout";

        bool bLoadLayout = true;
        bool bSaveLayout = true;

        bool fullscreen = false;
        bool bResizeable = true;
        bool bSurfaceTransparent = false;
        bool bHidden = false;
        bool bFocused = true;

        FVector2 aspectRatioSizeLimit = { -1, -1 };
        FVector4 sizeLimits = { -1, -1, -1, -1 };

        bool bDecorated = true;
        bool bMaximised = false;
    };

    typedef UImGui_MonitorState MonitorState;

    // CAUTION: THIS WILL NOT WORK ON EMSCRIPTEN
    struct UIMGUI_PUBLIC_API Monitor
    {
    public:
        Monitor() = default;
        explicit Monitor(GLFWmonitor* monitor) noexcept;

        // Event safety - begin, style, post-begin
        [[nodiscard]] FVector2 getPhysicalSize() const noexcept;

        // Event safety - begin, style, post-begin
        [[nodiscard]] FVector2 getContentScale() const noexcept;

        // Event safety - begin, style, post-begin
        [[nodiscard]] FVector2 getVirtualPosition() const noexcept;

        // Event safety - begin, style, post-begin
        // Returns work area as FVector4 where x = x position, y = y position, z = width, w = height
        [[nodiscard]] FVector4 getWorkArea() const noexcept;

        // Event safety - begin, style, post-begin
        // May not be unique
        [[nodiscard]] FString getName() const noexcept;

        // Event safety - begin, style, post-begin
        void pushEvent(const TFunction<void(Monitor&, MonitorState)>& f) noexcept;

        void* additionalData = nullptr;
        size_t additionalDataSize = 0;

        // This is made to circumvent the inability to access the private variables of this class by the C API. This is
        // mostly due to header file structure constraints in our current implementation, as otherwise, friend functions
        // would do the job.
        class UIMGUI_PUBLIC_API CInternalGetMonitorClassDoNotTouch
        {
        public:
            static UImGui_CMonitorData UImGui_Window_getWindowMonitor();
            static void pushGlobalMonitorCallbackFun(const Monitor& monitor, UImGui::MonitorState state,
                                                    UImGui_Window_pushGlobalMonitorCallbackFun f);
            static void UImGui_Monitor_pushEvent(UImGui_CMonitorData* data, UImGui_Monitor_EventsFun f);
            static void UImGui_Monitor_setWindowMonitor(const UImGui_CMonitorData* monitor);
            static UImGui_CMonitorData* UImGui_Window_getMonitors(size_t* size);
        };
    private:
        friend class Window;
        friend class WindowInternal;

        TVector<TFunction<void(Monitor&, MonitorState)>> events;
        GLFWmonitor* monitor = nullptr;
    };

    class WindowInternal
    {
    public:
        WindowInternal() noexcept;
        WindowInternal(const WindowInternal&) = delete;
        void operator=(WindowInternal const&) = delete;

        [[nodiscard]] GLFWwindow* data() const noexcept;
        bool& resized() noexcept;

    private:
        friend class Window;
        friend class Input;
        friend class RendererInternal;
        friend class Global;
        friend class Layouts;
        friend void ::UImGui_Window_pushWindowOSDragDropCallback(UImGui_Window_pushWindowOSDragDropCallbackFun f);

        void updateKeyState() noexcept;

        FVector2 windowSize = { 800.0f, 600.0f };
        FVector2 windowSizeInScreenCoords{};

        TArray<CKeyState, 350> keys{};
        TVector<InputAction> inputActionList{};

        void saveConfig(bool bSaveKeybindings) noexcept;
        void openConfig();
        void configureDefaultHints() const noexcept;

        void setTitle(String title) noexcept;
        void setIcon(String name) const noexcept;

        FVector2 getMousePositionChange() noexcept;
        FVector2 getScroll() noexcept;

        void createWindow() noexcept;
        void destroyWindow() const noexcept;

        void configureCallbacks() const noexcept;
        static void framebufferSizeCallback(GLFWwindow* window, int width, int height) noexcept;
        static void keyboardInputCallback(GLFWwindow* window, int key, int scanCode, int action, int mods) noexcept;
        static void mouseKeyInputCallback(GLFWwindow* window, int button, int action, int mods) noexcept;
        static void mouseCursorPositionCallback(GLFWwindow* window, double xpos, double ypos) noexcept;
        static void scrollInputCallback(GLFWwindow* window, double xoffset, double yoffset) noexcept;
        static void windowPositionCallback(GLFWwindow* window, int xpos, int ypos) noexcept;

        static void windowSizeCallback(GLFWwindow* window, int width, int height) noexcept;
        static void windowCloseCallback(GLFWwindow* window) noexcept;
        static void windowFocusCallback(GLFWwindow* window, int focused) noexcept;
        static void windowIconifyCallback(GLFWwindow* window, int iconified) noexcept;
        static void windowContentScaleCallback(GLFWwindow* window, float x, float y) noexcept;
        static void windowRefreshCallback(GLFWwindow* window) noexcept;
        static void windowMaximisedCallback(GLFWwindow* window, int maximised) noexcept;

        static void monitorCallback(GLFWmonitor* monitor, int event) noexcept;

        static void windowOSDragDropCallback(GLFWwindow* window, int count, const char** paths) noexcept;

        // As of now, only supported on X11, Win32 & macOS
        void setWindowAlwaysOnTop() const noexcept;

        // As of now, only supported on X11, Win32 & macOS
        void setWindowAlwaysBelow() const noexcept;

        // As of now, only supported on X11 & Win32
        void setShowWindowInPager(bool bShowInPagerr) noexcept;

        // As of now, only supported on X11 & Win32
        void setShowWindowOnTaskbar(bool bShowOnTaskbarr) noexcept;

        // As of now, only supported on X11
        void setWindowType(const char* type) const noexcept;

        // As of now, only supported on X11, Win32 and macOS
        // On macOS this is an integer representation of the underlying pointer
        [[nodiscard]] size_t getWindowID() const noexcept;

        bool bShowOnPager = true;
        bool bShowOnTaskbar = true;

        TVector<TFunction<void(int, int)>> windowResizeCallbackList;
        TVector<TFunction<void(int, int)>> windowResizeInScreenCoordCallbackList;
        TVector<TFunction<void(void)>> windowCloseCallbackList;
        TVector<TFunction<void(bool)>> windowFocusCallbackList;
        TVector<TFunction<void(bool)>> windowIconifiedCallbackList;
        TVector<TFunction<void(FVector2)>> windowPositionChangeCallbackList;
        TVector<TFunction<void(FVector2)>> windowContentScaleChangeCallbackList;
        TVector<TFunction<void(void)>> windowRefreshCallbackList;
        TVector<TFunction<void(bool)>> windowMaximisedCallbackList;
        TVector<TFunction<void(Monitor&, MonitorState)>> windowMonitorCallbackList;
        TVector<TFunction<void(String)>> dragDropPathCallbackList;

        TVector<Monitor> monitors;

        GLFWwindow* windowMain = nullptr;
        WindowData windowData;

        bool bFirstMove = true;
        bool bResized = false;

        FVector2 mousePos = { 0.0f, 0.0f };
        FVector2 mouseLastPos = { 0.0f, 0.0f };
        FVector2 mouseOffset = { 0.0f, 0.0f };

        FVector2 scroll{};

        FVector2 windowLastPos = { 0.0f, 0.0f };
        FVector2 windowCurrentPos = { 0.0f, 0.0f };
    };
}
