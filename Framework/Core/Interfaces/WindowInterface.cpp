#include "WindowInterface.hpp"
#include <Global.hpp>

#define window(x, ...) get()->x

void UImGui::Window::setTitle(const String name) noexcept
{
    return window(setTitle(name));
}

UImGui::String UImGui::Window::getTitle() noexcept
{
    return window(getTitle());
}

void UImGui::Window::setTitleSetting(const String name) noexcept
{
    window(setTitleSetting(name));
}

UImGui::String UImGui::Window::getTitleSetting() noexcept
{
    return window(getTitleSetting());
}

float UImGui::Window::getAspectRatio() noexcept
{
    return window(getAspectRatio());
}

UImGui::FVector2 UImGui::Window::getWindowSize() noexcept
{
    return window(getWindowSize());
}

UImGui::FVector2& UImGui::Window::getWindowSizeSetting() noexcept
{
    return window(getWindowSizeSetting());
}

bool UImGui::Window::getWindowFullscreen() noexcept
{
    return window(getWindowFullscreen());
}

bool& UImGui::Window::getWindowFullscreenSetting() noexcept
{
    return window(getWindowFullscreenSetting());
}

void UImGui::Window::setWindowFullscreen(const bool bFullscreen) noexcept
{
    return window(setWindowFullscreen(bFullscreen));
}

void UImGui::Window::saveSettings(const bool bSaveKeybinds) noexcept
{
    return window(saveSettings(bSaveKeybinds));
}

void UImGui::Window::close() noexcept
{
    return window(close());
}

UImGui::FVector2 UImGui::Window::getCurrentWindowPosition() noexcept
{
    return window(getCurrentWindowPosition());
}

UImGui::FVector2 UImGui::Window::getLastWindowPosition() noexcept
{
    return window(getLastWindowPosition());
}

UImGui::FVector2 UImGui::Window::getWindowPositionChange() noexcept
{
    return window(getWindowPositionChange());
}

void UImGui::Window::refreshSettings() noexcept
{
    return window(refreshSettings());
}

void UImGui::Window::setIcon(const String name) noexcept
{
    return window(setIcon(name));
}

UImGui::String UImGui::Window::getIconLocation() noexcept
{
    return window(getIconLocation());
}

UImGui::String UImGui::Window::getIconLocationSetting() noexcept
{
    return window(getIconLocationSetting());
}

void UImGui::Window::setIconLocationSetting(const String location) noexcept
{
    window(setIconLocationSetting(location));
}

void UImGui::Window::setCurrentWindowPosition(const FVector2 pos) noexcept
{
    return window(setCurrentWindowPosition(pos));
}

UImGui::FVector2 UImGui::Window::getWindowSizeInScreenCoords() noexcept
{
    return window(getWindowSizeInScreenCoords());
}

void UImGui::Window::setWindowSizeInScreenCoords(const FVector2 sz) noexcept
{
    return window(setWindowSizeInScreenCoords(sz));
}

UImGui::FVector4 UImGui::Window::getWindowDecorationFrameDistances() noexcept
{
    return window(getWindowDecorationFrameDistances());
}

void UImGui::Window::pushWindowResizedInScreenCoordsCallback(const TFunction<void(int, int)>& f) noexcept
{
    return window(pushWindowResizedInScreenCoordsCallback(f));
}

void UImGui::Window::pushWindowResizeCallback(const TFunction<void(int, int)>& f) noexcept
{
    return window(pushWindowResizeCallback(f));
}

void UImGui::Window::pushWindowCloseCallback(const TFunction<void(void)>& f) noexcept
{
    return window(pushWindowCloseCallback(f));
}

void UImGui::Window::requestWindowAttention() noexcept
{
    return window(requestWindowAttention());
}

void UImGui::Window::hideWindow() noexcept
{
    return window(hideWindow());
}

void UImGui::Window::showWindow() noexcept
{
    return window(showWindow());
}

bool& UImGui::Window::getWindowHiddenSetting() noexcept
{
    return window(getWindowHiddenSetting());
}

bool& UImGui::Window::windowSurfaceTransparentSetting() noexcept
{
    return window(windowSurfaceTransparentSetting());
}

void UImGui::Window::focusWindow() noexcept
{
    return window(focusWindow());
}

bool& UImGui::Window::getWindowFocusedSetting() noexcept
{
    return window(getWindowFocusedSetting());
}

void UImGui::Window::pushWindowFocusCallback(const TFunction<void(bool)>& f) noexcept
{
    return window(pushWindowFocusCallback(f));
}

bool UImGui::Window::getWindowCurrentlyHidden() noexcept
{
    return window(getWindowCurrentlyHidden());
}

bool UImGui::Window::getWindowCurrentlyFocused() noexcept
{
    return window(getWindowCurrentlyFocused());
}

void UImGui::Window::iconifyWindow() noexcept
{
    return window(iconifyWindow());
}

void UImGui::Window::restoreWindowState() noexcept
{
    return window(restoreWindowState());
}

void UImGui::Window::pushWindowIconifyCallback(const TFunction<void(bool)>& f) noexcept
{
    return window(pushWindowIconifyCallback(f));
}

bool UImGui::Window::getWindowIconified() noexcept
{
    return window(getWindowIconified());
}

void UImGui::Window::pushWindowPositionChangeCallback(const TFunction<void(FVector2)>& f) noexcept
{
    return window(pushWindowPositionChangeCallback(f));
}

UImGui::FVector2 UImGui::Window::getWindowContentScale() noexcept
{
    return window(getWindowContentScale());
}

void UImGui::Window::pushWindowContentScaleCallback(const TFunction<void(FVector2)>& f) noexcept
{
    return window(pushWindowContentScaleCallback(f));
}

void UImGui::Window::setSizeLimits(const FVector2 min, const FVector2 max) noexcept
{
    return window(setSizeLimits(min, max));
}

void UImGui::Window::setSizeLimitByAspectRatio(const FVector2 ratio) noexcept
{
    return window(setSizeLimitByAspectRatio(ratio));
}

UImGui::FVector4& UImGui::Window::getSizeLimits() noexcept
{
    return window(getSizeLimits());
}

UImGui::FVector2& UImGui::Window::getAspectRatioSizeLimits() noexcept
{
    return window(getAspectRatioSizeLimits());
}

void UImGui::Window::setWindowResizeable(const bool bResizeable) noexcept
{
    return window(setWindowResizeable(bResizeable));
}

bool& UImGui::Window::getWindowResizeableSetting() noexcept
{
    return window(getWindowResizeableSetting());
}

bool UImGui::Window::getWindowCurrentlyResizeable() noexcept
{
    return window(getWindowCurrentlyResizeable());
}

bool UImGui::Window::getCurrentWindowDecoratedState() noexcept
{
    return window(getCurrentWindowDecoratedState());
}

bool& UImGui::Window::getWindowDecoratedSetting() noexcept
{
    return window(getWindowDecoratedSetting());
}

void UImGui::Window::setWindowDecorated(const bool bDecorated) noexcept
{
    return window(setWindowDecorated(bDecorated));
}

void UImGui::Window::pushWindowRefreshCallback(const TFunction<void(void)>& f) noexcept
{
    return window(pushWindowRefreshCallback(f));
}

void UImGui::Window::maximiseWindow() noexcept
{
    return window(maximiseWindow());
}

bool UImGui::Window::getWindowCurrentlyMaximised() noexcept
{
    return window(getWindowCurrentlyMaximised());
}

void UImGui::Window::pushWindowMaximiseCallback(const TFunction<void(bool)>& f) noexcept
{
    return window(pushWindowMaximiseCallback(f));
}

bool& UImGui::Window::getWindowMaximisedSetting() noexcept
{
    return window(getWindowMaximisedSetting());
}

const UImGui::TVector<UImGui::Monitor>& UImGui::Window::getMonitors() noexcept
{
    return window(getMonitors());
}

UImGui::Monitor UImGui::Window::getWindowMonitor() noexcept
{
    return window(getWindowMonitor());
}

UImGui::Monitor UImGui::Window::getPrimaryMonitor() noexcept
{
    return window(getPrimaryMonitor());
}

void UImGui::Window::pushWindowOSDragDropCallback(const std::function<void(const FString&)>& f) noexcept
{
    return window(pushWindowOSDragDropCallback(f));
}

void UImGui::Window::Platform::setWindowAlwaysOnTop() noexcept
{
    return window(Platform_setWindowAlwaysOnTop());
}

void UImGui::Window::Platform::setWindowAlwaysOnBottom() noexcept
{
    return window(Platform_setWindowAlwaysOnBottom());
}

void UImGui::Window::Platform::setWindowShowingOnPager(const bool bShowInPager) noexcept
{
    return window(Platform_setWindowShowingOnPager(bShowInPager));
}

bool UImGui::Window::Platform::getWindowShowingOnPager() noexcept
{
    return window(Platform_getWindowShowingOnPager());
}

void UImGui::Window::Platform::setWindowShowingOnTaskbar(const bool bShowOnTaskbar) noexcept
{
    return window(Platform_setWindowShowingOnTaskbar(bShowOnTaskbar));
}

bool UImGui::Window::Platform::getWindowShowingOnTaskbar() noexcept
{
    return window(Platform_getWindowShowingOnTaskbar());
}

void UImGui::Window::Platform::setWindowType(const String type) noexcept
{
    return window(Platform_setWindowType(type));
}

size_t UImGui::Window::Platform::getWindowID() noexcept
{
    return window(Platform_getWindowID());
}

void* UImGui::Window::getInternal() noexcept
{
    return window(getInternal());
}

UImGui::GenericWindow* UImGui::Window::get() noexcept
{
    return Global::get().window.window;
}