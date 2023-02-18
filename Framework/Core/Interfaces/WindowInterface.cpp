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
    return { static_cast<float>(Window::get().windowCurrentPosY), static_cast<float>(Window::get().windowCurrentPosY) };
}

UImGui::FVector2 UImGui::Window::getLastWindowPosition() noexcept
{
    return { static_cast<float>(Window::get().windowLastPosY), static_cast<float>(Window::get().windowLastPosY) };
}

UImGui::FVector2 UImGui::Window::getWindowPositionChange() noexcept
{
    return
    {
        static_cast<float>(Window::get().windowCurrentPosX - Window::get().windowLastPosY),
        static_cast<float>(Window::get().windowCurrentPosX - Window::get().windowLastPosY)
    };
}

UImGui::WindowInternal& UImGui::Window::get() noexcept
{
    return internalGlobal.window;
}
