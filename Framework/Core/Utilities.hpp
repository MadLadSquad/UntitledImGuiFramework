#pragma once
#include <Defines.hpp>
#include <Types.hpp>
#include "Events/Keys.hpp"

namespace UImGui
{
    class Global;

    class UIMGUI_PUBLIC_API Utility
    {
    public:
        Utility() = delete;
        Utility(const Utility&) = delete;
        void operator=(Utility const&) = delete;
        ~Utility() = delete;

        static void sanitiseFilepath(FString& str) noexcept;
        static void keyToText(FString& text, const uint16_t& key, bool bLong) noexcept;
        static FString keyToText(const uint16_t& key, bool bLong) noexcept;
        static Global& getGlobal() noexcept;
        static void removeConsole() noexcept;

        static FString toLower(String str) noexcept;
        static void toLower(FString& str) noexcept;

        static FString toUpper(String str) noexcept;
        static void toUpper(FString& str) noexcept;
    private:
        typedef std::array<std::pair<FString, FString>, Keys::UnknownKey - Keys::Space + 1> KeyStringsArrType;
        static void initializeKeyStrings(KeyStringsArrType& keyStrings) noexcept;
    };
}