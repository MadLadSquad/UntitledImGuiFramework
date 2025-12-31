#include "Types.hpp"

template <>
void c4::yml::write<UImGui::FString>(NodeRef* ref, UImGui::FString const& t)
{
    *ref << t.c_str();
}

template <>
bool c4::yml::read<UImGui::FString>(ConstNodeRef const& ref, UImGui::FString* t)
{
    const auto val = ref.val();
    t->resize(val.len);
    memcpy(t->data(), val.data(), val.size());
    return true;
}

template <>
void c4::yml::write<UImGui::FString16>(NodeRef* ref, UImGui::FString16 const& t)
{
    const std::u16string str(t);
    *ref << utf8::utf16to8(str);
}

template <>
bool c4::yml::read<UImGui::FString16>(ConstNodeRef const& ref, UImGui::FString16* t)
{
    std::string str;
    const auto val = ref.val();
    str.resize(val.len);
    memcpy(str.data(), val.data(), val.size());

    *t = utf8::utf8to16(str);
    return true;
}

template <>
void c4::yml::write<UImGui::FString32>(NodeRef* ref, UImGui::FString32 const& t)
{
    const std::u32string str(t);
    *ref << utf8::utf32to8(str);
}

template <>
bool c4::yml::read<UImGui::FString32>(ConstNodeRef const& ref, UImGui::FString32* t)
{
    std::string str;
    const auto val = ref.val();
    str.resize(val.len);
    memcpy(str.data(), val.data(), val.size());

    *t = utf8::utf8to32(str);
    return true;
}

// ----------------------------------------------------- Vectors -----------------------------------------------------

template <>
void c4::yml::write<UImGui_FVector4>(NodeRef* ref, UImGui::FVector4 const& t)
{
    *ref |= SEQ | FLOW_SL;
    ref->append_child() << t.x;
    ref->append_child() << t.y;
    ref->append_child() << t.z;
    ref->append_child() << t.w;
}

template <>
bool c4::yml::read<UImGui_FVector4>(ConstNodeRef const& ref, UImGui::FVector4* t)
{
    if (ref.invalid() || !ref.is_seq() || ref.num_children() < 4)
        return false;
    ref.child(0) >> t->x;
    ref.child(1) >> t->y;
    ref.child(2) >> t->z;
    ref.child(3) >> t->w;
    return true;
}

template <>
void c4::yml::write<UImGui_FVector>(NodeRef* ref, UImGui::FVector const& t)
{
    *ref |= SEQ | FLOW_SL;
    ref->append_child() << t.x;
    ref->append_child() << t.y;
    ref->append_child() << t.z;
}

template <>
bool c4::yml::read<UImGui_FVector>(ConstNodeRef const& ref, UImGui::FVector* t)
{
    if (ref.invalid() || !ref.is_seq() || ref.num_children() < 3)
        return false;
    ref.child(0) >> t->x;
    ref.child(1) >> t->y;
    ref.child(2) >> t->z;
    return true;
}

template <>
void c4::yml::write<UImGui_FVector2>(NodeRef* ref, UImGui::FVector2 const& t)
{
    *ref |= SEQ | FLOW_SL;
    ref->append_child() << t.x;
    ref->append_child() << t.y;
}

template <>
bool c4::yml::read<UImGui_FVector2>(ConstNodeRef const& ref, UImGui::FVector2* t)
{
    if (ref.invalid() || !ref.is_seq() || ref.num_children() < 2)
        return false;
    ref.child(0) >> t->x;
    ref.child(1) >> t->y;
    return true;
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