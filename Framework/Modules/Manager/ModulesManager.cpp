#include "ModulesManager.hpp"
#include <Core/Global.hpp>
#include <yaml-cpp/yaml.h>
// The imspinner devs decided to just not include imgui
#include <imgui.h>
#ifdef UIMGUI_SPINNERS_MODULE_ENABLED
    #include "Modules/Spinners/ThirdParty/imspinner/imspinner.h"
#endif

#ifdef UIMGUI_KNOBS_MODULE_ENABLED
    #define AddBezierCurve AddBezierCubic
    #include "Modules/Knobs/ThirdParty/imgui-knobs/imgui-knobs.h"
#endif

#define CHECK_MODULE_ENABLED(x)     if (mod[#x])    \
{                                                   \
    Modules::data().x = mod[#x].as<bool>();         \
}

#include <Utilities.hpp>
#include <Components/Instance.hpp>


void UImGui::ModulesManager::init(const FString& configDir)
{
    YAML::Node node;
    try
    {
        node = YAML::LoadFile(configDir + "Core/Modules.yaml");
    }
    catch (YAML::BadFile&)
    {
        Logger::log("No Modules.yaml config file found, using the default configuration!", UVK_LOG_TYPE_WARNING);
        return;
    }

    if (node["undo-max-transactions"])
        settings.maxTransactions = node["undo-max-transactions"].as<size_t>();

    initModules(UImGui_InitInfo_getProjectDir());
}

void UImGui::ModulesManager::save(const FString& configDir) const noexcept
{
    YAML::Emitter out;
    out << YAML::BeginMap;

    out << YAML::Key << "undo-max-transactions" << YAML::Value << settings.maxTransactions;
    out << YAML::EndMap;

    std::ofstream fout(configDir + "Core/Modules.yaml");
    fout << out.c_str();
}

UImGui::ModuleSettings& UImGui::Modules::data() noexcept
{
    return Modules::get().settings;
}

void UImGui::Modules::save() noexcept
{
    Modules::get().save(UImGui::Utility::getGlobal().instance->initInfo.configDir);
}

UImGui::ModulesManager& UImGui::Modules::get() noexcept
{
    return internalGlobal.modulesManagerr;
}

void UImGui::ModulesManager::initModules(const FString& projectDir)
{
    YAML::Node node;
    try
    {
        node = YAML::LoadFile(projectDir + "uvproj.yaml");
    }
    catch (YAML::BadFile&)
    {
        Logger::log("No uvproj.yaml config file found, using the default configuration!", UVK_LOG_TYPE_WARNING);
        return;
    }
    // Some specific applications may want to override the crash on error log functionality as they need to print errors
    // while not crashing. Examples: debuggers, language interpreters, validators, etc.
#ifdef PRODUCTION
    auto prodSettings = node["production"];
    if (prodSettings)
    {
        if (prodSettings["crash-on-error"])
            Logger::setCrashOnError(prodSettings["crash-on-error"].as<bool>());
    }
#endif

    auto mod = node["enabled-modules"];
    if (!mod)
        return;

    CHECK_MODULE_ENABLED(os);
    CHECK_MODULE_ENABLED(dbus);
    CHECK_MODULE_ENABLED(uexec);
    CHECK_MODULE_ENABLED(theming);
    CHECK_MODULE_ENABLED(ufont);
    CHECK_MODULE_ENABLED(i18n);
    CHECK_MODULE_ENABLED(undo_redo);
    CHECK_MODULE_ENABLED(plotting);
    CHECK_MODULE_ENABLED(knobs);
    CHECK_MODULE_ENABLED(spinners);
    CHECK_MODULE_ENABLED(toggles);
    CHECK_MODULE_ENABLED(text_utils);
    CHECK_MODULE_ENABLED(cli_parser);
    CHECK_MODULE_ENABLED(xdg);
    CHECK_MODULE_ENABLED(open);

#ifdef UIMGUI_UNDO_MODULE_ENABLED
    if (Modules::data().undo_redo)
        stateTracker.init();
#endif
#ifdef UIMGUI_I18N_MODULE_ENABLED
    if (Modules::data().i18n)
        if (auto result = translationEngine.init((UImGui::Utility::getGlobal().instance->initInfo.configDir + "Translations").c_str()) != UI18N_INIT_RESULT_SUCCESS)
            Logger::log("I18N module: There was an issue with loading or processing the translations. Error code: ", UVK_LOG_TYPE_WARNING, (int)result);
#endif
#ifdef UIMGUI_OS_MODULE_ENABLED
    #ifdef UIMGUI_OPEN_SUBMODULE_ENABLED
        if (Modules::data().open)
            UOpen::init();
    #endif
#endif
}

void UImGui::ModulesManager::destroy() noexcept
{
#ifdef UIMGUI_OS_MODULE_ENABLED
    #ifdef UIMGUI_OPEN_SUBMODULE_ENABLED
        if (Modules::data().open)
            UOpen::destroy();
    #endif
#endif
}
