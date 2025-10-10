#pragma once
#include <Window/GenericWindow/GenericWindow.hpp>

struct GLFWwindow;
namespace UImGui
{
    class UIMGUI_PUBLIC_API MonitorGLFW final : public GenericMonitor
    {
    public:
        MonitorGLFW() noexcept = default;
        ~MonitorGLFW() noexcept override = default;

        FVector4 getWorkArea(MonitorData& data) noexcept override;
        FVector2 getSize(MonitorData& data) noexcept override;

        String getName(MonitorData& data) noexcept override;

        double getContentScale(MonitorData& data) noexcept override;
        float getPixelDensity(MonitorData& data) noexcept override;

        void* getPlatformHandle(MonitorData& data) noexcept override;
    };

    class UIMGUI_PUBLIC_API WindowGLFW final : public GenericWindow
    {
    public:
        WindowGLFW() noexcept;
        ~WindowGLFW() noexcept override = default;

        void createWindow() noexcept override;
        void destroyWindow() noexcept override;

        // -------------------------------------------------------------------------------------------------------------
        // ---------------------------------------- Renderer and UI integration ----------------------------------------
        // -------------------------------------------------------------------------------------------------------------

#ifndef __EMSCRIPTEN__
        void ImGuiInitFor_Vulkan() noexcept override;
#endif
        void ImGuiInitFor_OpenGL() noexcept override;
        void ImGuiInitFor_Other() noexcept override;

        void ImGuiInstallCallbacks() noexcept override;
        void ImGuiNewFrame() noexcept override;
        void ImGuiShutdown() noexcept override;

        bool shouldRender() noexcept override;
        void pollEvents(double& now, double& deltaTime, double& lastTime) noexcept override;
        void waitEventsTimeout(double timeout) noexcept override;
        void waitEvents() noexcept override;

        RendererUtils::OpenGL::Context* OpenGL_createContext() noexcept override;
        RendererUtils::OpenGL::Context* OpenGL_getCurrentContext() noexcept override;
        void OpenGL_setCurrentContext(RendererUtils::OpenGL::Context* ctx) noexcept override;
        void OpenGL_destroyContext(RendererUtils::OpenGL::Context* ctx) noexcept override;

        void OpenGL_swapBuffers() noexcept override;
        void OpenGL_setSwapInterval(int interval) noexcept override;
        void OpenGL_setHints(int majorVersion, int minorVersion, RendererClientAPI clientApi, RendererUtils::OpenGL::Profile profile, bool bForwardCompatible, uint32_t samples) noexcept override;
        RendererUtils::OpenGL::GetProcAddressFun OpenGL_getProcAddressFunction() noexcept override;

        void setupManualRenderingHints() noexcept override;

#ifndef __EMSCRIPTEN__
        VkResult Vulkan_createWindowSurface(VkInstance instance, const VkAllocationCallbacks* allocator, VkSurfaceKHR* surface) noexcept override;
        void Vulkan_fillInstanceAndLayerExtensions(TVector<const char*>& instanceExtensions, TVector<const char*>& instanceLayers) noexcept override;
#endif

        // -------------------------------------------------------------------------------------------------------------
        // --------------------------------------------- Input integration ---------------------------------------------
        // -------------------------------------------------------------------------------------------------------------

        CKeyState getKey(CKeys key) noexcept override;

        void setCursorVisibility(CursorVisibilityState visibility) noexcept override;

        void setRawMouseMotion(bool bEnable) noexcept override;
        bool getRawMouseMotion() noexcept override;

        // -------------------------------------------------------------------------------------------------------------
        // ---------------------------------------------- Window interface ---------------------------------------------
        // -------------------------------------------------------------------------------------------------------------

        void setTitle(String name) noexcept override;
        String getTitle() noexcept override;
        void setTitleSetting(String name) noexcept override;
        String getTitleSetting() noexcept override;

        void setIcon(String name) noexcept override;
        String getIconLocation() noexcept override;
        String getIconLocationSetting() noexcept override;
        void setIconLocationSetting(String location) noexcept override;

        float getAspectRatio() noexcept override;

        FVector2 getCurrentWindowPosition() noexcept override;
        FVector2 getLastWindowPosition() noexcept override;
        FVector2 getWindowPositionChange() noexcept override;

        void setCurrentWindowPosition(FVector2 pos) noexcept override;
        void pushWindowPositionChangeCallback(const TFunction<void(FVector2)>& f) noexcept override;

        FVector2 getWindowSize() noexcept override;
        FVector2& getWindowSizeSetting() noexcept override;

        bool getWindowFullscreen() noexcept override;
        bool& getWindowFullscreenSetting() noexcept override;
        void setWindowFullscreen(bool bFullscreen) noexcept override;

        void saveSettings(bool bSaveKeybinds) noexcept override;
        void refreshSettings() noexcept override;

        void close() noexcept override;
        void pushWindowCloseCallback(const TFunction<void(void)>& f) noexcept override;

        void Platform_setWindowAlwaysOnTop() noexcept override;
        void Platform_setWindowAlwaysOnBottom() noexcept override;

        void Platform_setWindowShowingOnPager(bool bShowInPager) noexcept override;
        bool Platform_getWindowShowingOnPager() noexcept override;

        void Platform_setWindowShowingOnTaskbar(bool bShowOnTaskbar) noexcept override;
        bool Platform_getWindowShowingOnTaskbar() noexcept override;

        void Platform_setWindowType(String type) noexcept override;
        size_t Platform_getWindowID() noexcept override;

        void* Platform_getNativeWindowHandle() noexcept override;
        WindowPlatform Platform_getCurrentWindowPlatform() noexcept override;
        void* Platform_getNativeDisplay() noexcept override;

        void setWindowSizeInScreenCoords(FVector2 sz) noexcept override;
        FVector2 getWindowSizeInScreenCoords() noexcept override;
        void pushWindowResizedInScreenCoordsCallback(const TFunction<void(int, int)>& f) noexcept override;

        void setWindowResizeable(bool bResizeable) noexcept override;
        bool& getWindowResizeableSetting() noexcept override;
        bool getWindowCurrentlyResizeable() noexcept override;
        void pushWindowResizeCallback(const TFunction<void(int, int)>& f) noexcept override;

        void requestWindowAttention() noexcept override;

        void hideWindow() noexcept override;
        void showWindow() noexcept override;
        bool& getWindowHiddenSetting() noexcept override;
        bool getWindowCurrentlyHidden() noexcept override;

        bool getWindowSurfaceTransparent() noexcept override;
        void setWindowSurfaceTransparent(bool bTransparent) noexcept override;
        bool& getWindowSurfaceTransparentSetting() noexcept override;

        void focusWindow() noexcept override;
        bool& getWindowFocusedSetting() noexcept override;
        bool getWindowCurrentlyFocused() noexcept override;
        void pushWindowFocusCallback(const TFunction<void(bool)>& f) noexcept override;

        void iconifyWindow() noexcept override;
        void restoreWindowState() noexcept override;
        void pushWindowIconifyCallback(const TFunction<void(bool)>& f) noexcept override;
        bool getWindowIconified() noexcept override;

        FVector2 getWindowContentScale() noexcept override;
        void pushWindowContentScaleCallback(const TFunction<void(FVector2)>& f) noexcept override;

        void setSizeLimits(FVector2 min, FVector2 max) noexcept override;
        void setSizeLimitByAspectRatio(FVector2 ratio) noexcept override;
        FVector4& getSizeLimits() noexcept override;
        FVector2& getAspectRatioSizeLimits() noexcept override;

        FVector4 getWindowDecorationFrameDistances() noexcept override;
        bool getCurrentWindowDecoratedState() noexcept override;
        bool& getWindowDecoratedSetting() noexcept override;
        void setWindowDecorated(bool bDecorated) noexcept override;

        void pushWindowRefreshCallback(const TFunction<void(void)>& f) noexcept override;

        void maximiseWindow() noexcept override;
        bool& getWindowMaximisedSetting() noexcept override;
        void pushWindowMaximiseCallback(const TFunction<void(bool)>& f) noexcept override;
        bool getWindowCurrentlyMaximised() noexcept override;

        Monitor getWindowMonitor() noexcept override;
        Monitor getPrimaryMonitor() noexcept override;
        const TVector<Monitor>& getMonitors() noexcept override;

        void pushWindowOSDragDropCallback(const TFunction<void(const FString&)>& f) noexcept override;

        void* getInternal() noexcept override;
        GenericWindow* get() noexcept override;
    private:
        GLFWwindow* window = nullptr;
        TArray<CKeyState, 350> keys{};
        TVector<Monitor> monitors{};

        MonitorGLFW monitorGLFW{};

        // For supporting getting the current icon location when setting the icon, since GLFW has no utility function
        // to query for this
        FString currentIconLocation{};

        void configureDefaultHints() const noexcept;

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

        static void windowOSDragDropCallback(GLFWwindow* window, int count, const char** paths) noexcept;
    };
}