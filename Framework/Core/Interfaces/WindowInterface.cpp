#include "WindowInterface.hpp"
#include <Global.hpp>
#include <GLFW/glfw3.h>

void UImGui::Window::setTitle(UImGui::String name) noexcept
{
    Window::get().setTitle(name);
}

void UImGui::Window::setCursorVisibility(bool bVisible) noexcept
{
    Window::get().setCursorVisibility(bVisible);
}

float UImGui::Window::aspectRatio() noexcept
{
    return Window::get().windowSize.x / Window::get().windowSize.y;
}

UImGui::FVector2& UImGui::Window::windowSize() noexcept
{
    return Window::get().windowSize;
}

bool& UImGui::Window::fullscreen() noexcept
{
    return Window::get().windowData.fullscreen;
}

UImGui::FString& UImGui::Window::name() noexcept
{
    return Window::get().windowData.name;
}

UImGui::FString& UImGui::Window::iconLocation() noexcept
{
    return Window::get().windowData.iconLocation;
}

void UImGui::Window::saveSettings(bool bSaveKeybinds) noexcept
{
    Window::get().saveConfig(bSaveKeybinds);
}

void UImGui::Window::close() noexcept
{
    Window::get().close();
}

UImGui::FVector2 UImGui::Window::getCurrentWindowPosition() noexcept
{
    return Window::get().windowCurrentPos;
}

UImGui::FVector2 UImGui::Window::getLastWindowPosition() noexcept
{
    return Window::get().windowLastPos;
}

UImGui::FVector2 UImGui::Window::getWindowPositionChange() noexcept
{
    return
    {
        Window::get().windowCurrentPos.x - Window::get().windowLastPos.x,
        Window::get().windowCurrentPos.y - Window::get().windowLastPos.y
    };
}

UImGui::WindowInternal& UImGui::Window::get() noexcept
{
    return internalGlobal.window;
}

void UImGui::Window::refreshSettings() noexcept
{
    auto& a = Window::get();
    setTitle(a.windowData.name.c_str());
    setIcon(a.windowData.iconLocation.c_str());
    setWindowSizeInScreenCoords(a.windowSize);
}

void UImGui::Window::setIcon(UImGui::String name) noexcept
{
    Window::get().setIcon(name);
}

UImGui::FString& UImGui::Window::layoutLocation() noexcept
{
    return Window::get().windowData.layoutLocation;
}

void UImGui::Window::setCurrentWindowPosition(UImGui::FVector2 pos) noexcept
{
    glfwSetWindowPos(Window::get().windowMain, (int)pos.x, (int)pos.y);
}

UImGui::FVector2& UImGui::Window::getWindowSizeInScreenCoords() noexcept
{
    return Window::get().windowSizeInScreenCoords;
}

void UImGui::Window::setWindowSizeInScreenCoords(UImGui::FVector2 sz) noexcept
{
    glfwSetWindowSize(Window::get().windowMain, (int)sz.x, (int)sz.y);
}

UImGui::FVector4 UImGui::Window::getWindowDecorationFrameDistances() noexcept
{
    int x = 0, y = 0, z = 0, w = 0;
    glfwGetWindowFrameSize(Window::get().windowMain, &x, &y, &z, &w);
    FVector4 val = { (float)x, (float)y, (float)z, (float)w };
    return val;
}

void UImGui::Window::pushWindowResizedInScreenCoordsCallback(const std::function<void(int, int)>& f) noexcept
{
    Window::get().windowResizeInScreenCoordCallbackList.push_back(f);
}

void UImGui::Window::pushWindowResizeCallback(const std::function<void(int, int)>& f) noexcept
{
    Window::get().windowResizeCallbackList.push_back(f);
}

void UImGui::Window::pushWindowCloseCallback(const std::function<void(void)>& f) noexcept
{
    Window::get().windowCloseCallbackList.push_back(f);
}

void UImGui::Window::requestWindowAttention() noexcept
{
    glfwRequestWindowAttention(Window::get().windowMain);
}

void UImGui::Window::hideWindow() noexcept
{
    glfwHideWindow(Window::get().windowMain);
}

void UImGui::Window::showWindow() noexcept
{
    glfwShowWindow(Window::get().windowMain);
}

bool& UImGui::Window::getWindowHiddenSetting() noexcept
{
    return Window::get().windowData.bHidden;
}

bool& UImGui::Window::windowSurfaceTransparent() noexcept
{
    return Window::get().windowData.bSurfaceTransparent;
}

void UImGui::Window::focusWindow() noexcept
{
    glfwFocusWindow(Window::get().windowMain);
}

bool& UImGui::Window::getWindowFocusedSetting() noexcept
{
    return Window::get().windowData.bFocused;
}

void UImGui::Window::pushWindowFocusCallback(const std::function<void(bool)>& f) noexcept
{
    Window::get().windowFocusCallbackList.push_back(f);
}

bool UImGui::Window::getWindowCurrentlyHidden() noexcept
{
    return !glfwGetWindowAttrib(Window::get().windowMain, GLFW_VISIBLE);
}

bool UImGui::Window::getWindowCurrentlyFocused() noexcept
{
    return glfwGetWindowAttrib(Window::get().windowMain, GLFW_FOCUSED);
}

void UImGui::Window::iconifyWindow() noexcept
{
    glfwIconifyWindow(Window::get().windowMain);
}

void UImGui::Window::restoreWindowState() noexcept
{
    glfwRestoreWindow(Window::get().windowMain);
}

void UImGui::Window::pushWindowIconifyCallback(const std::function<void(bool)>& f) noexcept
{
    Window::get().windowIconifiedCallbackList.push_back(f);
}

bool UImGui::Window::getWindowIconified() noexcept
{
    return glfwGetWindowAttrib(Window::get().windowMain, GLFW_ICONIFIED);
}

void UImGui::Window::pushWindowPositionChangeCallback(const std::function<void(FVector2)>& f) noexcept
{
    Window::get().windowPositionChangeCallbackList.push_back(f);
}

UImGui::FVector2 UImGui::Window::getWindowContentScale() noexcept
{
    FVector2 ret;
    glfwGetWindowContentScale(Window::get().windowMain, &ret.x, &ret.y);
    return ret;
}

void UImGui::Window::pushWindowContentScaleCallback(const std::function<void(FVector2)>& f) noexcept
{
    Window::get().windowContentScaleChangeCallbackList.push_back(f);
}

void UImGui::Window::setSizeLimits(UImGui::FVector2 min, UImGui::FVector2 max) noexcept
{
    glfwSetWindowSizeLimits(Window::get().windowMain, (int)min.x, (int)min.y, (int)max.x, (int)max.y);
}

void UImGui::Window::setSizeLimitByAspectRatio(UImGui::FVector2 ratio) noexcept
{
    glfwSetWindowAspectRatio(Window::get().windowMain, (int)ratio.x, (int)ratio.y);
}

UImGui::FVector4& UImGui::Window::getSizeLimits() noexcept
{
    return Window::get().windowData.sizeLimits;
}

UImGui::FVector2& UImGui::Window::getAspectRatioSizeLimits() noexcept
{
    return Window::get().windowData.aspectRatioSizeLimit;
}

void UImGui::Window::setWindowResizeable(bool bResizeable) noexcept
{
    glfwSetWindowAttrib(Window::get().windowMain, GLFW_RESIZABLE, bResizeable);
}

bool& UImGui::Window::getWindowResizeableSetting() noexcept
{
    return Window::get().windowData.bResizeable;
}

bool UImGui::Window::getWindowCurrentlyResizeable() noexcept
{
    return glfwGetWindowAttrib(Window::get().windowMain, GLFW_RESIZABLE);
}

bool UImGui::Window::getCurrentWindowDecoratedState() noexcept
{
    return glfwGetWindowAttrib(Window::get().windowMain, GLFW_DECORATED);
}

bool& UImGui::Window::getWindowDecoratedSetting() noexcept
{
    return Window::get().windowData.bDecorated;
}

void UImGui::Window::setWindowDecorated(bool bDecorated) noexcept
{
    glfwSetWindowAttrib(Window::get().windowMain, GLFW_DECORATED, bDecorated);
}

void UImGui::Window::pushWindowRefreshCallback(const std::function<void(void)>& f) noexcept
{
    Window::get().windowRefreshCallbackList.push_back(f);
}

void UImGui::Window::maximiseWindow() noexcept
{
    glfwMaximizeWindow(Window::get().windowMain);
}

bool UImGui::Window::getWindowCurrentlyMaximised() noexcept
{
    return glfwGetWindowAttrib(Window::get().windowMain, GLFW_MAXIMIZED);
}

void UImGui::Window::pushWindowMaximiseCallback(const std::function<void(bool)>& f) noexcept
{
    Window::get().windowMaximisedCallbackList.push_back(f);
}

bool& UImGui::Window::getWindowMaximisedSetting() noexcept
{
    return Window::get().windowData.bMaximised;
}

std::vector<UImGui::Monitor>& UImGui::Window::getMonitors() noexcept
{
    return Window::get().monitors;
}

UImGui::Monitor UImGui::Window::getWindowMonitor() noexcept
{
    return Monitor(glfwGetWindowMonitor(Window::get().windowMain));
}

void UImGui::Window::setWindowMonitor(UImGui::Monitor monitor) noexcept
{
    const GLFWvidmode* mode = glfwGetVideoMode(monitor.monitor);
    const GLFWvidmode* currentMode = glfwGetVideoMode(Window::getWindowMonitor().monitor);

    glfwSetWindowMonitor(Window::get().windowMain, monitor.monitor, 0, 0, currentMode->width, currentMode->height, mode->refreshRate);
}

std::vector<UImGui::FString>& UImGui::Window::getOSDragDropStrings() noexcept
{
    return Window::get().dragDropPaths;
}

void UImGui::Window::pushWindowOSDragDropCallback(const std::function<void(std::vector<FString>&)>& f) noexcept
{
    Window::get().dragDropPathCallbackList.push_back(f);
}

void UImGui::Window::pushGlobalMonitorCallback(const std::function<void(Monitor&, MonitorState)>& f) noexcept
{
    Window::get().windowMonitorCallbackList.push_back(f);
}

void UImGui::Window::Platform::setWindowAlwaysOnTop() noexcept
{
    Window::get().setWindowAlwaysOnTop();
}
