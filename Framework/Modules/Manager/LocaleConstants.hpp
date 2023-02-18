#pragma once
#include "Core/Types.hpp"

namespace UImGui
{
    enum class [[maybe_unused]] LocaleTypes {
        aa, ab, ae, af, ak, am, an, ar_AE, ar_BH, ar_DZ, ar_EG, ar_IQ, ar_JO, ar_KW, ar_LB, ar_LY, ar_MA, ar_OM, ar_QA,
        ar_SA, ar_SD, ar_SY, ar_TN, ar_YE, as, av, ay, az, ba, be, bg, bh, bi, bm, bn, bo, br, bs, ca, ce, ch, co, cr,
        cs, cu, cv, cy, da, de_AT, de_CH, de_DE, de_LI, de_LU, dv, dz, ee, el, en, eo, es, et, eu, fa, ff, fi, fj, fo,
        fr_BE, fr_CA, fr_CH, fr_FR, fy, ga, gd, gl, gn, gu, gv, ha, he, hi, ho, hr, ht, hu, hy, hz, ia, id, ie, ig, ii,
        ik, io, is, it, iu, ja, jv, ka, kg, ki, kj, kk, kl, km, kn, ko, kr, ks, ku, kv, kw, ky, la, lb, lg, li, ln,
        lo, lt, lu, lv, mg, mh, mi, mk, ml, mn, mr, ms, mt, my, na, nb, nd, ne, ng, nl_BE, nl_NL, nn, no, nr, nv,
        ny, oc, oj, om, or_OR, os, pa, pi, pl, ps, pt, qu, rm, rn, ro, ru, rw, sa, sc, sd, se, sg, si, sk, sl, sm, sn, so,
        sq, sr, ss, st, su, sv, sw, ta, te, tg, th, ti, tk, tl, tn, to, tr, ts, tt, tw, ty, ug, uk, ur, uz, ve, vi, vo,
        wa, wo, xh, yi, yo, za, zh_CN, zh_HK, zh_MO, zh_SG, zh_TW, zu, pirate, COUNT
    };

    static constexpr String localeStrings[] =
    {
        "aa", "ab", "ae", "af", "ak", "am", "an", "ar-AE", "ar-BH", "ar-DZ", "ar-EG", "ar-IQ",
        "ar-JO", "ar-KW", "ar-LB", "ar-LY", "ar-MA", "ar-OM", "ar-QA", "ar-SA", "ar-SD", "ar-SY",
        "ar-TN", "ar-YE","as", "av", "ay", "az", "ba", "be", "bg", "bh", "bi",
        "bm", "bn","bo", "br", "bs", "ca", "ce", "ch", "co", "cr", "cs", "cu",
        "cv", "cy", "da", "de-AT", "de-CH", "de-DE", "de-LI", "de-LU",
        "dv", "dz", "ee", "el", "en", "eo", "es", "et", "eu", "fa", "ff",
        "fi", "fj", "fo", "fr-BE", "fr-CA", "fr-CH", "fr-FR",
        "fy", "ga", "gd", "gl", "gn", "gu", "gv", "ha", "he", "hi", "ho", "hr",
        "ht", "hu", "hy", "hz", "ia", "id", "ie", "ig", "ii", "ik", "io", "is",
        "it", "iu", "ja", "jv", "ka", "kg", "ki", "kj", "kk", "kl", "km", "kn",
        "ko", "kr", "ks", "ku", "kv", "kw", "ky", "la", "lb", "lg", "li", "ln",
        "lo", "lt", "lu", "lv", "mg", "mh", "mi", "mk", "ml", "mn", "mr", "ms",
        "mt", "my", "na", "nb", "nd", "ne", "ng", "nl-BE", "nl-NL", "nn", "no",
        "nr", "nv","ny", "oc", "oj", "om", "or", "os", "pa", "pi", "pl", "ps",
        "pt", "qu","rm", "rn", "ro", "ru", "rw", "sa", "sc", "sd", "se", "sg",
        "si", "sk","sl", "sm", "sn", "so", "sq", "sr", "ss", "st", "su", "sv",
        "sw", "ta","te", "tg", "th", "ti", "tk", "tl", "tn", "to", "tr", "ts",
        "tt", "tw","ty", "ug", "uk", "ur", "uz", "ve", "vi", "vo", "wa", "wo",
        "xh", "yi","yo", "za", "zh-CN", "zh-HK", "zh-MO", "zh-SG", "zh-TW", "zu", "pirate"
    };

    static constexpr String localeStringFull[] = {
        "Afar", "Abkhazian", "Avestan", "Afrikaans", "Akan", "Amharic", "Aragonese", "Arabic (United Arab Emirates)",
        "Arabic (Bahrain)", "Arabic (Algeria)", "Arabic (Egypt)", "Arabic (Iraq)","Arabic (Jordan)", "Arabic (Kuwait)",
        "Arabic (Lebanon)", "Arabic (Libya)", "Arabic (Morocco)", "Arabic (Oman)","Arabic (Qatar)", "Arabic (Saudi Arabia)",
        "Arabic (Sudan)", "Arabic (Syria)", "Arabic (Tunisia)", "Arabic (Yemen)","Assamese", "Avaric", "Aymara",
        "Azerbaijani", "Bashkir", "Belarusian", "Bulgarian", "Bihari", "Bislama", "Bambara", "Bengali",
        "Tibetan", "Breton", "Bosnian", "Catalan", "Chechen", "Chamorro", "Corsican", "Cree", "Czech",
        "Church Slavic", "Chuvash", "Welsh", "Danish", "German (Austria)", "German (Switzerland)", "German (Germany)",
        "German (Liechtenstein)", "German (Luxembourg)", "Divehi", "Dzongkha", "Ewe", "Greek", "English", "Esperanto",
        "Spanish", "Estonian", "Basque","Persian", "Fulah", "Finnish", "Fijian", "Faroese", "French (Belgium)",
        "French (Canada)", "French (Switzerland)", "French (France)", "Western Frisian", "Irish", "Gaelic", "Galician",
        "Guarani", "Manx", "Hausa", "Hebrew", "Hindi", "Hiri Motu", "Croatian", "Haitian", "Hungarian",
        "Armenian", "Herero", "Interlingua", "Indonesian", "Interlingue", "Igbo", "Sichuan Yi", "Inupiaq",
        "Ido","Icelandic","Italian", "Inuktitut", "Japanese", "Javanese", "Georgian", "Kongo", "Kikuyu",
        "Kuanyama", "Kazakh", "Kalaallisut", "Central Khmer", "Kannada", "Korean", "Kanuri", "Kashmiri",
        "Kurdish", "Komi", "Cornish", "Kirghiz", "Latin", "Luxembourgish", "Ganda", "Limburgan",
        "Lingala", "Lao", "Lithuanian", "Luba-Katanga", "Latvian", "Malagasy", "Marshallese", "Maori",
        "Macedonian", "Malayalam", "Mongolian", "Marathi", "Malay", "Maltese", "Burmese", "Nauru",
        "Navajo", "Chichewa", "Ndebele", "Nepali", "Ndonga", "Dutch", "Norwegian Bokmal",
        "Norwegian Nynorsk", "Norwegian", "South Ndebele", "Navajo", "Chichewa", "Occitan", "Ojibwa",
        "Oromo", "Oriya", "Punjabi", "Pali", "Polish", "Pashto", "Portuguese", "Quechua", "Romansh",
        "Rundi", "Romanian", "Russian", "Kinyarwanda", "Sanskrit", "Sardinian", "Sindhi", "Northern Sami",
        "Sango", "Sinhala", "Slovak", "Slovenian", "Samoan","Shona", "Somali", "Albanian","Serbian",
        "Swati", "Sotho", "Sundanese", "Swedish","Swahili", "Tamil", "Telugu", "Tajik", "Thai",
        "Tigrinya", "Turkmen", "Tagalog", "Tswana","Tonga", "Turkish", "Tsonga", "Tatar", "Twi",
        "Tahitian","Uighur", "Ukrainian", "Urdu", "Uzbek", "Venda", "Vietnamese", "Volapuk",
        "Walloon", "Wolof", "Xhosa", "Yiddish","Yoruba", "Zhuang", "Chinese", "Zulu", "Pirate"
    };
}