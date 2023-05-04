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

    class UIMGUI_PUBLIC_API ModulesManager
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
        // Event Safety - Post-begin
        static ModulesManager& get() noexcept;

        inline static bool os = false;
        inline static bool dbus = false;
        inline static bool uexec = false;
        inline static bool theming = false;
        inline static bool notifications = false;
        inline static bool polkit = false;
        inline static bool ufont = false;
        inline static bool audio = false;
        inline static bool locale = false;
        inline static bool network = false;
        inline static bool undo_redo = false;
        inline static bool video = false;
        inline static bool plotting = false;
        inline static bool knobs = false;
        inline static bool spinners = false;
        inline static bool toggles = false;
        inline static bool text_utils = false;
        inline static bool markdown = false;
        inline static bool cli_parser = false;
    private:
        friend class StateTracker;
        friend class Locale;
    };
}
