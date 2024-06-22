#include "Types.hpp"

YAML::Emitter& UImGui::operator<<(YAML::Emitter& out, const FVector4& vect) noexcept
{
    out << YAML::Flow;
    out << YAML::BeginSeq << vect.x << vect.y << vect.z << vect.w << YAML::EndSeq;
    return out;
}

YAML::Emitter& UImGui::operator<<(YAML::Emitter& out, const FVector& vect) noexcept
{
    out << YAML::Flow;
    out << YAML::BeginSeq << vect.x << vect.y << vect.z << YAML::EndSeq;
    return out;
}

YAML::Emitter& UImGui::operator<<(YAML::Emitter& out, const FVector2& vect) noexcept
{
    out << YAML::Flow;
    out << YAML::BeginSeq << vect.x << vect.y << YAML::EndSeq;
    return out;
}

UImGui::FVector2 UImGui::operator+(const FVector2 x, const FVector2 y) noexcept
{
    return { x.x + y.x, x.y + y.y };
}

UImGui::FVector UImGui::operator+(const FVector x, const FVector y) noexcept
{
    return { x.x + y.x, x.y + y.y, x.z + y.z };
}

UImGui::FVector4 UImGui::operator+(const FVector4 x, const FVector4 y) noexcept
{
    return { x.x + y.x, x.y + y.y, x.z + y.z, x.w + y.w };
}

UImGui::FVector2 UImGui::operator-(const FVector2 x, const FVector2 y) noexcept
{
    return { x.x - y.x, x.y - y.y };
}

UImGui::FVector UImGui::operator-(const FVector x, const FVector y) noexcept
{
    return { x.x - y.x, x.y - y.y, x.z - y.z };
}

UImGui::FVector4 UImGui::operator-(const FVector4 x, const FVector4 y) noexcept
{
    return { x.x - y.x, x.y - y.y, x.z - y.z, x.w - y.w };
}

UImGui::FVector2 UImGui::operator*(const FVector2 x, const FVector2 y) noexcept
{
    return { x.x * y.x, x.y * y.y };
}

UImGui::FVector UImGui::operator*(const FVector x, const FVector y) noexcept
{
    return { x.x * y.x, x.y * y.y, x.z * y.z };
}

UImGui::FVector4 UImGui::operator*(const FVector4 x, const FVector4 y) noexcept
{
    return { x.x * y.x, x.y * y.y, x.z * y.z, x.w * y.w };
}

UImGui::FVector2 UImGui::operator/(const FVector2 x, const FVector2 y) noexcept
{
    return { x.x / y.x, x.y / y.y };
}

UImGui::FVector UImGui::operator/(const FVector x, const FVector y) noexcept
{
    return { x.x / y.x, x.y / y.y, x.z / y.z };
}

UImGui::FVector4 UImGui::operator/(const FVector4 x, const FVector4 y) noexcept
{
    return { x.x / y.x, x.y / y.y, x.z / y.z, x.w / y.w };
}

UImGui::FVector2 UImGui::operator+(const FVector2 x, const float y) noexcept
{
    return { x.x + y, x.y + y };
}

UImGui::FVector UImGui::operator+(const FVector x, const float y) noexcept
{
    return { x.x + y, x.y + y, x.z + y };
}

UImGui::FVector4 UImGui::operator+(const FVector4 x, const float y) noexcept
{
    return { x.x + y, x.y + y, x.z + y, x.w + y };
}

UImGui::FVector2 UImGui::operator-(const FVector2 x, const float y) noexcept
{
    return { x.x - y, x.y - y };
}

UImGui::FVector UImGui::operator-(const FVector x, const float y) noexcept
{
    return { x.x - y, x.y - y, x.z - y };
}

UImGui::FVector4 UImGui::operator-(const FVector4 x, const float y) noexcept
{
    return { x.x - y, x.y - y, x.z - y, x.w - y };
}

UImGui::FVector2 UImGui::operator*(const FVector2 x, const float y) noexcept
{
    return { x.x * y, x.y * y };
}

UImGui::FVector UImGui::operator*(const FVector x, const float y) noexcept
{
    return { x.x * y, x.y * y, x.z * y };
}

UImGui::FVector4 UImGui::operator*(const FVector4 x, const float y) noexcept
{
    return { x.x * y, x.y * y, x.z * y, x.w * y };
}

UImGui::FVector2 UImGui::operator/(const FVector2 x, const float y) noexcept
{
    return { x.x / y, x.y / y };
}

UImGui::FVector UImGui::operator/(const FVector x, const float y) noexcept
{
    return { x.x / y, x.y / y, x.z / y };
}

UImGui::FVector4 UImGui::operator/(const FVector4 x, const float y) noexcept
{
    return { x.x / y, x.y / y, x.z / y, x.w / y };
}