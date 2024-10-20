#pragma once
#include <Core.hpp>

// This imports the C API, look here for the definition of the ModuleSettings struct
#include <C/Modules/Manager/CModulesManager.hpp>

#ifdef UIMGUI_I18N_MODULE_ENABLED
    #include <i18n/ThirdParty/UntitledI18N/UI18N.hpp>
    #include <i18n/ThirdParty/UntitledI18N/C/cui18n.h>
#endif

#ifdef UIMGUI_UNDO_MODULE_ENABLED
    #include "Modules/Undo/src/Undo.hpp"
#endif

#ifdef UIMGUI_PLOTTING_MODULE_ENABLED
    #include "Modules/Plotting/ThirdParty/implot/implot.h"
#endif

#ifdef UIMGUI_OS_MODULE_ENABLED
    #include "Modules/OS/src/OS.hpp"
#endif

#ifdef UIMGUI_KNOBS_MODULE_ENABLED
    #define AddBezierCurve AddBezierCubic
    #include "Modules/Knobs/ThirdParty/imgui-knobs/imgui-knobs.h"
#endif

#ifdef UIMGUI_SPINNERS_MODULE_ENABLED
    #ifndef UIMGUI_EXECUTABLE
        #define IMSPINNER_DEMO
        #include "Modules/Spinners/ThirdParty/imspinner/imspinner.h"
    #endif
#endif

#ifdef UIMGUI_TOGGLES_MODULE_ENABLED
    #include "Modules/Toggles/ThirdParty/imgui_toggle/imgui_toggle.h"
#endif

#ifdef UIMGUI_CLI_PARSER_MODULE_ENABLED
    #include "Modules/CLIParser/ThirdParty/UntitledCLIParser/CLIParser.hpp"
    #include "Modules/CLIParser/ThirdParty/UntitledCLIParser/C/cucli.h"
#endif

#ifdef UIMGUI_TEXT_UTILS_MODULE_ENABLED
    #include <TextUtils/ThirdParty/UntitledImGuiTextUtils/UImGuiTextUtils.hpp>
#endif

#ifdef UIMGUI_THEME_MODULE_ENABLED
    #include <Theming/ThirdParty/UntitledImGuiTheme/UTheme.hpp>
#endif

namespace UImGui
{
    typedef UImGui_ModuleSettings ModuleSettings;

    class UIMGUI_PUBLIC_API ModulesManager
    {
    public:
        ModulesManager() = default;
    private:
        friend class Modules;
        friend class Global;
        friend class RendererInternal;

        friend class Locale;
        friend class LocaleManager;
        friend class StateTracker;
        friend class I18N;

        ModuleSettings settings =
        {
            .maxTransactions = 100,
            .os = false,
            .dbus = false,
            .uexec = false,
            .theming = false,
            .ufont = false,
            .i18n = false,
            .undo_redo = false,
            .plotting = false,
            .knobs = false,
            .spinners = false,
            .toggles = false,
            .text_utils = false,
            .cli_parser = false,
            .xdg = false,
            .open = false,
        };
#ifdef UIMGUI_I18N_MODULE_ENABLED
        UI18N::TranslationEngine translationEngine{};
#endif

#ifdef UIMGUI_UNDO_MODULE_ENABLED
        StateTracker stateTracker{};
#endif

        void init(const FString& configDir);
        void initModules(const FString& projectDir);
        void destroy() noexcept;

        void save(const FString& configDir) const noexcept;
    };

    class UIMGUI_PUBLIC_API Modules
    {
    public:
        // Event Safety - Post-begin
        static ModuleSettings& data() noexcept;
        // Event Safety - Post-begin
        static void save() noexcept;
        // Event Safety - Post-begin
        static ModulesManager& get() noexcept;
    private:
        friend class StateTracker;
        friend class Locale;
    };
}
