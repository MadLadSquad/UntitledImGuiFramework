#pragma once
#ifdef UIMGUI_LOCALE_MODULE_ENABLED
#include <Defines.hpp>
#include "LocaleConstants.hpp"
#include <vector>

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

        std::array<std::vector<std::pair<std::string, std::string>>, static_cast<int>(LocaleTypes::pirate) + 1> translations{};

        LocaleTypes defaultLayout = LocaleTypes::en_US;
        LocaleTypes currentLayout = LocaleTypes::en_US;
        FString emptyString;

        FString& getLocaleString(String original, LocaleTypes locale) noexcept;
    };

    class UIMGUI_PUBLIC_API Locale
    {
    public:
        static constexpr const char* getLocaleName(LocaleTypes types, bool bShort = true) noexcept;
        static LocaleTypes getLocaleID(const FString& str) noexcept;

        [[maybe_unused]] static const FString& getLocaleString(const FString& original, LocaleTypes locale) noexcept;
        [[maybe_unused]] static LocaleTypes& getCurrentLayout() noexcept;
        [[maybe_unused]] static LocaleTypes& getFallbackLayout() noexcept;
    };
}
#endif