#pragma once
#include <array>
#include <vector>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <deque>
#include <queue>
#include <forward_list>
#include <list>
#include <stack>
#include <functional>

#include <parallel-hashmap/parallel_hashmap/phmap.h>
#include <parallel-hashmap/parallel_hashmap/btree.h>
#include <utfcpp/source/utf8.h>

// Types.hpp only contains C++ code. Check out the C header for more types
#include <C/CTypes.h>

// Dependencies
#include <ThirdParty/logger/ULog.hpp>
#include <ryml.hpp>
#include <ryml_std.hpp>

#include "Allocator.hpp"

using namespace ULog;

namespace UImGui
{
    // Redefine for C++
    typedef UImGui_FVector2 FVector2;
    typedef UImGui_FVector FVector;
    typedef UImGui_FVector4 FVector4;

    typedef UImGui_String String;

#define TFunction std::function

    template<typename T, size_t S>
    using TArray = std::array<T, S>;

    template<typename Char>
    using FBasicString = std::basic_string<Char, std::char_traits<Char>, Allocator<Char>>;

    using FString = FBasicString<char>;
    using FString8 = FBasicString<char>;
    using FString16 = FBasicString<char16_t>;
    using FString32 = FBasicString<char32_t>;
    using FWString = FBasicString<wchar_t>;

    template<typename T>
    using TVector = std::vector<T, Allocator<T>>;

    template<typename T>
    using TDeque = std::deque<T, Allocator<T>>;

    template<typename T>
    using TQueue = std::queue<T, TDeque<T>>;

    template<typename T, typename Compare = std::less<typename TVector<T>::value_type>>
    using TPriorityQueue = std::priority_queue<T, TVector<T>, Compare>;

    template<typename T>
    using TStack = std::stack<T, TDeque<T>>;

    template<typename T>
    using TForwardList = std::forward_list<T, Allocator<T>>;

    template<typename T>
    using TList = std::list<T, Allocator<T>>;

    template<typename T, typename Hash = phmap::priv::hash_default_hash<T>, typename KeyEqual = phmap::priv::hash_default_eq<T>, size_t N = 4, typename Mutex = phmap::NullMutex>
    using TUnorderedSet = phmap::parallel_flat_hash_set<T, Hash, KeyEqual, Allocator<T>, N, Mutex>;

    template<typename T, typename Compare = phmap::Less<T>>
    using TSet = phmap::btree_set<T, Compare, Allocator<T>>;

    template<typename T, typename Compare = std::less<T>>
    using TSTDSet = std::set<T, Compare, Allocator<T>>;

    template<typename T, typename Compare = phmap::Less<T>>
    using TMultiset = phmap::btree_multiset<T, Compare, Allocator<T>>;

    template<typename T, typename Compare = std::less<T>>
    using TSTDMultiset = std::multiset<T, Compare, Allocator<T>>;

    template<typename T, typename Hash = std::hash<T>, typename KeyEqual = std::equal_to<T>>
    using TSTDUnorderedSet = std::unordered_set<T, Hash, KeyEqual, Allocator<T>>;

    template<typename T, typename Hash = std::hash<T>, typename KeyEqual = std::equal_to<T>>
    using TSTDUnorderedMultiset = std::unordered_multiset<T, Hash, KeyEqual, Allocator<T>>;

    template<typename Key, typename Value, typename Compare = phmap::Less<Key>>
    using TMap = phmap::btree_map<Key, Value, Compare, Allocator<phmap::priv::Pair<const Key, Value>>>;

    template<typename Key, typename Value, typename Compare = std::less<Key>>
    using TSTDMap = std::map<Key, Value, Compare, Allocator<std::pair<const Key, Value>>>;

    template<typename Key, typename Value, typename Compare = phmap::Less<Key>>
    using TMultimap = phmap::btree_multimap<Key, Value, Compare, Allocator<phmap::priv::Pair<const Key, Value>>>;

    template<typename Key, typename Value, typename Compare = std::less<Key>>
    using TSTDMultimap = std::multimap<Key, Value, Compare, Allocator<std::pair<const Key, Value>>>;

    template<typename Key, typename Value, typename Hash = std::hash<Key>, typename KeyEqual = std::equal_to<Key>>
    using TSTDUnorderedMap = std::unordered_map<Key, Value, Hash, KeyEqual, Allocator<std::pair<const Key, Value>>>;

    template<typename Key, typename Value, typename Hash = phmap::priv::hash_default_hash<Key>, typename Eq = phmap::priv::hash_default_eq<Key>, size_t N = 4, typename Mutex = phmap::NullMutex>
    using TUnorderedMap = phmap::parallel_flat_hash_map<Key, Value, Hash, Eq, Allocator<phmap::priv::Pair<const Key, const Value>>, N, Mutex>;

    template<typename Key, typename Value, typename Hash = std::hash<Key>, typename KeyEqual = std::equal_to<Key>>
    using TSTDUnorderedMultimap = std::unordered_multimap<Key, Value, Hash, KeyEqual, Allocator<std::pair<const Key, Value>>>;

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

namespace c4::yml
{
    UIMGUI_PUBLIC_API bool keyValid(NodeRef ref) noexcept;
    UIMGUI_PUBLIC_API bool keyValid(ConstNodeRef ref) noexcept;

    // ---------------------------------------------------- Strings ----------------------------------------------------

    template<>
    UIMGUI_PUBLIC_API void write<UImGui::FString>(NodeRef* ref, UImGui::FString const& t);

    template<>
    UIMGUI_PUBLIC_API bool read<UImGui::FString>(ConstNodeRef const& ref, UImGui::FString* t);

    template<>
    UIMGUI_PUBLIC_API void write<UImGui::FString16>(NodeRef* ref, UImGui::FString16 const& t);

    template<>
    UIMGUI_PUBLIC_API bool read<UImGui::FString16>(ConstNodeRef const& ref, UImGui::FString16* t);

    template<>
    UIMGUI_PUBLIC_API void write<UImGui::FString32>(NodeRef* ref, UImGui::FString32 const& t);

    template<>
    UIMGUI_PUBLIC_API bool read<UImGui::FString32>(ConstNodeRef const& ref, UImGui::FString32* t);

    // ---------------------------------------------------- Vectors ----------------------------------------------------

    template<>
    UIMGUI_PUBLIC_API void write<UImGui::FVector4>(NodeRef* ref, UImGui::FVector4 const& t);

    template<>
    UIMGUI_PUBLIC_API bool read<UImGui::FVector4>(ConstNodeRef const& ref, UImGui::FVector4* t);

    template<>
    UIMGUI_PUBLIC_API void write<UImGui::FVector>(NodeRef* ref, UImGui::FVector const& t);

    template<>
    UIMGUI_PUBLIC_API bool read<UImGui::FVector>(ConstNodeRef const& ref, UImGui::FVector* t);

    template<>
    UIMGUI_PUBLIC_API void write<UImGui::FVector2>(NodeRef* ref, UImGui::FVector2 const& t);

    template<>
    UIMGUI_PUBLIC_API bool read<UImGui::FVector2>(ConstNodeRef const& ref, UImGui::FVector2* t);

    // --------------------------------------------------- Sequences ---------------------------------------------------

    template<template<typename> class C, typename T>
    bool read(ConstNodeRef const& ref, C<T>* t)
    {
        if (!keyValid(ref) || !ref.is_seq())
            return false;

        for (const auto& a : ref.children())
        {
            T val{};
            a >> val;
            t->push_back(val);
        }
        return true;
    }

    template<template<typename> class C, typename T>
    void write(NodeRef* ref, C<T> const& t)
    {
        *ref |= SEQ;
        for (const auto& a : t)
            ref->append_child() << a;
    }

    // Check if similar to std::string
    template<typename T>
    concept IsStringLike = requires(T s, std::size_t n)
    {
        typename T::value_type;

        { s.data() } -> std::same_as<typename T::value_type*>;
        { std::as_const(s).data() } -> std::same_as<const typename T::value_type*>;
        { s.resize(n) } -> std::same_as<void>;
    } && std::is_trivial_v<typename T::value_type>;

    template<template<typename, typename, typename...> class C, typename Key, typename Val, typename ...Extra>
    bool read_dict(ConstNodeRef const& ref, C<Key, Val, Extra...>* t)
    {
        if (!keyValid(ref) || !ref.is_seq())
            return false;

        for (const auto& a : ref.children())
        {
            if (!a.is_map())
                continue;

            auto k = a.key();

            Key key{};
            if constexpr (IsStringLike<Key>)
            {
                key.resize(k.len);
                memcpy(&key.data(), k.data(), k.len);
            }
            else
                key = k.str;

            Val val{};
            a >> val;

            t->insert({key, val});
        }

        return true;
    }

    template<typename T>
    concept HasToChars = requires(substr buf, T const& t)
    {
        to_chars(buf, t);
    };

    template<template<typename, typename, typename...> class C, typename Key, typename Val, typename ...Extra>
    void write_dict(NodeRef* ref, C<Key, Val, Extra...> const& t)
    {
        *ref |= SEQ;
        for (const auto& a : t)
        {
            auto child = ref->append_child();
            child |= MAP;
            if constexpr (HasToChars<Key>)
                child[a.first] << a.second;
            else
                child[a.first.c_str()] << a.second;
        }
    }

#define WRITE_DICT_TYPE(x)                                  \
    template<typename Key, typename Val>                    \
    void write(NodeRef* ref, x<Key, Val> const& t)          \
    {                                                       \
        return write_dict(ref, t);                          \
    }

#define READ_DICT_TYPE(x)                                   \
    template<typename Key, typename Val>                    \
    bool read(ConstNodeRef const& ref, x<Key, Val>* t)      \
    {                                                       \
        return read_dict(ref, t);                           \
    }

    READ_DICT_TYPE(UImGui::TMap);
    READ_DICT_TYPE(UImGui::TSTDMap);
    READ_DICT_TYPE(UImGui::TMultimap);
    READ_DICT_TYPE(UImGui::TSTDMultimap);
    READ_DICT_TYPE(UImGui::TSTDUnorderedMap);
    READ_DICT_TYPE(UImGui::TUnorderedMap);
    READ_DICT_TYPE(UImGui::TSTDUnorderedMultimap);

    READ_DICT_TYPE(std::map);
    READ_DICT_TYPE(std::multimap);
    READ_DICT_TYPE(std::unordered_map);
    READ_DICT_TYPE(std::unordered_multimap);

    WRITE_DICT_TYPE(UImGui::TMap);
    WRITE_DICT_TYPE(UImGui::TSTDMap);
    WRITE_DICT_TYPE(UImGui::TMultimap);
    WRITE_DICT_TYPE(UImGui::TSTDMultimap);
    WRITE_DICT_TYPE(UImGui::TSTDUnorderedMap);
    WRITE_DICT_TYPE(UImGui::TUnorderedMap);
    WRITE_DICT_TYPE(UImGui::TSTDUnorderedMultimap);


    WRITE_DICT_TYPE(std::map);
    WRITE_DICT_TYPE(std::multimap);
    WRITE_DICT_TYPE(std::unordered_map);
    WRITE_DICT_TYPE(std::unordered_multimap);
}