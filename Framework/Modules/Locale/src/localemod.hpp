#pragma once
#ifdef UIMGUI_LOCALE_MODULE_ENABLED
#include <Defines.hpp>
#include "Modules/Manager/LocaleConstants.hpp"
#include <array>
#include <locale>

namespace UImGui
{
    class LocaleManager
    {
    public:
        LocaleManager() = default;
        ~LocaleManager() noexcept;
        void openLocaleConfig() noexcept;
    private:
        friend class Locale;

        // TODO: Refactor this, this does not make sense
        std::array<std::vector<std::pair<std::string, std::string>>, static_cast<int>(LocaleTypes::pirate) + 1> translations{};

        LocaleTypes defaultLayout = LocaleTypes::en;
        LocaleTypes currentLayout = LocaleTypes::en;
        FString emptyString;

        FString& getLocaleString(String original, LocaleTypes locale) noexcept;
    };

    class UIMGUI_PUBLIC_API Locale
    {
    public:
        // Event Safety - Post-begin
        static const char* getLocaleName(LocaleTypes types, bool bShort = true) noexcept;
        // Event Safety - Post-begin
        static LocaleTypes getLocaleID(const FString& str) noexcept;

        // Event Safety - Post-begin
        [[maybe_unused]] static const FString& getLocaleString(const FString& original, LocaleTypes locale) noexcept;
        // Event Safety - Post-begin
        [[maybe_unused]] static const FString& getLocaleString(const FString& original) noexcept;

        // Event Safety - Post-begin
        [[maybe_unused]] static LocaleTypes& getCurrentLayout() noexcept;
        // Event Safety - Post-begin
        [[maybe_unused]] static LocaleTypes& getFallbackLayout() noexcept;
    };
}
#endif