#pragma once
#include <Types.hpp>

namespace UImGui
{
    // A struct for storing strings, which will be deallocated when the application closes
    struct UIMGUI_PUBLIC_API CDeallocationStruct
    {
        std::vector<FString> keyStrings;
    };
}