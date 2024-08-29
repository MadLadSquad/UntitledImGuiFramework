#include <complex>
#ifdef UIMGUI_I18N_MODULE_ENABLED
#include "I18NModule.hpp"
#include <Manager/ModulesManager.hpp>

void UImGui::I18N::setCurrentLocale(const UI18N::LanguageCodes locale) noexcept
{
    getEngine().setCurrentLocale(locale);
}

ui18nstring UImGui::I18N::get(const char* id, const std::vector<ui18nstring>& positionalArgs, const ui18nmap<ui18nstring, ui18nstring>& args) noexcept
{
    return getEngine().get(id, positionalArgs, args);
}

void UImGui::I18N::pushVariable(const ui18nstring& name, const ui18nstring& val) noexcept
{
    getEngine().pushVariable(name, val);
}

const std::vector<UI18N::LanguageCodes>& UImGui::I18N::getExistingLocales() noexcept
{
    return getEngine().getExistingLocales();
}

UI18N::TranslationEngine& UImGui::I18N::getEngine() noexcept
{
    return Modules::get().translationEngine;
}

const UI18N_LanguageCodes* UImGui_I18N_getExistingLocales(size_t* size)
{
    return UI18N_TranslationEngine_getExistingLocales(&UImGui::I18N::getEngine(), size);
}

void UImGui_I18N_setCurrentLocale(const UI18N_LanguageCodes locale)
{
    UImGui::I18N::setCurrentLocale(locale);
}

void UImGui_I18N_pushVariable(const char* name, const char* val)
{
    UImGui::I18N::pushVariable(name, val);
}

const char* UImGui_I18N_get(const char* id, char** pargv, const size_t pargc, UI18N_Pair* argv, const size_t argc)
{
    return UI18N_TranslationEngine_get(&UImGui::I18N::getEngine(), id, pargv, pargc, argv, argc);
}
#endif