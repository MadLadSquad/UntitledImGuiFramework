#include "Fontconfig.hpp"
#ifdef UIMGUI_OS_MODULE_ENABLED
#ifdef UIMGUI_UFONT_UTILS_SUBMODULE_ENABLED

UImGui::FString UImGui::FontconfigUtils::getDefaultFontFromLocale(LocaleTypes locale) noexcept
{
    FcInit();

    FcConfig* config = FcInitLoadConfigAndFonts();
    FcPattern* pattern = FcPatternCreate();
    FcLangSet* langset = FcLangSetCreate();
    //FcFontSet* fs = FcFontSetCreate();

    FcLangSetAdd(langset, (FcChar8*)localeStrings[static_cast<size_t>(locale)]);
    FcPatternAddLangSet(pattern, FC_LANG, langset);
    FcConfigSubstitute(config, pattern, FcMatchPattern);
    FcDefaultSubstitute(pattern);

    FcResult result;
    FcFontSet* fontset = FcFontSort(config, pattern, FcTrue, nullptr, &result);

    FString ret;
    if (fontset)
    {
        FcChar8* file;

        if (FcPatternGetString(fontset->fonts[0], FC_FILE, 1, &file) == FcResultMatch)
            ret = std::string((const char*)file);
        FcFontSetDestroy(fontset);
    }

    FcLangSetDestroy(langset);
    FcPatternDestroy(pattern);
    FcConfigDestroy(config);

    FcFini();

    return ret;
}

#endif
#endif

