#include "CInput.h"
#include "Interfaces/Input.hpp"

void UImGui_Input_setCursorVisibility(const UImGui_CursorVisibilityState visibility)
{
    UImGui::Input::setCursorVisibility(visibility);
}

UImGui_CursorVisibilityState UImGui_Input_getCurrentCursorVisibility()
{
    return UImGui::Input::getCurrentCursorVisibility();
}

void UImGui_Input_setStickyKeys(const bool bEnable)
{
    UImGui::Input::setStickyKeys(bEnable);
}

bool UImGui_Input_getStickyKeys()
{
    return UImGui::Input::getStickyKeys();
}

void UImGui_Input_setRawMouseMotion(const bool bEnable)
{
    UImGui::Input::setRawMouseMotion(bEnable);
}

bool UImGui_Input_getRawMouseMotion()
{
    return UImGui::Input::getRawMouseMotion();
}

void UImGui_Input_setLockKeyMods(const bool bEnable)
{
    UImGui::Input::setLockKeyMods(bEnable);
}

bool UImGui_Input_getLockKeyMods()
{
    return UImGui::Input::getLockKeyMods();
}

uint8_t UImGui_Input_getKey(const uint16_t key)
{
    return UImGui::Input::getKey(key);
}

UImGui_CInputAction UImGui_Input_getAction(const UImGui_String name)
{
    auto& a = UImGui::Input::getAction(name);
    return UImGui_CInputAction
    {
        .name = a.name.c_str(),
        .keyCodes = const_cast<uint16_t*>(a.keyCodes.data()),
        .keyCodesSize = a.keyCodes.size(),
        .state = a.state,
    };
}

UImGui_FVector2 UImGui_Input_getMousePositionChange()
{
    return UImGui::Input::getMousePositionChange();
}

UImGui_FVector2 UImGui_Input_getCurrentMousePosition()
{
    return UImGui::Input::getCurrentMousePosition();
}

UImGui_FVector2 UImGui_Input_getLastMousePosition()
{
    return UImGui::Input::getLastMousePosition();
}

UImGui_FVector2 UImGui_Input_getScroll()
{
    return UImGui::Input::getScroll();
}