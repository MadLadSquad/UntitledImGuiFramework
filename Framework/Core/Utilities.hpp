#pragma once
#include <Defines.hpp>
#include <Types.hpp>
#include "Events/Keys.hpp"

namespace UImGui
{
    class Global;
    class InputAction;

    class UIMGUI_PUBLIC_API Utility
    {
    public:
        Utility() = delete;
        Utility(const Utility&) = delete;
        void operator=(Utility const&) = delete;
        ~Utility() = delete;

        // Event Safety - Any time
        static void sanitiseFilepath(FString& str) noexcept;

        // Event Safety - Any time
        static void keyToText(FString& text, const uint16_t& key, bool bLong) noexcept;
        // Event Safety - Any time
        static FString keyToText(const uint16_t& key, bool bLong) noexcept;

        // Event Safety - Any time
        static void keyToText(FString& text, const InputAction& action, bool bLong) noexcept;
        // Event Safety - Any time
        static FString keyToText(const InputAction& action, bool bLong) noexcept;

        // Event Safety - Any time
        // DO NOT USE THIS, THIS IS ONLY HERE FOR INTERNAL REASONS!!! REALLY KNOW WHAT YOU'RE DOING WHEN USING THIS
        static Global& getGlobal() noexcept;

        // Event Safety - Any time
        static void removeConsole() noexcept;

        // Event Safety - Any time
        static FString toLower(String str) noexcept;
        // Event Safety - Any time
        static void toLower(FString& str) noexcept;

        // Event Safety - Any time
        static FString toUpper(String str) noexcept;
        // Event Safety - Any time
        static void toUpper(FString& str) noexcept;
    private:
        typedef std::array<std::pair<FString, FString>, Keys::UnknownKey + 1> KeyStringsArrType;
        static void initializeKeyStrings(KeyStringsArrType& keyStrings) noexcept;
    };
}