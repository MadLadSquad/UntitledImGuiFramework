#pragma once
#include <iostream>
#include <vector>
#include <Core/Defines.hpp>
#include <ThirdParty/logger/src/UVKLog.h>
using namespace UVKLog;

namespace UImGui
{
    struct UIMGUI_PUBLIC_API FVector2
    {
        float x{};
        float y{};
    };

    struct UIMGUI_PUBLIC_API FVector
    {
        float x{};
        float y{};
        float z{};
    };

    struct UIMGUI_PUBLIC_API FVector4
    {
        float x{};
        float y{};
        float z{};
        float w{};
    };

    typedef std::string FString;
    typedef const char* String;
}