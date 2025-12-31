#pragma once
#include <Types.hpp>
#include <C/Window/Keys.h>

struct ImGuiContext;
typedef void* (*ImGuiMemAllocFunc)(size_t sz, void* user_data);
typedef void  (*ImGuiMemFreeFunc )(void* ptr, void* user_data);

namespace UImGui
{
    class Global;
    struct InputAction;
    struct TitlebarMenuItem;

    class UIMGUI_PUBLIC_API Utility
    {
    public:
        Utility() = delete;
        Utility(const Utility&) = delete;
        void operator=(Utility const&) = delete;
        ~Utility() = delete;

        typedef TArray<std::pair<FString, FString>, Keys_COUNT> KeyStringsArrType;

        // Event Safety - Any time
        static FString loadFileToString(const FString& location) noexcept;

        // Event Safety - Any time
        static void sanitiseFilepath(FString& str) noexcept;

        // Event Safety - Any time
        static void keyToText(FString& text, CKeys key, bool bLong) noexcept;
        // Event Safety - Any time
        static FString keyToText(CKeys key, bool bLong) noexcept;

        // Event Safety - Any time
        static void keyToText(FString& text, const InputAction& action, bool bLong) noexcept;
        // Event Safety - Any time
        static FString keyToText(const InputAction& action, bool bLong) noexcept;

        // Event Safety - Any time
        static TVector<FString> splitString(const FString& str, String token) noexcept;

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

        // Loads a framework context from the plugin's side
        static void loadContext(void* context) noexcept;

        // Event Safety - Any time
        // Sleep for X milliseconds
        static void sleep(uint64_t milliseconds) noexcept;

        // Event Safety - Any time
        static KeyStringsArrType& getKeyStrings() noexcept;
    private:
        friend class Global;
        static void interruptSignalHandler() noexcept;

        static void initializeKeyStrings(KeyStringsArrType& keyStrings) noexcept;
    };
}