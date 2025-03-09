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
#include <utfcpp/source/utf8.h>

// Types.hpp only contains C++ code. Check out the C header for more types
#include <C/CTypes.h>

// Dependencies
#include <../ThirdParty/logger/ULog.hpp>
#include <yaml-cpp/yaml.h>

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

    template<typename T>
    YAML::Emitter& outputSequence(YAML::Emitter& out, const T& t) noexcept
    {
        if (t.empty())
            return out;
        out << YAML::BeginSeq;
        for (const auto& a : t)
            out << a;
        out << YAML::EndSeq;
        return out;
    }

    UIMGUI_PUBLIC_API YAML::Emitter& operator<<(YAML::Emitter& out, const FString&) noexcept;
    UIMGUI_PUBLIC_API YAML::Emitter& operator<<(YAML::Emitter& out, const FString16&) noexcept;
    UIMGUI_PUBLIC_API YAML::Emitter& operator<<(YAML::Emitter& out, const FString32&) noexcept;

    // ---------------------------------------------------- Sequences --------------------------------------------------
#define OUTPUT_YAML_SEQUENCE_STREAM(x)                                          \
    template<typename T>                                                        \
    YAML::Emitter& operator<<(YAML::Emitter& out, const x<T>& t) noexcept       \
    {                                                                           \
        return outputSequence(out, t);                                          \
    }

    OUTPUT_YAML_SEQUENCE_STREAM(TVector);
    OUTPUT_YAML_SEQUENCE_STREAM(TDeque);
    OUTPUT_YAML_SEQUENCE_STREAM(TQueue);
    OUTPUT_YAML_SEQUENCE_STREAM(TPriorityQueue);
    OUTPUT_YAML_SEQUENCE_STREAM(TStack);
    OUTPUT_YAML_SEQUENCE_STREAM(TForwardList);
    OUTPUT_YAML_SEQUENCE_STREAM(TList);
    OUTPUT_YAML_SEQUENCE_STREAM(TUnorderedSet);
    OUTPUT_YAML_SEQUENCE_STREAM(TSet);
    OUTPUT_YAML_SEQUENCE_STREAM(TSTDSet);
    OUTPUT_YAML_SEQUENCE_STREAM(TMultiset);
    OUTPUT_YAML_SEQUENCE_STREAM(TSTDMultiset);
    OUTPUT_YAML_SEQUENCE_STREAM(TSTDUnorderedSet);
    OUTPUT_YAML_SEQUENCE_STREAM(TSTDUnorderedMultiset);

    // ------------------------------------------------------ Maps -----------------------------------------------------

    template<typename T>
    YAML::Emitter& outputMap(YAML::Emitter& out, const T& t) noexcept
    {
        if (t.empty())
            return out;

        out << YAML::BeginMap;
        for (const auto& a : t)
            out << YAML::Key << a.first << YAML::Value << a.second;
        out << YAML::EndMap;
        return out;
    }

#define OUTPUT_YAML_MAP_STREAM(x)                                                   \
    template<typename T, typename Key>                                              \
    YAML::Emitter& operator<<(YAML::Emitter& out, const x<T, Key>& t) noexcept      \
    {                                                                               \
        return outputMap(out, t);                                                   \
    }                                                                               \

    OUTPUT_YAML_MAP_STREAM(TMap);
    OUTPUT_YAML_MAP_STREAM(TSTDMap);
    OUTPUT_YAML_MAP_STREAM(TMultimap);
    OUTPUT_YAML_MAP_STREAM(TSTDMultimap);
    OUTPUT_YAML_MAP_STREAM(TSTDUnorderedMap);
    OUTPUT_YAML_MAP_STREAM(TUnorderedMap);
    OUTPUT_YAML_MAP_STREAM(TSTDUnorderedMultimap);

    // ----------------------------------------------------- Vectors ---------------------------------------------------


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
    template<typename T>
    Node encodeSequence(const T& t) noexcept
    {
        Node node(NodeType::Sequence);
        for (const auto& element : t)
            node.push_back(element);
        return node;
    }

    template<typename T>
    bool decodeSequence(const Node& node, T& t) noexcept
    {
        if (!node.IsSequence())
            return false;

        t.clear();
        for (const auto& element : node)
            t.push_back(element.as<typename T::value_type>());
        return true;
    }

    template<typename T>
    Node encodeMap(const T& t) noexcept
    {
        Node node(NodeType::Map);
        for (const auto& element : t)
            node.force_insert(element.first, element.second);
        return node;
    }

    template<typename T>
    bool decodeMap(const Node& node, T& t) noexcept
    {
        if (!node.IsMap())
            return false;

        t.clear();
        for (const auto& element : node)
            t[element.first.as<typename T::key_type>()] = element.second.as<typename T::mapped_type>();
        return true;
    }

    template<>
    struct convert<UImGui::FString>
    {
        static Node encode(const UImGui::FString& rhs) noexcept
        {
            return Node(rhs.c_str());
        }

        static bool decode(const Node& node, UImGui::FString& rhs) noexcept
        {
            if (!node.IsScalar())
                return false;
            rhs = node.Scalar();
            return true;
        }
    };

    template<>
    struct convert<UImGui::FString16>
    {
        static Node encode(const UImGui::FString16& rhs) noexcept
        {
            const std::u16string str(rhs);
            return Node(utf8::utf16to8(str));
        }

        static bool decode(const Node& node, UImGui::FString16& rhs) noexcept
        {
            if (!node.IsScalar())
                return false;
            rhs = utf8::utf8to16(node.Scalar());
            return true;
        }
    };

    template<>
    struct convert<UImGui::FString32>
    {
        static Node encode(const UImGui::FString32& rhs) noexcept
        {
            const std::u32string str(rhs);
            return Node(utf8::utf32to8(str));
        }

        static bool decode(const Node& node, UImGui::FString32& rhs) noexcept
        {
            if (!node.IsScalar())
                return false;
            rhs = utf8::utf8to32(node.Scalar());
            return true;
        }
    };

#define CREATE_YAML_CONVERT(x)                                                  \
    template<typename T>                                                        \
    struct convert<UImGui::x<T>>                                                \
    {                                                                           \
        static Node encode(const UImGui::x<T>& rhs) noexcept                    \
        {                                                                       \
            return encodeSequence(rhs);                                         \
        }                                                                       \
                                                                                \
        static bool decode(const Node& node, UImGui::x<T>& rhs) noexcept        \
        {                                                                       \
            return decodeSequence(node, rhs);                                   \
        }                                                                       \
    }

#define CREATE_YAML_CONVERT_MAP(x)                                              \
    template<typename T, typename V>                                            \
    struct convert<UImGui::x<T, V>>                                             \
    {                                                                           \
        static Node encode(const UImGui::x<T, V>& rhs) noexcept                 \
        {                                                                       \
            return encodeMap(rhs);                                              \
        }                                                                       \
                                                                                \
        static bool decode(const Node& node, UImGui::x<T, V>& rhs) noexcept     \
        {                                                                       \
            return decodeMap(node, rhs);                                        \
        }                                                                       \
    }

    CREATE_YAML_CONVERT(TVector);
    CREATE_YAML_CONVERT(TDeque);
    CREATE_YAML_CONVERT(TQueue);
    CREATE_YAML_CONVERT(TPriorityQueue);
    CREATE_YAML_CONVERT(TStack);
    CREATE_YAML_CONVERT(TForwardList);
    CREATE_YAML_CONVERT(TList);
    CREATE_YAML_CONVERT(TUnorderedSet);
    CREATE_YAML_CONVERT(TSet);
    CREATE_YAML_CONVERT(TSTDSet);
    CREATE_YAML_CONVERT(TMultiset);
    CREATE_YAML_CONVERT(TSTDMultiset);
    CREATE_YAML_CONVERT(TSTDUnorderedSet);
    CREATE_YAML_CONVERT(TSTDUnorderedMultiset);

    CREATE_YAML_CONVERT_MAP(TMap);
    CREATE_YAML_CONVERT_MAP(TSTDMap);
    CREATE_YAML_CONVERT_MAP(TMultimap);
    CREATE_YAML_CONVERT_MAP(TSTDMultimap);
    CREATE_YAML_CONVERT_MAP(TSTDUnorderedMap);
    CREATE_YAML_CONVERT_MAP(TUnorderedMap);
    CREATE_YAML_CONVERT_MAP(TSTDUnorderedMultimap);

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