#pragma once
#include <Core.hpp>

#ifdef UIMGUI_LOCALE_MODULE_ENABLED
    #include "Modules/Locale/src/localemod.hpp"
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
    #define IMSPINNER_DEMO
    #include "Modules/Spinners/ThirdParty/imspinner/imspinner.h"
#endif

#ifdef UIMGUI_TOGGLES_MODULE_ENABLED
    #include "Modules/Toggles/ThirdParty/imgui_toggle/imgui_toggle.h"
#endif

#ifdef UIMGUI_CLI_PARSER_MODULE_ENABLED
    #include "Modules/CLIParser/ThirdParty/UntitledCLIParser/CLIParser.hpp"
    #include "Modules/CLIParser/ThirdParty/UntitledCLIParser/C/cucli.h"
#endif

namespace UImGui
{
    struct UIMGUI_PUBLIC_API ModuleSettings
    {
        size_t maxTransactions = 100;
    };

    class ModulesManager
    {
    public:
        ModulesManager() = default;
    private:
        friend class Modules;
        friend class Global;

        friend class Locale;
        friend class LocaleManager;
        friend class StateTracker;


        ModuleSettings settings;
#ifdef UIMGUI_LOCALE_MODULE_ENABLED
        LocaleManager localeManager{};
#endif

#ifdef UIMGUI_UNDO_MODULE_ENABLED
        StateTracker stateTracker{};
#endif

        void init();
        void initModules();
        void save() const noexcept;
    };

    class UIMGUI_PUBLIC_API Modules
    {
    public:
        // Event Safety - Post-begin
        static ModuleSettings& data() noexcept;
        // Event Safety - Post-begin
        static void save() noexcept;
    private:
        friend class StateTracker;
        friend class Locale;

        static ModulesManager& get() noexcept;
    };
}
