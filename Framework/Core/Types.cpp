#include "Types.hpp"
#include <imgui.h>

template <>
void c4::yml::write<UImGui::FString>(NodeRef* ref, UImGui::FString const& t)
{
    ref->save(t.c_str());
}

bool c4::yml::read(ConstNodeRef const& ref, UImGui::FString* t)
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
    ref->save(utf8::utf16to8(str));
}

bool c4::yml::read(ConstNodeRef const& ref, UImGui::FString16* t)
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
    ref->save(utf8::utf32to8(str));
}

bool c4::yml::read(ConstNodeRef const& ref, UImGui::FString32* t)
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
void c4::yml::write<UImGui::FVector4>(NodeRef* ref, UImGui::FVector4 const& t)
{
    ref->set_seq(FLOW_SL);

    ref->append_child().save(t.x);
    ref->append_child().save(t.y);
    ref->append_child().save(t.z);
    ref->append_child().save(t.w);
}

bool c4::yml::read(ConstNodeRef const& ref, UImGui::FVector4* t)
{
    if (!keyValid(ref) || !ref.is_seq() || ref.num_children() < 4)
        return false;
    ref.child(0).load(&t->x);
    ref.child(1).load(&t->y);
    ref.child(2).load(&t->z);
    ref.child(3).load(&t->w);
    return true;
}

template <>
void c4::yml::write<UImGui::FVector>(NodeRef* ref, UImGui::FVector const& t)
{
    ref->set_seq(FLOW_SL);

    ref->append_child().save(t.x);
    ref->append_child().save(t.y);
    ref->append_child().save(t.z);
}

bool c4::yml::read(ConstNodeRef const& ref, UImGui::FVector* t)
{
    if (!keyValid(ref) || !ref.is_seq() || ref.num_children() < 3)
        return false;
    ref.child(0).load(&t->x);
    ref.child(1).load(&t->y);
    ref.child(2).load(&t->z);
    return true;
}

template <>
void c4::yml::write<UImGui::FVector2>(NodeRef* ref, UImGui::FVector2 const& t)
{
    ref->set_seq(FLOW_SL);

    ref->append_child().save(t.x);
    ref->append_child().save(t.y);
}

bool c4::yml::read(ConstNodeRef const& ref, UImGui::FVector2* t)
{
    if (!keyValid(ref) || !ref.is_seq() || ref.num_children() < 2)
        return false;
    ref.child(0).load(&t->x);
    ref.child(1).load(&t->y);
    return true;
}

UImGui::FVector2::FVector2(const float x, const float y) noexcept : UImGui_FVector2()
{
    this->x = x;
    this->y = y;
}

UImGui::FVector::FVector(const float x, const float y, const float z) noexcept : UImGui_FVector()
{
    this->x = x;
    this->y = y;
    this->z = z;
}

UImGui::FVector4::FVector4(const float x, const float y, const float z, const float w) noexcept : UImGui_FVector4()
{
    this->x = x;
    this->y = y;
    this->z = z;
    this->w = w;
}

UImGui::FVector2::operator ImVec2() const noexcept
{
    return { this->x, this->y };
}

UImGui::FVector4::operator ImVec4() const noexcept
{
    return { this->x, this->y, this->z, this->w };
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

bool c4::yml::keyValid(const NodeRef ref) noexcept
{
    return !ref.invalid() && ref.readable() && !ref.empty();
}

bool c4::yml::keyValid(const ConstNodeRef ref) noexcept
{
    return !ref.invalid() && ref.readable() && !ref.empty();
}
