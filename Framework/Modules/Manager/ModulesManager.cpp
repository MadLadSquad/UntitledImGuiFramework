#include "ModulesManager.hpp"
#include <Core/Global.hpp>
#include <yaml-cpp/yaml.h>
#ifdef UIMGUI_SPINNERS_MODULE_ENABLED
    #include "Modules/Spinners/ThirdParty/imspinner/imspinner.h"
#endif

#ifdef UIMGUI_KNOBS_MODULE_ENABLED
    #define AddBezierCurve AddBezierCubic
    #include "Modules/Knobs/ThirdParty/imgui-knobs/imgui-knobs.h"
#endif

#define CHECK_MODULE_ENABLED(x)     if (mod[#x])    \
{                                                   \
    settings.x = mod[#x].as<bool>();                \
}

#include <Utilities.hpp>
#include <Components/Instance.hpp>


void UImGui::ModulesManager::init(const FString& configDir)
{
    YAML::Node node;
    try
    {
        node = YAML::LoadFile((configDir + "Core/Modules.yaml").c_str());
    }
    catch (YAML::BadFile&)
    {
        Logger::log("No Modules.yaml config file found, using the default configuration!", ULOG_LOG_TYPE_WARNING);
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

    std::ofstream fout((configDir + "Core/Modules.yaml").c_str());
    fout << out.c_str();
}

UImGui::ModuleSettings& UImGui::Modules::data() noexcept
{
    return Modules::get().settings;
}

void UImGui::Modules::save() noexcept
{
    get().save(Instance::get()->initInfo.configDir);
}

UImGui::ModulesManager& UImGui::Modules::get() noexcept
{
    return Global::get().modulesManager;
}

void UImGui::ModulesManager::initModules(const FString& projectDir)
{
    YAML::Node node;
    try
    {
        node = YAML::LoadFile((projectDir + "uvproj.yaml").c_str());
    }
    catch (YAML::BadFile&)
    {
        Logger::log("No uvproj.yaml config file found, using the default configuration!", ULOG_LOG_TYPE_WARNING);
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

    // Fix up double forms
    if (mod["undo-redo"])
        settings.undo_redo = mod["undo-redo"].as<bool>();
    if (mod["text-utils"])
        settings.text_utils = mod["text-utils"].as<bool>();
    if (mod["cli-parser"])
        settings.cli_parser = mod["cli-parser"].as<bool>();

#ifdef UIMGUI_UNDO_MODULE_ENABLED
    if (settings.undo_redo)
        stateTracker.init();
#endif
#ifdef UIMGUI_I18N_MODULE_ENABLED
    if (settings.i18n)
        if (const auto result = translationEngine.init((Instance::get()->initInfo.configDir + "Translations").c_str()) != UI18N_INIT_RESULT_SUCCESS)
            Logger::log("I18N module: There was an issue with loading or processing the translations. Error code: ", ULOG_LOG_TYPE_WARNING, CAST(int, result));
#endif
#ifdef UIMGUI_OS_MODULE_ENABLED
    #ifdef UIMGUI_OPEN_SUBMODULE_ENABLED
        if (settings.open)
            UOpen::init();
    #endif
#endif

    // Load standard plugins
#ifdef __APPLE__
    if (node["plugins"] && node["plugins"]["macos"])
        Global::get().plugins.standardPlugins = node["plugins"]["macos"].as<decltype(Global::get().plugins.standardPlugins)>();
#elif _WIN32
    if (node["plugins"] && node["plugins"]["windows"])
        Global::get().plugins.standardPlugins = node["plugins"]["windows"].as<decltype(Global::get().plugins.standardPlugins)>();
#else
    if (node["plugins"] && node["plugins"]["linux"])
        Global::get().plugins.standardPlugins = node["plugins"]["linux"].as<decltype(Global::get().plugins.standardPlugins)>();
#endif
}

void UImGui::ModulesManager::initialiseWithImGuiContext() const noexcept
{
#ifdef UIMGUI_PLOTTING_MODULE_ENABLED
    if (settings.plotting)
        ImPlot::CreateContext();
#endif
}

void UImGui::ModulesManager::applyCustomisations() const noexcept
{
#ifdef UIMGUI_THEME_MODULE_ENABLED
    if (settings.theming && (Modules::data().themeLocation != nullptr || Modules::data().themeLocation != ""))
        Theme::load((Instance::get()->initInfo.configDir + "Theme/" + Modules::data().themeLocation + ".theme.yaml").c_str());
#endif
}

void UImGui::ModulesManager::destroy() const noexcept
{
#ifdef UIMGUI_OS_MODULE_ENABLED
    #ifdef UIMGUI_OPEN_SUBMODULE_ENABLED
        if (settings.open)
            UOpen::destroy();
    #endif
#endif
}
