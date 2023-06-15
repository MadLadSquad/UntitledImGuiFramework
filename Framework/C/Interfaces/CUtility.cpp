#include "CUtility.h"
#include <Core/Utilities.hpp>
#include <Events/Input.hpp>
#include <cstring>
#include <Core/Global.hpp>

UImGui_String UImGui_Utility_sanitiseFilepath(UImGui_String str)
{
    UImGui::FString s = str;
    UImGui::Utility::sanitiseFilepath(s);

    UImGui::internalGlobal.deallocationStruct.keyStrings.push_back(s);
    return UImGui::internalGlobal.deallocationStruct.keyStrings.back().c_str();
}

UImGui_String UImGui_Utility_keyToText(uint16_t key, bool bLong)
{
    UImGui::internalGlobal.deallocationStruct.keyStrings.push_back(UImGui::Utility::keyToText(key, bLong));
    return UImGui::internalGlobal.deallocationStruct.keyStrings.back().c_str();
}

UImGui_String UImGui_Utility_keyToTextInputAction(UImGui_CInputAction* action, bool bLong)
{
    UImGui::InputAction a;
    a.keyCodes.resize(action->keyCodesSize);
    memcpy(a.keyCodes.data(), action->keyCodes, a.keyCodes.size() * sizeof(size_t));

    auto& deallocationStruct = UImGui::internalGlobal.deallocationStruct;

    deallocationStruct.keyStrings.push_back(UImGui::Utility::keyToText(a, bLong));
    return deallocationStruct.keyStrings.back().c_str();
}

void UImGui_Utility_removeConsole()
{
    UImGui::Utility::removeConsole();
}

void UImGui_Utility_sleep(uint64_t milliseconds)
{
    UImGui::Utility::sleep(milliseconds);
}