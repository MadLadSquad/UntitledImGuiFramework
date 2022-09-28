#include "Input.hpp"
#include <Global.hpp>

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
    return internalGlobal.window.getKeys()[key];
}

const UImGui::InputAction& UImGui::Input::getAction(const UImGui::FString& name) noexcept
{
    for (auto& a : internalGlobal.window.inputActionList)
        if (a.name == name)
            return a;
    logger.consoleLog("Input action with name: ", UVK_LOG_TYPE_ERROR, name, ", does not exist!");
    std::terminate();
}

std::vector<UImGui::InputAction>& UImGui::Input::getActions() noexcept
{
    return internalGlobal.window.inputActionList;
}

UImGui::FVector2 UImGui::Input::getMousePositionChange() noexcept
{
    return internalGlobal.window.getMousePositionChange();
}

UImGui::FVector2 UImGui::Input::getCurrentMousePosition() noexcept
{
    return internalGlobal.window.getCurrentMousePosition();
}

UImGui::FVector2 UImGui::Input::getLastMousePosition() noexcept
{
    return internalGlobal.window.getLastMousePosition();
}

UImGui::FVector2 UImGui::Input::getScroll() noexcept
{
    return internalGlobal.window.getScroll();
}