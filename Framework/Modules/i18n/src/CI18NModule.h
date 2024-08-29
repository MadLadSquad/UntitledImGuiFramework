#pragma once
#ifdef UIMGUI_I18N_MODULE_ENABLED
#include <C/CDefines.h>
#include <i18n/ThirdParty/UntitledI18N/C/cui18n.h>

#ifdef __cplusplus
extern "C"
{
#endif
    // Event Safety - Any time
    UIMGUI_PUBLIC_API const char* UImGui_I18N_get(const char* id, char** pargv, size_t pargc, UI18N_Pair* argv, size_t argc);
    // Event Safety - Any time
    UIMGUI_PUBLIC_API void UImGui_I18N_pushVariable(const char* name, const char* val);
    // Event Safety - Any time
    UIMGUI_PUBLIC_API void UImGui_I18N_setCurrentLocale(UI18N_LanguageCodes locale);
    // Event Safety - Any time
    UIMGUI_PUBLIC_API const UI18N_LanguageCodes* UImGui_I18N_getExistingLocales(size_t* size);
#ifdef __cplusplus
}
#endif
#endif