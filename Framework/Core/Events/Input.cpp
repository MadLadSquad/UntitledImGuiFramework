#include "Input.hpp"
#include <Interfaces/WindowInterface.hpp>

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
    return Window::get().getKeys()[key];
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
    return Window::get().getCurrentMousePosition();
}

UImGui::FVector2 UImGui::Input::getLastMousePosition() noexcept
{
    return Window::get().getLastMousePosition();
}

UImGui::FVector2 UImGui::Input::getScroll() noexcept
{
    return Window::get().getScroll();
}