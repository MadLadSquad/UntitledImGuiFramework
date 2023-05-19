#include "Input.hpp"
#include <Interfaces/WindowInterface.hpp>
#include <GLFW/glfw3.h>

bool UImGui::InputAction::operator==(const uint8_t& st) const noexcept
{
    return state == st;
}

bool UImGui::InputAction::operator!=(const uint8_t& st) const noexcept
{
    return state != st;
}

uint8_t UImGui::Input::getKey(uint16_t key) noexcept
{
    return Window::get().keys[key];
}

const UImGui::InputAction& UImGui::Input::getAction(const UImGui::FString& name) noexcept
{
    for (auto& a : Window::get().inputActionList)
        if (a.name == name)
            return a;
    Logger::log("Input action with name: ", UVK_LOG_TYPE_ERROR, name, ", does not exist!");
    std::terminate();
}

std::vector<UImGui::InputAction>& UImGui::Input::getActions() noexcept
{
    return Window::get().inputActionList;
}

UImGui::FVector2 UImGui::Input::getMousePositionChange() noexcept
{
    return Window::get().getMousePositionChange();
}

UImGui::FVector2 UImGui::Input::getCurrentMousePosition() noexcept
{
    return Window::get().mousePos;
}

UImGui::FVector2 UImGui::Input::getLastMousePosition() noexcept
{
    return Window::get().mouseLastPos;
}

UImGui::FVector2 UImGui::Input::getScroll() noexcept
{
    return Window::get().getScroll();
}

void UImGui::Input::setCursorVisibility(UImGui::CursorVisibilityState visibility) noexcept
{
    glfwSetInputMode(Window::get().windowMain, GLFW_CURSOR, visibility);
}

UImGui::CursorVisibilityState UImGui::Input::getCurrentCursorVisibility() noexcept
{
    return static_cast<CursorVisibilityState>(glfwGetInputMode(Window::get().windowMain, GLFW_CURSOR));
}

void UImGui::Input::setStickyKeys(bool bEnable) noexcept
{
    glfwSetInputMode(Window::get().windowMain, GLFW_STICKY_KEYS, bEnable);
    glfwSetInputMode(Window::get().windowMain, GLFW_STICKY_MOUSE_BUTTONS, bEnable);
}

bool UImGui::Input::getStickyKeys() noexcept
{
    // Use this since we set both anyway
    return glfwGetInputMode(Window::get().windowMain, GLFW_STICKY_KEYS);
}

void UImGui::Input::setRawMouseMotion(bool bEnable) noexcept
{
    if (glfwRawMouseMotionSupported())
        glfwSetInputMode(Window::get().windowMain, GLFW_RAW_MOUSE_MOTION, bEnable);
}

bool UImGui::Input::getRawMouseMotion() noexcept
{
    return glfwGetInputMode(Window::get().windowMain, GLFW_RAW_MOUSE_MOTION);
}

void UImGui::Input::setLockKeyMods(bool bEnable) noexcept
{
    glfwSetInputMode(Window::get().windowMain, GLFW_LOCK_KEY_MODS, bEnable);
}

bool UImGui::Input::getLockKeyMods() noexcept
{
    return glfwGetInputMode(Window::get().windowMain, GLFW_LOCK_KEY_MODS);
}
