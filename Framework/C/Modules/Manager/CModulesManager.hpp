#pragma once
#include <C/CDefines.h>
#include <C/CTypes.h>

#ifdef __cplusplus
extern "C"
{
#endif
    /**
     * @brief Struct containing settings for all modules.
     * @var maxTransactions - Maximum number of undo/redo transactions before removing old transactions
     * @var themeLocation - The string location of the theme file to be loaded and saved to by the theming module. Path
     * is prefixed by UIMGUI_CONFIG_DIR/Theme/
     * @var os, dbus, uexec, theming, ufont, i18n, undo_redo, plotting, knobs, spinners, toggles, text_utils,
     * cli_parser, xdg, open - Boolean that marks whether the module with the given name is enabled
     */
    typedef struct UIMGUI_PUBLIC_API UImGui_ModuleSettings
    {
        size_t maxTransactions;
        UImGui_String themeLocation;

        bool os;
        bool dbus;
        bool uexec;
        bool theming;
        bool ufont;
        bool i18n;
        bool undo_redo;
        bool plotting;
        bool knobs;
        bool spinners;
        bool toggles;
        bool text_utils;
        bool cli_parser;
        bool xdg;
        bool open;
    } UImGui_ModuleSettings;

    // Event safety - begin, style, post-begin
    UIMGUI_PUBLIC_API void UImGui_Modules_save();
    // Event safety - begin, style, post-begin
    UIMGUI_PUBLIC_API UImGui_ModuleSettings* UImGui_Modules_data();

#ifdef __cplusplus
}
#endif