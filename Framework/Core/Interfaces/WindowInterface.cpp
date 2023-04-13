#include "WindowInterface.hpp"
#include <Global.hpp>

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
    auto& a = Window::get().windowData;
    setTitle(a.name.c_str());
    setIcon(a.iconLocation.c_str());
}

void UImGui::Window::setIcon(UImGui::String name) noexcept
{
    Window::get().setIcon(name);
}

UImGui::FString& UImGui::Window::layoutLocation() noexcept
{
    return Window::get().windowData.layoutLocation;
}
