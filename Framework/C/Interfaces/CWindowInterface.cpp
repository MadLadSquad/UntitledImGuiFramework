#include "CWindowInterface.h"
#include "Interfaces/WindowInterface.hpp"

void UImGui_Window_setTitle(UImGui_String name)
{
    UImGui::Window::setTitle(name);
}

void UImGui_Window_setIcon(UImGui_String name)
{
    UImGui::Window::setIcon(name);
}

float UImGui_Window_aspectRatio()
{
    return UImGui::Window::aspectRatio();
}

[[maybe_unused]] UImGui_FVector2 UImGui_Window_getCurrentWindowPosition()
{
    return UImGui::Window::getCurrentWindowPosition();
}

UImGui_FVector2 UImGui_Window_getLastWindowPosition()
{
    return UImGui::Window::getLastWindowPosition();
}

UImGui_FVector2 UImGui_Window_getWindowPositionChange()
{
    return UImGui::Window::getWindowPositionChange();
}

void UImGui_Window_setCurrentWindowPosition(UImGui_FVector2 pos)
{
    UImGui::Window::setCurrentWindowPosition(pos);
}

void UImGui_Window_pushWindowPositionChangeCallback(UImGui_Window_pushWindowPositionChangeCallbackFun f)
{
    UImGui::Window::pushWindowPositionChangeCallback(f);
}

UImGui_FVector2* UImGui_Window_windowSize()
{
    return &UImGui::Window::windowSize();
}

bool* UImGui_Window_fullscreen()
{
    return &UImGui::Window::fullscreen();
}

UImGui_String UImGui_Window_name()
{
    return UImGui::Window::name().c_str();
}

UImGui_String UImGui_Window_iconLocation()
{
    return UImGui::Window::iconLocation().c_str();
}

UImGui_String UImGui_Window_layoutLocation()
{
    return UImGui::Window::layoutLocation().c_str();
}

void UImGui_Window_saveSettings(bool bSaveKeybinds)
{
    UImGui::Window::saveSettings(bSaveKeybinds);
}

void UImGui_Window_refreshSettings()
{
    UImGui::Window::refreshSettings();
}

void UImGui_Window_close()
{
    UImGui::Window::close();
}

void UImGui_Window_pushWindowCloseCallback(UImGui_Window_pushWindowCloseCallbackFun f)
{
    UImGui::Window::pushWindowCloseCallback(f);
}

void UImGui_Window_Platform_setWindowAlwaysOnTop()
{
    UImGui::Window::Platform::setWindowAlwaysOnTop();
}

void UImGui_Window_Platform_setWindowAlwaysOnBottom()
{
    UImGui::Window::Platform::setWindowAlwaysOnBottom();
}

void UImGui_Window_Platform_disableWindowMovement()
{
    UImGui::Window::Platform::disableWindowMovement();
}

void UImGui_Window_Platform_setWindowShowingOnPager(bool bShowInPager)
{
    UImGui::Window::Platform::setWindowShowingOnPager(bShowInPager);
}

bool UImGui_Window_Platform_getWindowShowingOnPager()
{
    return UImGui::Window::Platform::getWindowShowingOnPager();
}

void UImGui_Window_Platform_setWindowShowingOnTaskbar(bool bShowOnTaskbar)
{
    UImGui::Window::Platform::setWindowShowingOnTaskbar(bShowOnTaskbar);
}

bool UImGui_Window_Platform_getWindowShowingOnTaskbar()
{
    return UImGui::Window::Platform::getWindowShowingOnTaskbar();
}

void UImGui_Window_Platform_setWindowType(UImGui_String type)
{
    UImGui::Window::Platform::setWindowType(type);
}

void UImGui_Window_setWindowSizeInScreenCoords(UImGui_FVector2 sz)
{
    UImGui::Window::setWindowSizeInScreenCoords(sz);
}

UImGui_FVector2* UImGui_Window_getWindowSizeInScreenCoords()
{
    return &UImGui::Window::getWindowSizeInScreenCoords();
}

void UImGui_Window_pushWindowResizedInScreenCoordsCallback(UImGui_Window_pushWindowResizedInScreenCoordsCallbackFun f)
{
    UImGui::Window::pushWindowResizedInScreenCoordsCallback(f);
}

void UImGui_Window_setWindowResizeable(bool bResizeable)
{
    UImGui::Window::setWindowResizeable(bResizeable);
}

bool* UImGui_Window_getWindowResizeableSetting()
{
    return &UImGui::Window::getWindowResizeableSetting();
}

bool UImGui_Window_getWindowCurrentlyResizeable()
{
    return UImGui::Window::getWindowCurrentlyResizeable();
}

void UImGui_Window_pushWindowResizeCallback(UImGui_Window_pushWindowResizedInScreenCoordsCallbackFun f)
{
    UImGui::Window::pushWindowResizeCallback(f);
}

UImGui_FVector4 UImGui_Window_getWindowDecorationFrameDistances()
{
    return UImGui::Window::getWindowDecorationFrameDistances();
}

void UImGui_Window_requestWindowAttention()
{
    UImGui::Window::requestWindowAttention();
}

void UImGui_Window_hideWindow()
{
    UImGui::Window::hideWindow();
}
void UImGui_Window_showWindow()
{
    UImGui::Window::showWindow();
}
bool* UImGui_Window_getWindowHiddenSetting()
{
    return &UImGui::Window::getWindowHiddenSetting();
}
bool UImGui_Window_getWindowCurrentlyHidden()
{
    return UImGui::Window::getWindowCurrentlyHidden();
}

bool* UImGui_Window_windowSurfaceTransparent()
{
    return &UImGui::Window::windowSurfaceTransparent();
}

void UImGui_Window_focusWindow()
{
    UImGui::Window::focusWindow();
}

bool* UImGui_Window_getWindowFocusedSetting()
{
    return &UImGui::Window::getWindowFocusedSetting();
}

bool UImGui_Window_getWindowCurrentlyFocused()
{
    return UImGui::Window::getWindowCurrentlyFocused();
}

void UImGui_Window_pushWindowFocusCallback(UImGui_Window_pushWindowFocusCallbackFun f)
{
    UImGui::Window::pushWindowFocusCallback(f);
}

void UImGui_Window_iconifyWindow()
{
    UImGui::Window::iconifyWindow();
}

void UImGui_Window_restoreWindowState()
{
    UImGui::Window::restoreWindowState();
}

void UImGui_Window_pushWindowIconifyCallback(UImGui_Window_pushWindowIconifyCallbackFun f)
{
    UImGui::Window::pushWindowIconifyCallback(f);
}

bool UImGui_Window_getWindowIconified()
{
    return UImGui::Window::getWindowIconified();
}

UImGui_FVector2 UImGui_Window_getWindowContentScale()
{
    return UImGui::Window::getWindowContentScale();
}

void UImGui_Window_pushWindowContentScaleCallback(UImGui_Window_pushWindowContentScaleCallbackFun f)
{
    UImGui::Window::pushWindowContentScaleCallback(f);
}

void UImGui_Window_setSizeLimits(UImGui_FVector2 min, UImGui_FVector2 max)
{
    UImGui::Window::setSizeLimits(min, max);
}

void UImGui_Window_setSizeLimitByAspectRatio(UImGui_FVector2 ratio)
{
    UImGui::Window::setSizeLimitByAspectRatio(ratio);
}

UImGui_FVector4* UImGui_Window_getSizeLimits()
{
    return &UImGui::Window::getSizeLimits();
}
UImGui_FVector2* UImGui_Window_getAspectRatioSizeLimits()
{
    return &UImGui::Window::getAspectRatioSizeLimits();
}

bool UImGui_Window_getCurrentWindowDecoratedState()
{
    return UImGui::Window::getCurrentWindowDecoratedState();
}

bool* UImGui_Window_getWindowDecoratedSetting()
{
    return &UImGui::Window::getWindowDecoratedSetting();
}

void UImGui_Window_setWindowDecorated(bool bDecorated)
{
    UImGui::Window::setWindowDecorated(bDecorated);
}

void UImGui_Window_pushWindowRefreshCallback(UImGui_Window_pushWindowRefreshCallbackFun f)
{
    UImGui::Window::pushWindowRefreshCallback(f);
}

void UImGui_Window_maximiseWindow()
{
    UImGui::Window::maximiseWindow();
}

bool* UImGui_Window_getWindowMaximisedSetting()
{
    return &UImGui::Window::getWindowMaximisedSetting();
}

void UImGui_Window_pushWindowMaximiseCallback(UImGui_Window_pushWindowMaximiseCallbackFun f)
{
    UImGui::Window::pushWindowMaximiseCallback(f);
}

bool UImGui_Window_getWindowCurrentlyMaximised()
{
    return UImGui::Window::getWindowCurrentlyMaximised();
}

//UImGui_Monitor UImGui_Window_getWindowMonitor()
//{
//    return UImGui::Window::getWindowMonitor();
//}
//
//
//void UImGui_Window_setWindowMonitor(const UImGui_Monitor* monitor)
//{
//    UImGui::Window::setWindowMonitor(*monitor);
//}
//
//
//UImGui_Monitor* UImGui_Window_getMonitors()
//{
//    return UImGui::Window::getMonitors().data();
//}
//
//
//void UImGui_Window_pushGlobalMonitorCallback(const std::function<void(Monitor&, MonitorState)>* f)
//{
//
//}

char** UImGui_Window_getOSDragDropStrings()
{

}

void UImGui_Window_pushWindowOSDragDropCallback(const std::function<void(std::vector<UImGui_String>&)>* f)
{

}

void UImGui_Window_pushWindowErrorCallback(UImGuiWindow_pushWindowErrorCallbackFun f)
{
    UImGui::Window::pushWindowErrorCallback(f);
}
