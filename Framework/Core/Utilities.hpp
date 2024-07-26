#pragma once
#include <Defines.hpp>
#include <Types.hpp>
#include <C/Internal/Keys.h>

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
        static void removeConsole() noexcept;

        // Event Safety - Any time
        static FString toLower(String str) noexcept;
        // Event Safety - Any time
        static void toLower(FString& str) noexcept;

        // Event Safety - Any time
        static FString toUpper(String str) noexcept;
        // Event Safety - Any time
        static void toUpper(FString& str) noexcept;

        // Event Safety - Any time
        // Sleep for X milliseconds
        static void sleep(uint64_t milliseconds) noexcept;
    private:
        friend class Global;
        static void interruptSignalHandler() noexcept;

        typedef std::array<std::pair<FString, FString>, Keys_UnknownKey + 1> KeyStringsArrType;
        static void initializeKeyStrings(KeyStringsArrType& keyStrings) noexcept;
    };
}