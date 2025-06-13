#include "CUtility.h"
#include <Core/Utilities.hpp>
#include <Interfaces/Input.hpp>
#include <cstring>
#include <Core/Global.hpp>
#include <utfcpp/source/utf8.h>
#include <Core/Types.hpp>
#include <locale>

UImGui_String UImGui_Utility_sanitiseFilepath(const UImGui_String str)
{
    UImGui::FString s = str;
    UImGui::Utility::sanitiseFilepath(s);

    auto* ss = static_cast<char*>(UImGui_Allocator_allocate(s.size()));
    memcpy(ss, s.data(), s.size() + 1);
    return ss;
}

UImGui_String UImGui_Utility_keyToText(const uint16_t key, const bool bLong)
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
    UImGui::FString u8tmp = str;
    std::u32string tmp = utf8::utf8to32(u8tmp);

    for (auto& a : tmp)
#ifdef _WIN32
        a = std::tolower(a, std::locale(""));
#else
        a = std::tolower<wchar_t>(static_cast<wchar_t>(a), std::locale(""));
#endif
    u8tmp = utf8::utf32to8(tmp);

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
    UImGui::FString u8tmp = str;
    std::u32string tmp = utf8::utf8to32(u8tmp);

    for (auto& a : tmp)
#ifdef _WIN32
        a = std::toupper(a, std::locale(""));
#else
        a = std::toupper<wchar_t>(static_cast<wchar_t>(a), std::locale(""));
#endif
    u8tmp = utf8::utf32to8(tmp);

    auto tmpRealloc = static_cast<char*>(realloc(str, u8tmp.size()));
    if (tmpRealloc == nullptr)
    {
        UImGui_Allocator_deallocate(str);
        tmpRealloc = static_cast<char*>(UImGui_Allocator_allocate(u8tmp.size()));
    }
    return strcpy(tmpRealloc, u8tmp.data());
}