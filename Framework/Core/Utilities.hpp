#pragma once
#include <Defines.hpp>
#include <Types.hpp>

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
    };
}