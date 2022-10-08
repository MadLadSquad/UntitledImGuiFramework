#pragma once
#include <Core.hpp>

#ifdef UIMGUI_LOCALE_MODULE_ENABLED
    #include "Modules/Locale/src/localemod.hpp"
#endif

#ifdef UIMGUI_UNDO_MODULE_ENABLED
    #include "Modules/Undo/src/Undo.hpp"
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
        friend class LocaleManager;
        friend class StateTracker;
        friend class Locale;

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
        static ModuleSettings& data() noexcept;
        static void save() noexcept;
    };
}
