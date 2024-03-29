#pragma once
#include <Core/Events/Input.hpp>
#include <array>
#include <C/Internal/CMonitor.h>

struct GLFWwindow;
namespace UImGui
{
    struct UIMGUI_PUBLIC_API WindowData
    {
        FString name = "UntitledImGuiFramework Application";
        FString iconLocation = "example-icon.png";
        FString layoutLocation = "DefaultLayout";

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

    struct UIMGUI_PUBLIC_API Monitor
    {
    public:
        Monitor() = default;
        explicit Monitor(GLFWmonitor* monitor) noexcept;

        // Event safety - begin, style, post-begin
        FVector2 getPhysicalSize() noexcept;

        // Event safety - begin, style, post-begin
        FVector2 getContentScale() noexcept;

        // Event safety - begin, style, post-begin
        FVector2 getVirtualPosition() noexcept;

        // Event safety - begin, style, post-begin
        // Returns work area as FVector4 where x = x position, y = y position, z = width, w = height
        FVector4 getWorkArea() noexcept;

        // Event safety - begin, style, post-begin
        // May not be unique
        FString getName() noexcept;

        // Event safety - begin, style, post-begin
        void pushEvent(const std::function<void(Monitor&, MonitorState)>& f) noexcept;

        void* additionalData = nullptr;
        size_t additionalDataSize = 0;

        // This is made to circumvent the inability to access the private variables of this class by the C API. This is
        // mostly due to header file structure constraints in our current implementation, as otherwise, friend functions
        // would do the job.
        class UIMGUI_PUBLIC_API CInternalGetMonitorClassDoNotTouch
        {
        public:
            static UImGui_CMonitorData UImGui_Window_getWindowMonitor();
            static void pushGlobalMonitorCallbackFun(UImGui::Monitor& monitor, UImGui::MonitorState state,
                                                    UImGui_Window_pushGlobalMonitorCallbackFun f);
            static void UImGui_Monitor_pushEvent(UImGui_CMonitorData* data, UImGui_Monitor_EventsFun f);
            static void UImGui_Monitor_setWindowMonitor(UImGui_CMonitorData* monitor);
            static UImGui_CMonitorData* UImGui_Window_getMonitors(size_t* size);
        };
    private:
        friend class Window;
        friend class WindowInternal;

        std::vector<std::function<void(Monitor&, MonitorState)>> events;
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

        void close() noexcept;

        std::vector<std::function<void(const char**, size_t size)>> dragDropPathCCallbackList;
    private:
        friend class Window;
        friend class Input;
        friend class RendererInternal;
        friend class Global;

        void updateKeyState() noexcept;

        FVector2 windowSize = { 800.0f, 600.0f };
        FVector2 windowSizeInScreenCoords;

        std::array<uint16_t, 350> keys{};
        std::vector<InputAction> inputActionList{};

        void saveConfig(bool bSaveKeybindings) noexcept;
        void openConfig();
        void setTitle(String title) noexcept;
        void setIcon(String name) noexcept;

        FVector2 getMousePositionChange() noexcept;
        FVector2 getScroll() noexcept;

        void createWindow() noexcept;
        void destroyWindow() noexcept;

        void configureCallbacks() noexcept;
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

        static void windowErrorCallback(int code, const char* description) noexcept;

        // As of now, only supported in X11
        // TODO: Port to Win32
        // TODO: Port to Wayland
        void setWindowAlwaysOnTop() noexcept;

        // As of now, only supported in X11
        // TODO: Port to Win32
        // TODO: Port to Wayland
        void setWindowAlwaysBelow() noexcept;

        // As of now, only supported in X11
        // TODO: Port to Win32
        // TODO: Port to Wayland
        void disableWindowMoving() noexcept;

        // As of now, only supported in X11
        // TODO: Port to Win32
        // TODO: Port to Wayland
        void setShowWindowInPager(bool bShowInPagerr) noexcept;

        // As of now, only supported in X11
        // TODO: Port to Win32
        // TODO: Port to Wayland
        void setShowWindowOnTaskbar(bool bShowOnTaskbarr) noexcept;

        // As of now, only supported in X11
        // TODO: Port to Win32
        // TODO: Port to Wayland
        void setWindowType(const char* type) noexcept;

        bool bShowOnPager = true;
        bool bShowOnTaskbar = true;

        std::vector<std::function<void(int, int)>> windowResizeCallbackList;
        std::vector<std::function<void(int, int)>> windowResizeInScreenCoordCallbackList;
        std::vector<std::function<void(void)>> windowCloseCallbackList;
        std::vector<std::function<void(bool)>> windowFocusCallbackList;
        std::vector<std::function<void(bool)>> windowIconifiedCallbackList;
        std::vector<std::function<void(FVector2)>> windowPositionChangeCallbackList;
        std::vector<std::function<void(FVector2)>> windowContentScaleChangeCallbackList;
        std::vector<std::function<void(void)>> windowRefreshCallbackList;
        std::vector<std::function<void(bool)>> windowMaximisedCallbackList;
        std::vector<std::function<void(Monitor&, MonitorState)>> windowMonitorCallbackList;

        std::vector<std::function<void(std::vector<FString>&)>> dragDropPathCallbackList;

        std::vector<std::function<void(int, const char*)>> windowErrorCallbackList;

        std::vector<FString> dragDropPaths;

        std::vector<Monitor> monitors;

        GLFWwindow* windowMain = nullptr;
        WindowData windowData;

        bool bFirstMove = true;
        bool bResized = false;

        FVector2 mousePos = { 0.0f, 0.0f };
        FVector2 mouseLastPos = { 0.0f, 0.0f };
        FVector2 mouseOffset = { 0.0f, 0.0f };

        FVector2 scroll;

        FVector2 windowLastPos = { 0.0f, 0.0f };
        FVector2 windowCurrentPos = { 0.0f, 0.0f };
    };
}
