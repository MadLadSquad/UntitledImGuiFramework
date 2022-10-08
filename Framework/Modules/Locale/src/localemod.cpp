#ifdef UIMGUI_LOCALE_MODULE_ENABLED
#include "localemod.hpp"
#include "yaml.h"
#include <Utilities.hpp>
#include <Core/Global.hpp>

UImGui::LocaleManager::~LocaleManager() noexcept
{
    for (auto& a : translations)
    {
        for (auto& f : a)
        {
            f.first.clear();
            f.second.clear();
        }
        a.clear();
    }
}

void UImGui::LocaleManager::openLocaleConfig() noexcept
{
    YAML::Node node;
    try
    {
        node = YAML::LoadFile("../Config/Translations/translation-base.yaml");
    }
    catch (YAML::BadFile&)
    {
        logger.consoleLog("Couldn't open the translation base file!", UVK_LOG_TYPE_WARNING);
        return;
    }

    if (node["origin-locale"])
    {
        auto str = Utility::toLower(node["origin-locale"].as<std::string>().c_str());
        auto it = str.find('-');
        if (it != std::string::npos)
            str[it] = '_';

        defaultLayout = UImGui::Locale::getLocaleID(str);
        if (defaultLayout == static_cast<UImGui::LocaleTypes>(-1))
        {
            logger.consoleLog("A non-valid default layout string was submitted! The layout will not be used until the error is fixed! String: ", UVK_LOG_TYPE_WARNING, str);
            return;
        }
        currentLayout = defaultLayout;
    }

    const auto& strings = node["strings"];
    if (strings)
        for (const auto& a : strings)
            translations[static_cast<int>(currentLayout)].push_back({ a.as<std::string>(), a.as<std::string>() });
    if (exists(std_filesystem::path("../Config/Translations/")))
    {
        YAML::Node node2;
        for (auto& a : std_filesystem::directory_iterator(std_filesystem::path("../Config/Translations")))
        {
            if (a.path().filename() != "translation-base.yaml" && (a.path().extension().string() == ".yaml" || a.path().extension().string() == ".yml"))
            {
                try
                {
                    node2 = YAML::LoadFile(a.path().string());
                }
                catch (YAML::BadFile&)
                {
                    continue;
                }
                auto tmp = a.path().filename().string();
                tmp.erase(tmp.find_last_of('.'));
                auto id = Locale::getLocaleID(Utility::toLower(tmp.c_str()));
                if (node2["strings"])
                    for (const auto& f : node2["strings"])
                        if (f["string"] && f["translation"])
                            translations[static_cast<int>(id)].push_back({ f["string"].as<std::string>(), f["translation"].as<std::string>() });
            }
        }
        logger.consoleLog("Successfully loaded translations!", UVK_LOG_TYPE_SUCCESS);
    }
    else
        logger.consoleLog("Couldn't open the Config/Translations directory, no translations were loaded, make sure you at least provide an empty translation file or your program will crash in production!", UVK_LOG_TYPE_ERROR);
}

UImGui::FString& UImGui::LocaleManager::getLocaleString(UImGui::String original, UImGui::LocaleTypes locale) noexcept
{
    auto& arr = translations[static_cast<int>(locale)];
    for (auto& a : arr)
        if (a.first == original)
            return a.second;
    logger.consoleLog("Couldn't find the translated string for locale ", UVK_LOG_TYPE_WARNING, Locale::getLocaleName(locale, true), ". Reverting to default layout ", Locale::getLocaleName(defaultLayout, true), "!");
    return emptyString;
}

constexpr const char* UImGui::Locale::getLocaleName(UImGui::LocaleTypes types, bool bShort) noexcept
{
    if (bShort)
        return localeString[static_cast<int>(types)];
    return localeStringFull[static_cast<int>(types)];
}

UImGui::LocaleTypes UImGui::Locale::getLocaleID(const UImGui::FString& str) noexcept
{
    for (size_t ret = 0; ret < 229; ret++)
        if (localeString[ret] == str)
            return static_cast<LocaleTypes>(ret);
    return static_cast<LocaleTypes>(-1);
}

const UImGui::FString& UImGui::Locale::getLocaleString(const UImGui::FString& original, UImGui::LocaleTypes locale) noexcept
{
    for (auto& a : internalGlobal.modulesManager.localeManager.translations[static_cast<size_t>(locale)])
        if (a.first == original)
            return a.second;
    logger.consoleLog("Couldn't find the provided localization string, using the default one! Please fix this in the near future!", UVK_LOG_TYPE_WARNING);
    return original;
}

UImGui::LocaleTypes& UImGui::Locale::getCurrentLayout() noexcept
{
    return internalGlobal.modulesManager.localeManager.currentLayout;
}

UImGui::LocaleTypes& UImGui::Locale::getFallbackLayout() noexcept
{
    return internalGlobal.modulesManager.localeManager.defaultLayout;
}
#endif