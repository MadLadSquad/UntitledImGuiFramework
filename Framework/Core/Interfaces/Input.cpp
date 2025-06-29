#include <Interfaces/Input.hpp>
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

uint8_t UImGui::Input::getKey(const uint16_t key) noexcept
{
    return Window::get().keys[key];
}

const UImGui::InputAction& UImGui::Input::getAction(const FString& name) noexcept
{
    for (auto& a : Window::get().inputActionList)
        if (a.name == name)
            return a;
    Logger::log("Input action with name: ", ULOG_LOG_TYPE_ERROR, name, ", does not exist!");
    std::terminate();
}

UImGui::TVector<UImGui::InputAction>& UImGui::Input::getActions() noexcept
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

void UImGui::Input::setCursorVisibility(const CursorVisibilityState visibility) noexcept
{
    glfwSetInputMode(Window::getInternal(), GLFW_CURSOR, visibility);
}

void UImGui::Input::setRawMouseMotion(const bool bEnable) noexcept
{
    if (glfwRawMouseMotionSupported())
        glfwSetInputMode(Window::getInternal(), GLFW_RAW_MOUSE_MOTION, bEnable);
}

bool UImGui::Input::getRawMouseMotion() noexcept
{
    return glfwGetInputMode(Window::getInternal(), GLFW_RAW_MOUSE_MOTION);
}