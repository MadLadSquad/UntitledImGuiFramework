#include "CUtility.h"
#include <Core/Utilities.hpp>
#include <Interfaces/Input.hpp>
#include <cstring>
#include <Core/Global.hpp>
#include <Core/Types.hpp>

UImGui_String UImGui_Utility_sanitiseFilepath(const UImGui_String str)
{
    UImGui::FString s = str;
    UImGui::Utility::sanitiseFilepath(s);

    auto* ss = static_cast<char*>(UImGui_Allocator_allocate(s.size() + 1));
    memcpy(ss, s.c_str(), s.size() + 1);
    return ss;
}

UImGui_String UImGui_Utility_keyToText(const CKeys key, const bool bLong)
{
    auto& global = UImGui::Global::get();
    const auto text = UImGui::Utility::keyToText(key, bLong);
    for (auto& f : global.deallocationStruct.keyStrings)
        if (f == text)
            return f.c_str();

    global.deallocationStruct.keyStrings.push_back(text);
    return global.deallocationStruct.keyStrings.back().c_str();
}

UImGui_String UImGui_Utility_keyToTextInputAction(const UImGui_CInputAction* action, const bool bLong)
{
    UImGui::InputAction a;
    a.keyCodes.resize(action->keyCodesSize);
    memcpy(a.keyCodes.data(), action->keyCodes, a.keyCodes.size() * sizeof(size_t));

    auto& deallocationStruct = UImGui::Global::get().deallocationStruct;
    const auto text = UImGui::Utility::keyToText(a, bLong);
    for (auto& f : deallocationStruct.keyStrings)
        if (f == text)
            return f.c_str();

    deallocationStruct.keyStrings.push_back(text);
    return deallocationStruct.keyStrings.back().c_str();
}

void UImGui_Utility_removeConsole()
{
    UImGui::Utility::removeConsole();
}

void UImGui_Utility_sleep(const uint64_t milliseconds)
{
    UImGui::Utility::sleep(milliseconds);
}

void UImGui_Utility_loadContext(void* context)
{
    UImGui::Utility::loadContext(context);
}


UImGui_CGlobal* UImGui_Global_get(UImGui_CGlobal* parent)
{
    return &UImGui::Global::get(static_cast<UImGui::Global*>(parent));
}

UImGui_String UImGui_Utility_toLower(char* str)
{
    // Delegated instead of duplicated - the C++ side sets up LC_CTYPE once and uses towlower, where this used to build a
    // std::locale("") per character, which is both slow and a throw site in a build without exception support
    const UImGui::FString u8tmp = UImGui::Utility::toLower(str);

    auto tmpRealloc = static_cast<char*>(realloc(str, u8tmp.size()));
    if (tmpRealloc == nullptr)
    {
        UImGui_Allocator_deallocate(str);
        tmpRealloc = static_cast<char*>(UImGui_Allocator_allocate(u8tmp.size()));
    }
    return strcpy(tmpRealloc, u8tmp.data());
}

UImGui_String UImGui_Utility_toUpper(char* str)
{
    const UImGui::FString u8tmp = UImGui::Utility::toUpper(str);

    auto tmpRealloc = static_cast<char*>(realloc(str, u8tmp.size()));
    if (tmpRealloc == nullptr)
    {
        UImGui_Allocator_deallocate(str);
        tmpRealloc = static_cast<char*>(UImGui_Allocator_allocate(u8tmp.size()));
    }
    return strcpy(tmpRealloc, u8tmp.data());
}

UImGui_String UImGui_Utility_loadFileToString(const UImGui_String location)
{
    const auto content = UImGui::Utility::loadFileToString(location);
    const auto result = static_cast<char*>(UImGui_Allocator_allocate(content.size()));
    memcpy(result, content.data(), content.size());
    return result;
}