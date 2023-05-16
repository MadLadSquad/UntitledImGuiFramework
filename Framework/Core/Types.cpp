#include "Types.hpp"

YAML::Emitter& UImGui::operator<<(YAML::Emitter& out, const UImGui::FVector4& vect) noexcept
{
    out << YAML::Flow;
    out << YAML::BeginSeq << vect.x << vect.y << vect.z << vect.w << YAML::EndSeq;
    return out;
}

YAML::Emitter& UImGui::operator<<(YAML::Emitter& out, const UImGui::FVector& vect) noexcept
{
    out << YAML::Flow;
    out << YAML::BeginSeq << vect.x << vect.y << vect.z << YAML::EndSeq;
    return out;
}

YAML::Emitter& UImGui::operator<<(YAML::Emitter& out, const UImGui::FVector2& vect) noexcept
{
    out << YAML::Flow;
    out << YAML::BeginSeq << vect.x << vect.y << YAML::EndSeq;
    return out;
}