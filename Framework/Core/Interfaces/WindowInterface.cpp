#include "WindowInterface.hpp"
#include <Global.hpp>

// Delegates a call to the active GenericWindow backend. Exists purely to keep the ~80 one-line forwarders below
// readable; #undef'd at the bottom of the file so it cannot leak into anything else.
#define window(x) get()->x

void UImGui::Window::setTitle(const String name) noexcept
{
    window(setTitle(name));
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
    window(setWindowFullscreen(bFullscreen));
}

void UImGui::Window::saveSettings(const bool bSaveKeybinds) noexcept
{
    window(saveSettings(bSaveKeybinds));
}

void UImGui::Window::close() noexcept
{
    window(close());
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
    window(refreshSettings());
}

void UImGui::Window::setIcon(const String name) noexcept
{
    window(setIcon(name));
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
    window(setCurrentWindowPosition(pos));
}

UImGui::FVector2 UImGui::Window::getWindowSizeInScreenCoords() noexcept
{
    return window(getWindowSizeInScreenCoords());
}

void UImGui::Window::setWindowSizeInScreenCoords(const FVector2 sz) noexcept
{
    window(setWindowSizeInScreenCoords(sz));
}

UImGui::FVector4 UImGui::Window::getWindowDecorationFrameDistances() noexcept
{
    return window(getWindowDecorationFrameDistances());
}

void UImGui::Window::pushWindowResizedInScreenCoordsCallback(const TFunction<void(int, int)>& f) noexcept
{
    window(pushWindowResizedInScreenCoordsCallback(f));
}

void UImGui::Window::pushWindowResizeCallback(const TFunction<void(int, int)>& f) noexcept
{
    window(pushWindowResizeCallback(f));
}

void UImGui::Window::pushWindowCloseCallback(const TFunction<void(void)>& f) noexcept
{
    window(pushWindowCloseCallback(f));
}

void UImGui::Window::requestWindowAttention() noexcept
{
    window(requestWindowAttention());
}

void UImGui::Window::hideWindow() noexcept
{
    window(hideWindow());
}

void UImGui::Window::showWindow() noexcept
{
    window(showWindow());
}

bool& UImGui::Window::getWindowHiddenSetting() noexcept
{
    return window(getWindowHiddenSetting());
}

bool UImGui::Window::getWindowSurfaceTransparent() noexcept
{
    return window(getWindowSurfaceTransparent());
}

void UImGui::Window::setWindowSurfaceTransparent(const bool bTransparent) noexcept
{
    window(setWindowSurfaceTransparent(bTransparent));
}

bool& UImGui::Window::getWindowSurfaceTransparentSetting() noexcept
{
    return window(getWindowSurfaceTransparentSetting());
}

void UImGui::Window::focusWindow() noexcept
{
    window(focusWindow());
}

bool& UImGui::Window::getWindowFocusedSetting() noexcept
{
    return window(getWindowFocusedSetting());
}

void UImGui::Window::pushWindowFocusCallback(const TFunction<void(bool)>& f) noexcept
{
    window(pushWindowFocusCallback(f));
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
    window(iconifyWindow());
}

void UImGui::Window::restoreWindowState() noexcept
{
    window(restoreWindowState());
}

void UImGui::Window::pushWindowIconifyCallback(const TFunction<void(bool)>& f) noexcept
{
    window(pushWindowIconifyCallback(f));
}

bool UImGui::Window::getWindowIconified() noexcept
{
    return window(getWindowIconified());
}

void UImGui::Window::pushWindowPositionChangeCallback(const TFunction<void(FVector2)>& f) noexcept
{
    window(pushWindowPositionChangeCallback(f));
}

UImGui::FVector2 UImGui::Window::getWindowContentScale() noexcept
{
    return window(getWindowContentScale());
}

void UImGui::Window::pushWindowContentScaleCallback(const TFunction<void(FVector2)>& f) noexcept
{
    window(pushWindowContentScaleCallback(f));
}

void UImGui::Window::setSizeLimits(const FVector2 min, const FVector2 max) noexcept
{
    window(setSizeLimits(min, max));
}

void UImGui::Window::setSizeLimitByAspectRatio(const FVector2 ratio) noexcept
{
    window(setSizeLimitByAspectRatio(ratio));
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
    window(setWindowResizeable(bResizeable));
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
    window(setWindowDecorated(bDecorated));
}

void UImGui::Window::pushWindowRefreshCallback(const TFunction<void(void)>& f) noexcept
{
    window(pushWindowRefreshCallback(f));
}

void UImGui::Window::maximiseWindow() noexcept
{
    window(maximiseWindow());
}

bool UImGui::Window::getWindowCurrentlyMaximised() noexcept
{
    return window(getWindowCurrentlyMaximised());
}

void UImGui::Window::pushWindowMaximiseCallback(const TFunction<void(bool)>& f) noexcept
{
    window(pushWindowMaximiseCallback(f));
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
    window(pushWindowOSDragDropCallback(f));
}

void UImGui::Window::Platform::setWindowAlwaysOnTop() noexcept
{
    window(Platform_setWindowAlwaysOnTop());
}

void UImGui::Window::Platform::setWindowAlwaysOnBottom() noexcept
{
    window(Platform_setWindowAlwaysOnBottom());
}

void UImGui::Window::Platform::setWindowShowingOnPager(const bool bShowInPager) noexcept
{
    window(Platform_setWindowShowingOnPager(bShowInPager));
}

bool UImGui::Window::Platform::getWindowShowingOnPager() noexcept
{
    return window(Platform_getWindowShowingOnPager());
}

void UImGui::Window::Platform::setWindowShowingOnTaskbar(const bool bShowOnTaskbar) noexcept
{
    window(Platform_setWindowShowingOnTaskbar(bShowOnTaskbar));
}

bool UImGui::Window::Platform::getWindowShowingOnTaskbar() noexcept
{
    return window(Platform_getWindowShowingOnTaskbar());
}

void UImGui::Window::Platform::setWindowType(const String type) noexcept
{
    window(Platform_setWindowType(type));
}

size_t UImGui::Window::Platform::getWindowID() noexcept
{
    return window(Platform_getWindowID());
}

void* UImGui::Window::Platform::getNativeWindowHandle() noexcept
{
    return window(Platform_getNativeWindowHandle());
}

UImGui::WindowPlatform UImGui::Window::Platform::getCurrentWindowPlatform() noexcept
{
    return window(Platform_getCurrentWindowPlatform());
}

void* UImGui::Window::Platform::getNativeDisplay() noexcept
{
    return window(Platform_getNativeDisplay());
}

void* UImGui::Window::getInternal() noexcept
{
    return window(getInternal());
}

UImGui::GenericWindow* UImGui::Window::get() noexcept
{
    return Global::get().window.window;
}

#undef window
