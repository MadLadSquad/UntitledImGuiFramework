#pragma once
#ifdef UIMGUI_I18N_MODULE_ENABLED
#include <Types.hpp>
#include <i18n/ThirdParty/UntitledI18N/UI18N.hpp>

namespace UImGui
{
    class UIMGUI_PUBLIC_API I18N
    {
    public:
        I18N() = delete;
        I18N(const I18N&) = delete;
        void operator=(I18N const&) = delete;

        // Event Safety - Any time
        static void setCurrentLocale(UI18N::LanguageCodes locale) noexcept;

        // Event Safety - Any time
        static ui18nstring get(const char* id, const std::vector<ui18nstring>& positionalArgs = {}, const ui18nmap<ui18nstring, ui18nstring>& args = {}) noexcept;
        // Event Safety - Any time
        static void pushVariable(const ui18nstring& name, const ui18nstring& val) noexcept;

        // Event Safety - Any time
        static const std::vector<UI18N::LanguageCodes>& getExistingLocales() noexcept;

        // Event Safety - Any time
        static UI18N::TranslationEngine& getEngine() noexcept;
    };
}
#endif