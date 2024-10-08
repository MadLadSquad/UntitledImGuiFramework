#pragma once
#include <vector>

// Types.hpp only contains C++ code. Check out the C header for more types
#include <C/CTypes.h>

// Dependencies
#include <../ThirdParty/logger/ULog.hpp>
#include <yaml-cpp/yaml.h>

using namespace ULog;

namespace UImGui
{
    // Redefine for C++
    typedef UImGui_FVector2 FVector2;
    typedef UImGui_FVector FVector;
    typedef UImGui_FVector4 FVector4;

    typedef UImGui_String String;
    typedef std::string FString;

    UIMGUI_PUBLIC_API YAML::Emitter& operator<<(YAML::Emitter& out, const FVector4& vect) noexcept;
    UIMGUI_PUBLIC_API YAML::Emitter& operator<<(YAML::Emitter& out, const FVector& vect) noexcept;
    UIMGUI_PUBLIC_API YAML::Emitter& operator<<(YAML::Emitter& out, const FVector2& vect) noexcept;

    UIMGUI_PUBLIC_API FVector2 operator+(FVector2 x, FVector2 y) noexcept;
    UIMGUI_PUBLIC_API FVector operator+(FVector x, FVector y) noexcept;
    UIMGUI_PUBLIC_API FVector4 operator+(FVector4 x, FVector4 y) noexcept;

    UIMGUI_PUBLIC_API FVector2 operator-(FVector2 x, FVector2 y) noexcept;
    UIMGUI_PUBLIC_API FVector operator-(FVector x, FVector y) noexcept;
    UIMGUI_PUBLIC_API FVector4 operator-(FVector4 x, FVector4 y) noexcept;

    UIMGUI_PUBLIC_API FVector2 operator*(FVector2 x, FVector2 y) noexcept;
    UIMGUI_PUBLIC_API FVector operator*(FVector x, FVector y) noexcept;
    UIMGUI_PUBLIC_API FVector4 operator*(FVector4 x, FVector4 y) noexcept;

    UIMGUI_PUBLIC_API FVector2 operator/(FVector2 x, FVector2 y) noexcept;
    UIMGUI_PUBLIC_API FVector operator/(FVector x, FVector y) noexcept;
    UIMGUI_PUBLIC_API FVector4 operator/(FVector4 x, FVector4 y) noexcept;

    UIMGUI_PUBLIC_API FVector2 operator+(FVector2 x, float y) noexcept;
    UIMGUI_PUBLIC_API FVector operator+(FVector x, float y) noexcept;
    UIMGUI_PUBLIC_API FVector4 operator+(FVector4 x, float y) noexcept;

    UIMGUI_PUBLIC_API FVector2 operator-(FVector2 x, float y) noexcept;
    UIMGUI_PUBLIC_API FVector operator-(FVector x, float y) noexcept;
    UIMGUI_PUBLIC_API FVector4 operator-(FVector4 x, float y) noexcept;

    UIMGUI_PUBLIC_API FVector2 operator*(FVector2 x, float y) noexcept;
    UIMGUI_PUBLIC_API FVector operator*(FVector x, float y) noexcept;
    UIMGUI_PUBLIC_API FVector4 operator*(FVector4 x, float y) noexcept;

    UIMGUI_PUBLIC_API FVector2 operator/(FVector2 x, float y) noexcept;
    UIMGUI_PUBLIC_API FVector operator/(FVector x, float y) noexcept;
    UIMGUI_PUBLIC_API FVector4 operator/(FVector4 x, float y) noexcept;
}

namespace YAML
{
    template<>
    struct convert<UImGui::FVector4>
    {
        static Node encode(const UImGui::FVector4& rhs) noexcept
        {
            Node node;
            node.push_back(rhs.x);
            node.push_back(rhs.y);
            node.push_back(rhs.z);
            node.push_back(rhs.w);
            node.SetStyle(EmitterStyle::Flow);
            return node;
        }

        static bool decode(const Node& node, UImGui::FVector4& rhs) noexcept
        {
            if (!node.IsSequence() || node.size() != 4)
                return false;

            rhs.x = node[0].as<float>();
            rhs.y = node[1].as<float>();
            rhs.z = node[2].as<float>();
            rhs.w = node[3].as<float>();
            return true;
        }
    };

    template<>
    struct convert<UImGui::FVector>
    {
        static Node encode(const UImGui::FVector& rhs) noexcept
        {
            Node node;
            node.push_back(rhs.x);
            node.push_back(rhs.y);
            node.push_back(rhs.z);
            node.SetStyle(EmitterStyle::Flow);
            return node;
        }

        static bool decode(const Node& node, UImGui::FVector& rhs) noexcept
        {
            if (!node.IsSequence() || node.size() != 3)
                return false;

            rhs.x = node[0].as<float>();
            rhs.y = node[1].as<float>();
            rhs.z = node[2].as<float>();
            return true;
        }
    };

    template<>
    struct convert<UImGui::FVector2>
    {
        static Node encode(const UImGui::FVector2& rhs) noexcept
        {
            Node node;
            node.push_back(rhs.x);
            node.push_back(rhs.y);
            node.SetStyle(EmitterStyle::Flow);
            return node;
        }

        static bool decode(const Node& node, UImGui::FVector2& rhs) noexcept
        {
            if (!node.IsSequence() || node.size() != 2)
                return false;

            rhs.x = node[0].as<float>();
            rhs.y = node[1].as<float>();
            return true;
        }
    };
}