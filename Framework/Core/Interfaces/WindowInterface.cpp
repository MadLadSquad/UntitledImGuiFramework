#include "WindowInterface.hpp"
#include <Global.hpp>

void UImGui::Window::setTitle(UImGui::String name) noexcept
{
    internalGlobal.window.setTitle(name);
}

void UImGui::Window::setCursorVisibility(bool bVisible) noexcept
{
    internalGlobal.window.setCursorVisibility(bVisible);
}

float UImGui::Window::aspectRatio() noexcept
{
    return internalGlobal.window.windowSize.x / internalGlobal.window.windowSize.y;
}

UImGui::FVector2& UImGui::Window::windowSize() noexcept
{
    return internalGlobal.window.windowSize;
}

bool& UImGui::Window::fullscreen() noexcept
{
    return internalGlobal.window.windowData.fullscreen;
}

UImGui::FString& UImGui::Window::name() noexcept
{
    return internalGlobal.window.windowData.name;
}

UImGui::FString& UImGui::Window::iconLocation() noexcept
{
    return internalGlobal.window.windowData.iconLocation;
}

void UImGui::Window::saveSettings(bool bSaveKeybinds) noexcept
{
    internalGlobal.window.saveConfig(bSaveKeybinds);
}

void UImGui::Window::close() noexcept
{
    internalGlobal.window.close();
}

UImGui::FVector2 UImGui::Window::getCurrentWindowPosition() noexcept
{
    return { static_cast<float>(internalGlobal.window.windowCurrentPosY), static_cast<float>(internalGlobal.window.windowCurrentPosY) };
}

UImGui::FVector2 UImGui::Window::getLastWindowPosition() noexcept
{
    return { static_cast<float>(internalGlobal.window.windowLastPosY), static_cast<float>(internalGlobal.window.windowLastPosY) };
}

UImGui::FVector2 UImGui::Window::getWindowPositionChange() noexcept
{
    return
    {
        static_cast<float>(internalGlobal.window.windowCurrentPosX - internalGlobal.window.windowLastPosY),
        static_cast<float>(internalGlobal.window.windowCurrentPosX - internalGlobal.window.windowLastPosY)
    };
}
