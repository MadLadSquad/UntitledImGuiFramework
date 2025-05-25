#include "WindowInterface.hpp"
#include <Global.hpp>
#include <GLFW/glfw3.h>

void UImGui::Window::setTitle(const String name) noexcept
{
    get().setTitle(name);
}

float UImGui::Window::aspectRatio() noexcept
{
    return get().windowSize.x / get().windowSize.y;
}

UImGui::FVector2& UImGui::Window::windowSize() noexcept
{
    return get().windowSize;
}

bool& UImGui::Window::fullscreen() noexcept
{
    return get().windowData.fullscreen;
}

UImGui::FString& UImGui::Window::name() noexcept
{
    return get().windowData.name;
}

UImGui::FString& UImGui::Window::iconLocation() noexcept
{
    return get().windowData.iconLocation;
}

void UImGui::Window::saveSettings(const bool bSaveKeybinds) noexcept
{
    get().saveConfig(bSaveKeybinds);
}

void UImGui::Window::close() noexcept
{
    get().close();
}

UImGui::FVector2 UImGui::Window::getCurrentWindowPosition() noexcept
{
    return get().windowCurrentPos;
}

UImGui::FVector2 UImGui::Window::getLastWindowPosition() noexcept
{
    return get().windowLastPos;
}

UImGui::FVector2 UImGui::Window::getWindowPositionChange() noexcept
{
    return
    {
        get().windowCurrentPos.x - get().windowLastPos.x,
        get().windowCurrentPos.y - get().windowLastPos.y
    };
}

UImGui::WindowInternal& UImGui::Window::get() noexcept
{
    return Global::get().window;
}

void UImGui::Window::refreshSettings() noexcept
{
    const auto& a = get();
    setTitle(a.windowData.name.c_str());
    setIcon(a.windowData.iconLocation.c_str());
    setWindowSizeInScreenCoords(a.windowSize);
}

void UImGui::Window::setIcon(const String name) noexcept
{
    get().setIcon(name);
}

void UImGui::Window::setCurrentWindowPosition(const FVector2 pos) noexcept
{
    glfwSetWindowPos(get().windowMain, CAST(int, pos.x), CAST(int, pos.y));
}

UImGui::FVector2& UImGui::Window::getWindowSizeInScreenCoords() noexcept
{
    return get().windowSizeInScreenCoords;
}

void UImGui::Window::setWindowSizeInScreenCoords(const FVector2 sz) noexcept
{
    glfwSetWindowSize(get().windowMain, CAST(int, sz.x), CAST(int, sz.y));
}

UImGui::FVector4 UImGui::Window::getWindowDecorationFrameDistances() noexcept
{
    int x = 0, y = 0, z = 0, w = 0;
    glfwGetWindowFrameSize(get().windowMain, &x, &y, &z, &w);
    const FVector4 val = { CAST(float, x), CAST(float, y), CAST(float, z), CAST(float, w) };
    return val;
}

void UImGui::Window::pushWindowResizedInScreenCoordsCallback(const TFunction<void(int, int)>& f) noexcept
{
    get().windowResizeInScreenCoordCallbackList.push_back(f);
}

void UImGui::Window::pushWindowResizeCallback(const TFunction<void(int, int)>& f) noexcept
{
    get().windowResizeCallbackList.push_back(f);
}

void UImGui::Window::pushWindowCloseCallback(const TFunction<void(void)>& f) noexcept
{
    get().windowCloseCallbackList.push_back(f);
}

void UImGui::Window::requestWindowAttention() noexcept
{
    glfwRequestWindowAttention(get().windowMain);
}

void UImGui::Window::hideWindow() noexcept
{
    glfwHideWindow(get().windowMain);
}

void UImGui::Window::showWindow() noexcept
{
    glfwShowWindow(get().windowMain);
}

bool& UImGui::Window::getWindowHiddenSetting() noexcept
{
    return get().windowData.bHidden;
}

bool& UImGui::Window::windowSurfaceTransparent() noexcept
{
    return get().windowData.bSurfaceTransparent;
}

void UImGui::Window::focusWindow() noexcept
{
    glfwFocusWindow(get().windowMain);
}

bool& UImGui::Window::getWindowFocusedSetting() noexcept
{
    return get().windowData.bFocused;
}

void UImGui::Window::pushWindowFocusCallback(const TFunction<void(bool)>& f) noexcept
{
    get().windowFocusCallbackList.push_back(f);
}

bool UImGui::Window::getWindowCurrentlyHidden() noexcept
{
    return !glfwGetWindowAttrib(get().windowMain, GLFW_VISIBLE);
}

bool UImGui::Window::getWindowCurrentlyFocused() noexcept
{
    return glfwGetWindowAttrib(get().windowMain, GLFW_FOCUSED);
}

void UImGui::Window::iconifyWindow() noexcept
{
    glfwIconifyWindow(get().windowMain);
}

void UImGui::Window::restoreWindowState() noexcept
{
    glfwRestoreWindow(get().windowMain);
}

void UImGui::Window::pushWindowIconifyCallback(const TFunction<void(bool)>& f) noexcept
{
    get().windowIconifiedCallbackList.push_back(f);
}

bool UImGui::Window::getWindowIconified() noexcept
{
    return glfwGetWindowAttrib(get().windowMain, GLFW_ICONIFIED);
}

void UImGui::Window::pushWindowPositionChangeCallback(const TFunction<void(FVector2)>& f) noexcept
{
    get().windowPositionChangeCallbackList.push_back(f);
}

UImGui::FVector2 UImGui::Window::getWindowContentScale() noexcept
{
    FVector2 ret;
    glfwGetWindowContentScale(get().windowMain, &ret.x, &ret.y);
    return ret;
}

void UImGui::Window::pushWindowContentScaleCallback(const TFunction<void(FVector2)>& f) noexcept
{
    get().windowContentScaleChangeCallbackList.push_back(f);
}

void UImGui::Window::setSizeLimits(const FVector2 min, const FVector2 max) noexcept
{
    glfwSetWindowSizeLimits(get().windowMain, CAST(int, min.x), CAST(int, min.y), CAST(int, max.x), CAST(int, max.y));
}

void UImGui::Window::setSizeLimitByAspectRatio(const FVector2 ratio) noexcept
{
    glfwSetWindowAspectRatio(get().windowMain, CAST(int, ratio.x), CAST(int, ratio.y));
}

UImGui::FVector4& UImGui::Window::getSizeLimits() noexcept
{
    return get().windowData.sizeLimits;
}

UImGui::FVector2& UImGui::Window::getAspectRatioSizeLimits() noexcept
{
    return get().windowData.aspectRatioSizeLimit;
}

void UImGui::Window::setWindowResizeable(const bool bResizeable) noexcept
{
    glfwSetWindowAttrib(get().windowMain, GLFW_RESIZABLE, bResizeable);
}

bool& UImGui::Window::getWindowResizeableSetting() noexcept
{
    return get().windowData.bResizeable;
}

bool UImGui::Window::getWindowCurrentlyResizeable() noexcept
{
    return glfwGetWindowAttrib(get().windowMain, GLFW_RESIZABLE);
}

bool UImGui::Window::getCurrentWindowDecoratedState() noexcept
{
    return glfwGetWindowAttrib(get().windowMain, GLFW_DECORATED);
}

bool& UImGui::Window::getWindowDecoratedSetting() noexcept
{
    return get().windowData.bDecorated;
}

void UImGui::Window::setWindowDecorated(const bool bDecorated) noexcept
{
    glfwSetWindowAttrib(get().windowMain, GLFW_DECORATED, bDecorated);
}

void UImGui::Window::pushWindowRefreshCallback(const TFunction<void(void)>& f) noexcept
{
    get().windowRefreshCallbackList.push_back(f);
}

void UImGui::Window::maximiseWindow() noexcept
{
    glfwMaximizeWindow(get().windowMain);
}

bool UImGui::Window::getWindowCurrentlyMaximised() noexcept
{
    return glfwGetWindowAttrib(get().windowMain, GLFW_MAXIMIZED);
}

void UImGui::Window::pushWindowMaximiseCallback(const TFunction<void(bool)>& f) noexcept
{
    get().windowMaximisedCallbackList.push_back(f);
}

bool& UImGui::Window::getWindowMaximisedSetting() noexcept
{
    return get().windowData.bMaximised;
}

#ifndef __EMSCRIPTEN__

UImGui::TVector<UImGui::Monitor>& UImGui::Window::getMonitors() noexcept
{
    return get().monitors;
}

UImGui::Monitor UImGui::Window::getWindowMonitor() noexcept
{
    const auto* monitor = glfwGetWindowMonitor(get().windowMain);
    if (monitor == nullptr)
        return {};
    return Monitor(glfwGetWindowMonitor(get().windowMain));
}

void UImGui::Window::setWindowMonitor(const Monitor& monitor) noexcept
{
    const GLFWvidmode* mode = glfwGetVideoMode(monitor.monitor);
    const GLFWvidmode* currentMode = glfwGetVideoMode(getWindowMonitor().monitor);

    glfwSetWindowMonitor(get().windowMain, monitor.monitor, 0, 0, currentMode->width, currentMode->height, mode->refreshRate);
}
#endif

UImGui::TVector<UImGui::FString>& UImGui::Window::getOSDragDropStrings() noexcept
{
    return get().dragDropPaths;
}

void UImGui::Window::pushWindowOSDragDropCallback(const TFunction<void(TVector<FString>&)>& f) noexcept
{
    get().dragDropPathCallbackList.push_back(f);
}

#ifndef __EMSCRIPTEN__

void UImGui::Window::pushGlobalMonitorCallback(const TFunction<void(Monitor&, MonitorState)>& f) noexcept
{
    get().windowMonitorCallbackList.push_back(f);
}

#endif

void UImGui::Window::pushWindowErrorCallback(const TFunction<void(int, String)>& f) noexcept
{
    get().windowErrorCallbackList.push_back(f);
}

void UImGui::Window::Platform::setWindowAlwaysOnTop() noexcept
{
    get().setWindowAlwaysOnTop();
}

void UImGui::Window::Platform::setWindowAlwaysOnBottom() noexcept
{
    get().setWindowAlwaysBelow();
}

void UImGui::Window::Platform::setWindowShowingOnPager(const bool bShowInPager) noexcept
{
    get().setShowWindowInPager(bShowInPager);
}

bool UImGui::Window::Platform::getWindowShowingOnPager() noexcept
{
    return get().bShowOnPager;
}

void UImGui::Window::Platform::setWindowShowingOnTaskbar(const bool bShowOnTaskbar) noexcept
{
    get().setShowWindowOnTaskbar(bShowOnTaskbar);
}

bool UImGui::Window::Platform::getWindowShowingOnTaskbar() noexcept
{
    return get().bShowOnTaskbar;
}

void UImGui::Window::Platform::setWindowType(const String type) noexcept
{
    get().setWindowType(type);
}

size_t UImGui::Window::Platform::getWindowID() noexcept
{
    return get().getWindowID();
}

GLFWwindow* UImGui::Window::getInternal() noexcept
{
    return get().data();
}