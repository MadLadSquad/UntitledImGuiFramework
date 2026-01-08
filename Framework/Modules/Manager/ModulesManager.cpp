#include "ModulesManager.hpp"
#include <Core/Global.hpp>
#include <ryml.hpp>
#ifdef UIMGUI_SPINNERS_MODULE_ENABLED
    #include "Modules/Spinners/ThirdParty/imspinner/imspinner.h"
#endif

#ifdef UIMGUI_KNOBS_MODULE_ENABLED
    #define AddBezierCurve AddBezierCubic
    #include "Modules/Knobs/ThirdParty/imgui-knobs/imgui-knobs.h"
#endif

#define CHECK_MODULE_ENABLED(x)     if (keyValid(mod[#x]))     \
{                                                                                   \
    mod[#x] >> settings.x;                                                          \
}

#include <Utilities.hpp>
#include <Components/Instance.hpp>

void UImGui::ModulesManager::init(const FString& configDir)
{
    const auto file = Utility::loadFileToString(configDir + "Core/Modules.yaml");
    if (file.empty())
    {
        Logger::log("No Modules.yaml config file found! Reverting to the default configuration!", ULOG_LOG_TYPE_WARNING);
        return;
    }

    auto tree = ryml::parse_in_arena(file.c_str());
    if (tree.empty())
    {
        Logger::log("Couldn't load Modules.yaml due to a parser error! Reverting to the default configuration", ULOG_LOG_TYPE_WARNING);
        return;
    }

    auto root = tree.rootref();

    auto maxTransactions = root["max-transactions"];
    if (keyValid(maxTransactions))
        maxTransactions >> settings.maxTransactions;

    initModules(UImGui_InitInfo_getProjectDir());
}

void UImGui::ModulesManager::save(const FString& configDir) const noexcept
{
    ryml::Tree tree;
    ryml::NodeRef root = tree.rootref();
    root |= ryml::MAP;

    root["undo-max-transations"] << settings.maxTransactions;

    std::ofstream fout((configDir + "Core/Modules.yaml").c_str());
    fout << tree;
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

static void loadStandardPlugins(const ryml::ConstNodeRef& root, const UImGui::String platform, UImGui::TVector<UImGui::FString>& plugins) noexcept
{
    auto p = root["plugins"];
    if (keyValid(p) && keyValid(p[platform]))
        p[platform] >> plugins;
}

void UImGui::ModulesManager::initModules(const FString& projectDir)
{
    const auto file = Utility::loadFileToString(projectDir + "uvproj.yaml");
    if (file.empty())
    {
        Logger::log("No uvproj.yaml config file found. Reverting to the default configuration!", ULOG_LOG_TYPE_WARNING);
        return;
    }

    auto tree = ryml::parse_in_arena(file.c_str());
    if (tree.empty())
    {
        Logger::log("Couldn't load uvproj.yaml due to a parser error! Reverting to the default configuration", ULOG_LOG_TYPE_WARNING);
        return;
    }

    const auto root = tree.rootref();

    // Some specific applications may want to override the crash on error log functionality as they need to print errors
    // while not crashing. Examples: debuggers, language interpreters, validators, etc.
#ifdef PRODUCTION
    auto prodSettings = root["production"];
    if (keyValid(prodSettings))
    {
        auto crash = prodSettings["crash-on-error"];
        if (keyValid(crash))
        {
            bool val;
            crash >> val;
            Logger::setCrashOnError(val);
        }
    }
#endif

    auto mod = root["enabled-modules"];
    if (keyValid(mod))
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
    if (keyValid(mod["undo-redo"]))
        mod["undo-redo"] >> settings.undo_redo;

    if (keyValid(mod["text-utils"]))
        mod["text-utils"] >> settings.text_utils;

    if (keyValid(mod["cli-parser"]))
        mod["cli-parser"] >> settings.cli_parser;

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
    loadStandardPlugins(root, "macos", Global::get().plugins.standardPlugins);
#elif _WIN32
    loadStandardPlugins(root, "windows", Global::get().plugins.standardPlugins);
#else
    loadStandardPlugins(root, "linux", Global::get().plugins.standardPlugins);
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
    if (settings.theming && (Modules::data().themeLocation != nullptr || strcmp(Modules::data().themeLocation, "") != 0))
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
