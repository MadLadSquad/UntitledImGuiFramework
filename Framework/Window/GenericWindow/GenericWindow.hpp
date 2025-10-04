#pragma once
#include <Core/Core.hpp>
#include <C/Window/Keys.h>
#include <Core/Interfaces/Input.hpp>
#include <C/Interfaces/CWindowInterface.h>
#include <Renderer/RendererUtils.hpp>

#include "GenericMonitor.hpp"

#ifndef __EMSCRIPTEN__
    #include <vulkan/vulkan.h>
#endif

namespace UImGui
{
    typedef UImGui_CursorVisibilityState CursorVisibilityState;
    typedef UImGui_WindowPlatform WindowPlatform;

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

    class UIMGUI_PUBLIC_API GenericWindow
    {
    public:
        GenericWindow() noexcept = default;
        virtual ~GenericWindow() noexcept = default;

        virtual void createWindow() noexcept = 0;
        virtual void destroyWindow() noexcept = 0;

        // -------------------------------------------------------------------------------------------------------------
        // ---------------------------------------- Renderer and UI integration ----------------------------------------
        // -------------------------------------------------------------------------------------------------------------

#ifndef __EMSCRIPTEN__
        virtual void ImGuiInitFor_Vulkan() noexcept = 0;
#endif
        virtual void ImGuiInitFor_OpenGL() noexcept = 0;
        virtual void ImGuiInitFor_Other() noexcept = 0;

        virtual void ImGuiInstallCallbacks() noexcept = 0;
        virtual void ImGuiNewFrame() noexcept = 0;
        virtual void ImGuiShutdown() noexcept = 0;

        virtual bool shouldRender() noexcept = 0;
        virtual void pollEvents(double& now, double& deltaTime, double& lastTime) noexcept = 0;
        virtual void waitEventsTimeout(double timeout) noexcept = 0;
        virtual void waitEvents() noexcept = 0;

        virtual RendererUtils::OpenGL::Context* OpenGL_createContext() noexcept = 0;
        virtual RendererUtils::OpenGL::Context* OpenGL_getCurrentContext() noexcept = 0;
        virtual void OpenGL_setCurrentContext(RendererUtils::OpenGL::Context* ctx) noexcept = 0;
        virtual void OpenGL_destroyContext(RendererUtils::OpenGL::Context* ctx) noexcept = 0;

        virtual void OpenGL_swapBuffers() noexcept = 0;
        virtual void OpenGL_setSwapInterval(int interval) noexcept = 0;
        virtual void OpenGL_setHints(int majorVersion, int minorVersion, RendererClientAPI clientApi, RendererUtils::OpenGL::Profile profile, bool bForwardCompatible, uint32_t samples) noexcept = 0;
        virtual RendererUtils::OpenGL::GetProcAddressFun OpenGL_getProcAddressFunction() noexcept = 0;

        virtual void setupManualRenderingHints() noexcept = 0;

#ifndef __EMSCRIPTEN__
        virtual VkResult Vulkan_createWindowSurface(VkInstance instance, const VkAllocationCallbacks* allocator, VkSurfaceKHR* surface) noexcept = 0;
        virtual void Vulkan_fillInstanceAndLayerExtensions(TVector<const char*>& instanceExtensions, TVector<const char*>& instanceLayers) noexcept = 0;
#endif

        // -------------------------------------------------------------------------------------------------------------
        // --------------------------------------------- Input integration ---------------------------------------------
        // -------------------------------------------------------------------------------------------------------------

        virtual CKeyState getKey(CKeys key) noexcept = 0;

        FVector2 getMousePositionChange() noexcept;
        [[nodiscard]] FVector2 getCurrentMousePosition() const noexcept;
        [[nodiscard]] FVector2 getLastMousePosition() const noexcept;

        FVector2 getScroll() noexcept;

        virtual void setCursorVisibility(CursorVisibilityState visibility) noexcept = 0;

        virtual void setRawMouseMotion(bool bEnable) noexcept = 0;
        virtual bool getRawMouseMotion() noexcept = 0;

        // -------------------------------------------------------------------------------------------------------------
        // ---------------------------------------------- Window interface ---------------------------------------------
        // -------------------------------------------------------------------------------------------------------------

        virtual void setTitle(String name) noexcept = 0;
        virtual String getTitle() noexcept = 0;
        virtual void setTitleSetting(String name) noexcept = 0;
        virtual String getTitleSetting() noexcept = 0;

        virtual void setIcon(String name) noexcept = 0;
        virtual String getIconLocation() noexcept = 0;
        virtual String getIconLocationSetting() noexcept = 0;
        virtual void setIconLocationSetting(String location) noexcept = 0;

        virtual float getAspectRatio() noexcept = 0;

        virtual FVector2 getCurrentWindowPosition() noexcept = 0;
        virtual FVector2 getLastWindowPosition() noexcept = 0;
        virtual FVector2 getWindowPositionChange() noexcept = 0;

        virtual void setCurrentWindowPosition(FVector2 pos) noexcept = 0;
        virtual void pushWindowPositionChangeCallback(const TFunction<void(FVector2)>& f) noexcept = 0;

        virtual FVector2 getWindowSize() noexcept = 0;
        virtual FVector2& getWindowSizeSetting() noexcept = 0;

        virtual bool getWindowFullscreen() noexcept = 0;
        virtual bool& getWindowFullscreenSetting() noexcept = 0;
        virtual void setWindowFullscreen(bool bFullscreen) noexcept = 0;

        virtual void saveSettings(bool bSaveKeybinds) noexcept;
        void openConfig() noexcept;
        virtual void refreshSettings() noexcept = 0;

        virtual void close() noexcept = 0;
        virtual void pushWindowCloseCallback(const TFunction<void(void)>& f) noexcept = 0;

        virtual void Platform_setWindowAlwaysOnTop() noexcept = 0;
        virtual void Platform_setWindowAlwaysOnBottom() noexcept = 0;

        virtual void Platform_setWindowShowingOnPager(bool bShowInPager) noexcept = 0;
        virtual bool Platform_getWindowShowingOnPager() noexcept = 0;

        virtual void Platform_setWindowShowingOnTaskbar(bool bShowOnTaskbar) noexcept = 0;
        virtual bool Platform_getWindowShowingOnTaskbar() noexcept = 0;

        virtual void Platform_setWindowType(String type) noexcept = 0;
        virtual size_t Platform_getWindowID() noexcept = 0;

        virtual void* Platform_getNativeWindowHandle() noexcept = 0;
        virtual WindowPlatform Platform_getCurrentWindowPlatform() noexcept = 0;
        virtual void* Platform_getNativeDisplay() noexcept = 0;

        virtual void setWindowSizeInScreenCoords(FVector2 sz) noexcept = 0;
        virtual FVector2 getWindowSizeInScreenCoords() noexcept = 0;
        virtual void pushWindowResizedInScreenCoordsCallback(const TFunction<void(int, int)>& f) noexcept = 0;

        virtual void setWindowResizeable(bool bResizeable) noexcept = 0;
        virtual bool& getWindowResizeableSetting() noexcept = 0;
        virtual bool getWindowCurrentlyResizeable() noexcept = 0;
        virtual void pushWindowResizeCallback(const TFunction<void(int, int)>& f) noexcept = 0;

        virtual void requestWindowAttention() noexcept = 0;

        virtual void hideWindow() noexcept = 0;
        virtual void showWindow() noexcept = 0;
        virtual bool& getWindowHiddenSetting() noexcept = 0;
        virtual bool getWindowCurrentlyHidden() noexcept = 0;

        virtual bool getWindowSurfaceTransparent() noexcept = 0;
        virtual void setWindowSurfaceTransparent(bool bTransparent) noexcept = 0;
        virtual bool& getWindowSurfaceTransparentSetting() noexcept = 0;

        virtual void focusWindow() noexcept = 0;
        virtual bool& getWindowFocusedSetting() noexcept = 0;
        virtual bool getWindowCurrentlyFocused() noexcept = 0;
        virtual void pushWindowFocusCallback(const TFunction<void(bool)>& f) noexcept = 0;

        virtual void iconifyWindow() noexcept = 0;
        virtual void restoreWindowState() noexcept = 0;
        virtual void pushWindowIconifyCallback(const TFunction<void(bool)>& f) noexcept = 0;
        virtual bool getWindowIconified() noexcept = 0;

        virtual FVector2 getWindowContentScale() noexcept = 0;
        virtual void pushWindowContentScaleCallback(const TFunction<void(FVector2)>& f) noexcept = 0;

        virtual void setSizeLimits(FVector2 min, FVector2 max) noexcept = 0;
        virtual void setSizeLimitByAspectRatio(FVector2 ratio) noexcept = 0;
        virtual FVector4& getSizeLimits() noexcept = 0;
        virtual FVector2& getAspectRatioSizeLimits() noexcept = 0;

        virtual FVector4 getWindowDecorationFrameDistances() noexcept = 0;
        virtual bool getCurrentWindowDecoratedState() noexcept = 0;
        virtual bool& getWindowDecoratedSetting() noexcept = 0;
        virtual void setWindowDecorated(bool bDecorated) noexcept = 0;

        virtual void pushWindowRefreshCallback(const TFunction<void(void)>& f) noexcept = 0;

        virtual void maximiseWindow() noexcept = 0;
        virtual bool& getWindowMaximisedSetting() noexcept = 0;
        virtual void pushWindowMaximiseCallback(const TFunction<void(bool)>& f) noexcept = 0;
        virtual bool getWindowCurrentlyMaximised() noexcept = 0;

        virtual Monitor getWindowMonitor() noexcept = 0;
        virtual Monitor getPrimaryMonitor() noexcept = 0;
        virtual const TVector<Monitor>& getMonitors() noexcept = 0;

        // Event safety - begin, style, post-begin
        virtual void pushWindowOSDragDropCallback(const TFunction<void(const FString&)>& f) noexcept = 0;

        virtual void* getInternal() noexcept = 0;
        virtual GenericWindow* get() noexcept = 0;
    protected:
        friend void ::UImGui_Window_pushWindowOSDragDropCallback(UImGui_Window_pushWindowOSDragDropCallbackFun f);
        friend class Input;
        friend class Layouts;
        friend class Monitor;

        bool bFirstMove = true;
        bool bResized = false;

        FVector2 mousePos = { 0.0f, 0.0f };
        FVector2 mouseLastPos = { 0.0f, 0.0f };
        FVector2 mouseOffset = { 0.0f, 0.0f };

        FVector2 scroll{};

        FVector2 windowLastPos = { 0.0f, 0.0f };
        FVector2 windowCurrentPos = { 0.0f, 0.0f };

        bool bShowOnPager = true;
        bool bShowOnTaskbar = true;

        TVector<TFunction<void(int, int)>> windowResizeCallbackList;
        TVector<TFunction<void(int, int)>> windowResizeInScreenCoordCallbackList;
        TVector<TFunction<void()>> windowCloseCallbackList;
        TVector<TFunction<void(bool)>> windowFocusCallbackList;
        TVector<TFunction<void(bool)>> windowIconifiedCallbackList;
        TVector<TFunction<void(FVector2)>> windowPositionChangeCallbackList;
        TVector<TFunction<void(FVector2)>> windowContentScaleChangeCallbackList;
        TVector<TFunction<void(void)>> windowRefreshCallbackList;
        TVector<TFunction<void(bool)>> windowMaximisedCallbackList;
        TVector<TFunction<void(String)>> dragDropPathCallbackList;

        FVector2 windowSizeS = { 800.0f, 600.0f };
        FVector2 windowSizeInScreenCoords{};

        WindowData windowData;
        TVector<InputAction> inputActionList{};

        GenericMonitor* monitor = nullptr;
    };
}
