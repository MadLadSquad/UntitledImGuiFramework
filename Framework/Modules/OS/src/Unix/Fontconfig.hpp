#pragma once
#ifdef UIMGUI_OS_MODULE_ENABLED
#ifdef UIMGUI_UFONT_UTILS_SUBMODULE_ENABLED
#include <Core/Types.hpp>
#include <fontconfig/fontconfig.h>
#include "Modules/Manager/LocaleConstants.hpp"

namespace UImGui
{

    class UIMGUI_PUBLIC_API FontconfigUtils
    {
    public:
        enum FontconfigFontWeights
        {
            FONTCONFIG_FONT_WEIGHT_REGULAR = 0,
            FONTCONFIG_FONT_WEIGHT_THIN = 1,
            FONTCONFIG_FONT_WEIGHT_EXTRALIGHT = 2,
            FONTCONFIG_FONT_WEIGHT_ULTRALIGHT = 3,
            FONTCONFIG_FONT_WEIGHT_LIGHT = 4,
            FONTCONFIG_FONT_WEIGHT_DEMILIGHT = 5,
            FONTCONFIG_FONT_WEIGHT_SEMILIGHT = 6,
            FONTCONFIG_FONT_WEIGHT_BOOK = 7,
            FONTCONFIG_FONT_WEIGHT_NORMAL = 8,
            FONTCONFIG_FONT_WEIGHT_MEDIUM = 9,
            FONTCONFIG_FONT_WEIGHT_DEMIBOLD = 10,
            FONTCONFIG_FONT_WEIGHT_SEMIBOLD = 11,
            FONTCONFIG_FONT_WEIGHT_BOLD = 12,
            FONTCONFIG_FONT_WEIGHT_EXTRABOLD = 13,
            FONTCONFIG_FONT_WEIGHT_COUNT = 14
        };

        // Given a locale returns a string that contains the path to the font file, on errors returns an empty string
        FString getDefaultFontFromLocale(LocaleTypes locale) noexcept;


    };
}

#endif
#endif