#pragma once
#include <iostream>
#include <vector>
#include <Core/Defines.hpp>
#include <ThirdParty/logger/src/UVKLog.h>
#include <yaml-cpp/yaml.h>

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

    YAML::Emitter& operator<<(YAML::Emitter& out, const FVector4& vect) noexcept;
    YAML::Emitter& operator<<(YAML::Emitter& out, const FVector& vect) noexcept;
    YAML::Emitter& operator<<(YAML::Emitter& out, const FVector2& vect) noexcept;

    typedef std::string FString;
    typedef const char* String;
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