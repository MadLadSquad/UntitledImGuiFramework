#include "CGenericWindow.h"
#include <Window/GenericWindow/GenericWindow.hpp>

class UIMGUI_PUBLIC_API CGenericWindow final : public UImGui::GenericWindow
{
public:
    CGenericWindow() noexcept = default;
    explicit CGenericWindow(UImGui_CGenericWindowInitInfo* info) noexcept
    {
        initInfo = info;
        monitor = static_cast<UImGui::GenericMonitor*>(initInfo->monitor);
    }

    ~CGenericWindow() noexcept override
    {
        if (initInfo->monitor != nullptr)
            UImGui_CGenericMonitor_free(initInfo->monitor);
    }

    void createWindow() noexcept override
    {
        initInfo->createWindow(initInfo);
    }

    void destroyWindow() noexcept override
    {
        initInfo->destroyWindow(initInfo);
    }


    // -------------------------------------------------------------------------------------------------------------
    // ---------------------------------------- Renderer and UI integration ----------------------------------------
    // -------------------------------------------------------------------------------------------------------------

#ifndef __EMSCRIPTEN__
    void ImGuiInitFor_Vulkan() noexcept override
    {
        initInfo->ImGuiInitFor_Vulkan(initInfo);
    }
#endif

    void ImGuiInitFor_OpenGL() noexcept override
    {
        initInfo->ImGuiInitFor_OpenGL(initInfo);
    }

    void ImGuiInitFor_Other() noexcept override
    {
        initInfo->ImGuiInitFor_Other(initInfo);
    }


    void ImGuiInstallCallbacks() noexcept override
    {
        initInfo->ImGuiInstallCallbacks(initInfo);
    }

    void ImGuiNewFrame() noexcept override
    {
        initInfo->ImGuiNewFrame(initInfo);
    }

    void ImGuiShutdown() noexcept override
    {
        initInfo->ImGuiShutdown(initInfo);
    }


    bool shouldRender() noexcept override
    {
        return initInfo->shouldRender(initInfo);
    }

    void pollEvents(double& now, double& deltaTime, double& lastTime) noexcept override
    {
        initInfo->pollEvents(initInfo, &now, &deltaTime, &lastTime);
    }

    void waitEventsTimeout(const double timeout) noexcept override
    {
        initInfo->waitEventsTimeout(initInfo, timeout);
    }

    void waitEvents() noexcept override
    {
        initInfo->waitEvents(initInfo);
    }


    UImGui::RendererUtils::OpenGL::Context* OpenGL_createContext() noexcept override
    {
        return initInfo->OpenGL_createContext(initInfo);
    }

    UImGui::RendererUtils::OpenGL::Context* OpenGL_getCurrentContext() noexcept override
    {
        return initInfo->OpenGL_getCurrentContext(initInfo);
    }

    void OpenGL_setCurrentContext(UImGui::RendererUtils::OpenGL::Context* ctx) noexcept override
    {
        initInfo->OpenGL_setCurrentContext(initInfo, ctx);
    }

    void OpenGL_destroyContext(UImGui::RendererUtils::OpenGL::Context* ctx) noexcept override
    {
        initInfo->OpenGL_destroyContext(initInfo, ctx);
    }


    void OpenGL_swapBuffers() noexcept override
    {
        initInfo->OpenGL_swapBuffers(initInfo);
    }

    void OpenGL_setSwapInterval(const int interval) noexcept override
    {
        initInfo->OpenGL_setSwapInterval(initInfo, interval);
    }

    void OpenGL_setHints(const int majorVersion, const int minorVersion, const UImGui::RendererClientAPI clientApi, const UImGui::RendererUtils::OpenGL::Profile profile, const bool bForwardCompatible, const uint32_t samples) noexcept override
    {
        initInfo->OpenGL_setHints(initInfo, majorVersion, minorVersion, clientApi, profile, bForwardCompatible, samples);
    }

    UImGui::RendererUtils::OpenGL::GetProcAddressFun OpenGL_getProcAddressFunction() noexcept override
    {
        return initInfo->OpenGL_getProcAddressFunction(initInfo);
    }


    void setupManualRenderingHints() noexcept override
    {
        initInfo->setupManualRenderingHints(initInfo);
    }

#ifndef __EMSCRIPTEN__
    VkResult Vulkan_createWindowSurface(VkInstance instance, const VkAllocationCallbacks* allocator, VkSurfaceKHR* surface) noexcept override
    {
        return initInfo->Vulkan_createWindowSurface(initInfo, instance, allocator, surface);
    }

    void Vulkan_fillInstanceAndLayerExtensions(UImGui::TVector<const char*>& instanceExtensions, UImGui::TVector<const char*>& instanceLayers) noexcept override
    {
        return initInfo->Vulkan_fillInstanceAndLayerExtensions(initInfo, instanceExtensions.data(), instanceExtensions.size(), instanceLayers.data(), instanceLayers.size());
    }
#endif


    // -------------------------------------------------------------------------------------------------------------
    // --------------------------------------------- Input integration ---------------------------------------------
    // -------------------------------------------------------------------------------------------------------------

    CKeyState getKey(const CKeys key) noexcept override
    {
        return initInfo->getKey(initInfo, key);
    }


    void setCursorVisibility(const UImGui::CursorVisibilityState visibility) noexcept override
    {
        initInfo->setCursorVisibility(initInfo, visibility);
    }


    void setRawMouseMotion(const bool bEnable) noexcept override
    {
        initInfo->setRawMouseMotion(initInfo, bEnable);
    }

    bool getRawMouseMotion() noexcept override
    {
        return initInfo->getRawMouseMotion(initInfo);
    }


    // -------------------------------------------------------------------------------------------------------------
    // ---------------------------------------------- Window interface ---------------------------------------------
    // -------------------------------------------------------------------------------------------------------------

    void setTitle(const UImGui::String name) noexcept override
    {
        initInfo->setTitle(initInfo, name);
    }

    UImGui::String getTitle() noexcept override
    {
        return initInfo->getTitle(initInfo);
    }

    void setTitleSetting(const UImGui::String name) noexcept override
    {
        initInfo->setTitleSetting(initInfo, name);
    }

    UImGui::String getTitleSetting() noexcept override
    {
        return initInfo->getTitleSetting(initInfo);
    }

    void setIcon(const UImGui::String name) noexcept override
    {
        initInfo->setIcon(initInfo, name);
    }

    UImGui::String getIconLocation() noexcept override
    {
        return initInfo->getIconLocation(initInfo);
    }

    UImGui::String getIconLocationSetting() noexcept override
    {
        return initInfo->getIconLocationSetting(initInfo);
    }

    void setIconLocationSetting(const UImGui::String location) noexcept override
    {
        initInfo->setIconLocationSetting(initInfo, location);
    }

    UImGui::FVector2 getWindowSize() noexcept override
    {
        return initInfo->getWindowSize(initInfo);
    }

    UImGui::FVector2& getWindowSizeSetting() noexcept override
    {
        return *initInfo->getWindowSizeSetting(initInfo);
    }

    bool getWindowFullscreen() noexcept override
    {
        return initInfo->getWindowFullscreen(initInfo);
    }

    bool& getWindowFullscreenSetting() noexcept override
    {
        return *initInfo->getWindowFullscreenSetting(initInfo);
    }

    void setWindowFullscreen(const bool bFullscreen) noexcept override
    {
        initInfo->setWindowFullscreen(initInfo, bFullscreen);
    }

    float getAspectRatio() noexcept override
    {
        return initInfo->getAspectRatio(initInfo);
    }


    UImGui::FVector2 getCurrentWindowPosition() noexcept override
    {
        return initInfo->getCurrentWindowPosition(initInfo);
    }

    UImGui::FVector2 getLastWindowPosition() noexcept override
    {
        return initInfo->getLastWindowPosition(initInfo);
    }

    UImGui::FVector2 getWindowPositionChange() noexcept override
    {
        return initInfo->getWindowPositionChange(initInfo);
    }

    void setCurrentWindowPosition(const UImGui::FVector2 pos) noexcept override
    {
        initInfo->setCurrentWindowPosition(initInfo, pos);
    }

    void pushWindowPositionChangeCallback(const TFunction<void(UImGui::FVector2)>& f) noexcept override
    {
        initInfo->pushWindowPositionChangeCallback(initInfo, reinterpret_cast<const void*>(&f));
    }




    void saveSettings(const bool bSaveKeybinds) noexcept override
    {
        initInfo->saveSettings(initInfo, bSaveKeybinds);
    }

    void refreshSettings() noexcept override
    {
        initInfo->refreshSettings(initInfo);
    }


    void close() noexcept override
    {
        initInfo->close(initInfo);
    }

    void pushWindowCloseCallback(const TFunction<void()>& f) noexcept override
    {
        initInfo->pushWindowCloseCallback(initInfo, reinterpret_cast<const void*>(&f));
    }


    void Platform_setWindowAlwaysOnTop() noexcept override
    {
        initInfo->Platform_setWindowAlwaysOnTop(initInfo);
    }

    void Platform_setWindowAlwaysOnBottom() noexcept override
    {
        initInfo->Platform_setWindowAlwaysOnTop(initInfo);
    }


    void Platform_setWindowShowingOnPager(const bool bShowInPager) noexcept override
    {
        initInfo->Platform_setWindowShowingOnPager(initInfo, bShowInPager);
    }

    bool Platform_getWindowShowingOnPager() noexcept override
    {
        return initInfo->Platform_getWindowShowingOnPager(initInfo);
    }


    void Platform_setWindowShowingOnTaskbar(const bool bShowOnTaskbar) noexcept override
    {
        initInfo->Platform_setWindowShowingOnTaskbar(initInfo, bShowOnTaskbar);
    }

    bool Platform_getWindowShowingOnTaskbar() noexcept override
    {
        return initInfo->Platform_getWindowShowingOnTaskbar(initInfo);
    }


    void Platform_setWindowType(const UImGui::String type) noexcept override
    {
        initInfo->Platform_setWindowType(initInfo, type);
    }

    size_t Platform_getWindowID() noexcept override
    {
        return initInfo->Platform_getWindowID(initInfo);
    }

    void* Platform_getNativeWindowHandle() noexcept override
    {
        return initInfo->Platform_getNativeWindowHandle(initInfo);
    }

    UImGui::WindowPlatform Platform_getCurrentWindowPlatform() noexcept override
    {
        return initInfo->Platform_getCurrentWindowPlatform(initInfo);
    }

    void* Platform_getNativeDisplay() noexcept override
    {
        return initInfo->Platform_getNativeDisplay(initInfo);
    }

    void setWindowSizeInScreenCoords(const UImGui::FVector2 sz) noexcept override
    {
        initInfo->setWindowSizeInScreenCoords(initInfo, sz);
    }

    UImGui::FVector2 getWindowSizeInScreenCoords() noexcept override
    {
        return initInfo->getWindowSizeInScreenCoords(initInfo);
    }

    void pushWindowResizedInScreenCoordsCallback(const TFunction<void(int, int)>& f) noexcept override
    {
        initInfo->pushWindowResizedInScreenCoordsCallback(initInfo, reinterpret_cast<const void*>(&f));
    }


    void setWindowResizeable(const bool bResizeable) noexcept override
    {
        initInfo->setWindowResizeable(initInfo, bResizeable);
    }

    bool& getWindowResizeableSetting() noexcept override
    {
        return *initInfo->getWindowResizeableSetting(initInfo);
    }

    bool getWindowCurrentlyResizeable() noexcept override
    {
        return initInfo->getWindowCurrentlyResizeable(initInfo);
    }

    void pushWindowResizeCallback(const TFunction<void(int, int)>& f) noexcept override
    {
        initInfo->pushWindowResizeCallback(initInfo, reinterpret_cast<const void*>(&f));
    }


    void requestWindowAttention() noexcept override
    {
        return initInfo->requestWindowAttention(initInfo);
    }


    void hideWindow() noexcept override
    {
        return initInfo->hideWindow(initInfo);
    }

    void showWindow() noexcept override
    {
        return initInfo->showWindow(initInfo);
    }

    bool& getWindowHiddenSetting() noexcept override
    {
        return *initInfo->getWindowHiddenSetting(initInfo);
    }

    bool getWindowCurrentlyHidden() noexcept override
    {
        return initInfo->getWindowCurrentlyHidden(initInfo);
    }

    bool getWindowSurfaceTransparent() noexcept override
    {
        return initInfo->getWindowSurfaceTransparent(initInfo);
    }

    void setWindowSurfaceTransparent(const bool bTransparent) noexcept override
    {
        initInfo->setWindowSurfaceTransparent(initInfo, bTransparent);
    }

    bool& getWindowSurfaceTransparentSetting() noexcept override
    {
        return *initInfo->getWindowSurfaceTransparentSetting(initInfo);
    }


    void focusWindow() noexcept override
    {
        return initInfo->focusWindow(initInfo);
    }

    bool& getWindowFocusedSetting() noexcept override
    {
        return *initInfo->getWindowFocusSetting(initInfo);
    }

    bool getWindowCurrentlyFocused() noexcept override
    {
        return initInfo->getWindowCurrentlyFocused(initInfo);
    }

    void pushWindowFocusCallback(const TFunction<void(bool)>& f) noexcept override
    {
        initInfo->pushWindowFocusCallback(initInfo, reinterpret_cast<const void*>(&f));
    }


    void iconifyWindow() noexcept override
    {
        return initInfo->iconifyWindow(initInfo);
    }

    void restoreWindowState() noexcept override
    {
        initInfo->restoreWindowState(initInfo);
    }

    void pushWindowIconifyCallback(const TFunction<void(bool)>& f) noexcept override
    {
        initInfo->pushWindowIconifyCallback(initInfo, reinterpret_cast<const void*>(&f));
    }

    bool getWindowIconified() noexcept override
    {
        return initInfo->getWindowIconified(initInfo);
    }


    UImGui::FVector2 getWindowContentScale() noexcept override
    {
        return initInfo->getWindowContentScale(initInfo);
    }

    void pushWindowContentScaleCallback(const TFunction<void(UImGui::FVector2)>& f) noexcept override
    {
        initInfo->pushWindowContentScaleCallback(initInfo, reinterpret_cast<const void*>(&f));
    }


    void setSizeLimits(const UImGui::FVector2 min, const UImGui::FVector2 max) noexcept override
    {
        initInfo->setSizeLimits(initInfo, min, max);
    }

    void setSizeLimitByAspectRatio(const UImGui::FVector2 ratio) noexcept override
    {
        initInfo->setSizeLimitByAspectRatio(initInfo, ratio);
    }

    UImGui::FVector4& getSizeLimits() noexcept override
    {
        return *initInfo->getSizeLimits(initInfo);
    }

    UImGui::FVector2& getAspectRatioSizeLimits() noexcept override
    {
        return *initInfo->getAspectRatioSizeLimits(initInfo);
    }


    UImGui::FVector4 getWindowDecorationFrameDistances() noexcept override
    {
        return initInfo->getWindowDecorationFrameDistances(initInfo);
    }

    bool getCurrentWindowDecoratedState() noexcept override
    {
        return initInfo->getCurrentWindowDecoratedState(initInfo);
    }

    bool& getWindowDecoratedSetting() noexcept override
    {
        return *initInfo->getWindowDecoratedSetting(initInfo);
    }

    void setWindowDecorated(const bool bDecorated) noexcept override
    {
        initInfo->setWindowDecorated(initInfo, bDecorated);
    }

    void pushWindowRefreshCallback(const TFunction<void(void)>& f) noexcept override
    {
        initInfo->pushWindowRefreshCallback(initInfo, reinterpret_cast<const void*>(&f));
    }

    void maximiseWindow() noexcept override
    {
        initInfo->maximiseWindow(initInfo);
    }

    bool& getWindowMaximisedSetting() noexcept override
    {
        return *initInfo->getWindowMaximizedSetting(initInfo);
    }

    void pushWindowMaximiseCallback(const TFunction<void(bool)>& f) noexcept override
    {
        return initInfo->pushWindowMaximiseCallback(initInfo, reinterpret_cast<const void*>(&f));
    }

    bool getWindowCurrentlyMaximised() noexcept override
    {
        return initInfo->getWindowCurrentlyMaximised(initInfo);
    }

    UImGui::Monitor getWindowMonitor() noexcept override
    {
        auto tmp = initInfo->getWindowMonitor(initInfo);
        return *reinterpret_cast<UImGui::Monitor*>(&tmp);
    }

    UImGui::Monitor getPrimaryMonitor() noexcept override
    {
        auto tmp = initInfo->getPrimaryMonitor(initInfo);
        return *reinterpret_cast<UImGui::Monitor*>(&tmp);
    }

    const UImGui::TVector<UImGui::Monitor>& getMonitors() noexcept override
    {
        monitors.clear();
        size_t size = 0;
        auto* result = initInfo->getMonitors(initInfo, &size);
        
        if (result != nullptr && size > 0)
            for (size_t i = 0; i < size; i++)
                monitors.push_back(*reinterpret_cast<UImGui::Monitor*>(&result[i]));

        return monitors;
    }

    void pushWindowOSDragDropCallback(const TFunction<void(const UImGui::FString&)>& f) noexcept override
    {
        initInfo->pushWindowOSDragDropCallback(initInfo, reinterpret_cast<const void*>(&f));
    }

    void* getInternal() noexcept override
    {
        return initInfo->getInternal(initInfo);
    }

    GenericWindow* get() noexcept override
    {
        return static_cast<GenericWindow*>(initInfo->get(initInfo));
    }

    UImGui_CGenericWindowInitInfo* initInfo{};
    UImGui::TVector<UImGui::Monitor> monitors{};
};

void UImGui_CGenericWindow_create(UImGui_CGenericWindowInitInfo* initInfo)
{
    auto* result = new CGenericWindow{};
    result->initInfo = initInfo;
    initInfo->instance = result;
}

void UImGui_CGenericWindow_destroy(const UImGui_CGenericWindowInitInfo* instance)
{
    delete static_cast<CGenericWindow*>(instance->instance);
}
