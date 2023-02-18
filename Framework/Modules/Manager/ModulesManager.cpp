#include "ModulesManager.hpp"
#include <Core/Global.hpp>
#include <yaml.h>
// The imspinner devs decided to just not include imgui
#include <imgui.h>
#include <imgui_internal.h>
#include "Modules/Spinners/ThirdParty/imspinner/imspinner.h"


void UImGui::ModulesManager::init()
{
    YAML::Node node;
    try
    {
        node = YAML::LoadFile("../Config/Core/Modules.yaml");
    }
    catch (YAML::BadFile&)
    {
        Logger::log("No Modules.yaml config file found, using the default configuration!", UVK_LOG_TYPE_WARNING);
        return;
    }

    if (node["undo-max-transactions"])
        settings.maxTransactions = node["undo-max-transactions"].as<size_t>();

    initModules();

    // Put this one after we have initialized the locale module
#ifdef UIMGUI_LOCALE_MODULE_ENABLED
    if (node["current-locale"])
        Locale::getCurrentLayout() = Locale::getLocaleID(node["current-locale"].as<std::string>());
#endif
}

void UImGui::ModulesManager::save() const noexcept
{
    YAML::Emitter out;
    out << YAML::BeginMap;

    out << YAML::Key << "undo-max-transactions" << YAML::Value << settings.maxTransactions;
#ifdef UIMGUI_LOCALE_MODULE_ENABLED
    out << YAML::Key << "current-locale" << YAML::Value << Locale::getLocaleName(Locale::getCurrentLayout());
#endif
    out << YAML::EndMap;

    std::ofstream fout("../Config/Core/Modules.yaml");
    fout << out.c_str();
}

UImGui::ModuleSettings& UImGui::Modules::data() noexcept
{
    return Modules::get().settings;
}

void UImGui::Modules::save() noexcept
{
    Modules::get().save();
}

UImGui::ModulesManager& UImGui::Modules::get() noexcept
{
    return internalGlobal.modulesManagerr;
}

void UImGui::ModulesManager::initModules()
{
#ifdef UIMGUI_UNDO_MODULE_ENABLED
    stateTracker.init();
#endif
#ifdef UIMGUI_LOCALE_MODULE_ENABLED
    localeManager.openLocaleConfig();
#endif
}