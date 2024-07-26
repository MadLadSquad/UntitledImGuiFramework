#include "CUtility.h"
#include <Core/Utilities.hpp>
#include <Events/Input.hpp>
#include <cstring>
#include <Core/Global.hpp>

UImGui_String UImGui_Utility_sanitiseFilepath(const UImGui_String str)
{
    UImGui::FString s = str;
    UImGui::Utility::sanitiseFilepath(s);

    auto& global = UImGui::Global::get();
    global.deallocationStruct.keyStrings.push_back(s);
    return global.deallocationStruct.keyStrings.back().c_str();
}

UImGui_String UImGui_Utility_keyToText(const uint16_t key, const bool bLong)
{
    auto& global = UImGui::Global::get();
    global.deallocationStruct.keyStrings.push_back(UImGui::Utility::keyToText(key, bLong));
    return global.deallocationStruct.keyStrings.back().c_str();
}

UImGui_String UImGui_Utility_keyToTextInputAction(const UImGui_CInputAction* action, const bool bLong)
{
    UImGui::InputAction a;
    a.keyCodes.resize(action->keyCodesSize);
    memcpy(a.keyCodes.data(), action->keyCodes, a.keyCodes.size() * sizeof(size_t));

    auto& deallocationStruct = UImGui::Global::get().deallocationStruct;

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