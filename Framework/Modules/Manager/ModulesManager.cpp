#include "ModulesManager.hpp"
#include <Core/Global.hpp>
#include <yaml.h>

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
}

void UImGui::ModulesManager::save() const noexcept
{
    YAML::Emitter out;
    out << YAML::BeginMap;

    out << YAML::Key << "undo-max-transactions" << YAML::Value << settings.maxTransactions;

    out << YAML::EndMap;

    std::ofstream fout("../Config/Core/Modules.yaml");
    fout << out.c_str();
}

UImGui::ModuleSettings& UImGui::Modules::data() noexcept
{
    return internalGlobal.modulesManager.settings;
}

void UImGui::Modules::save() noexcept
{
    internalGlobal.modulesManager.save();
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