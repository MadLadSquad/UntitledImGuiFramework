#pragma once
#include <C/CDefines.h>
#include <C/CTypes.h>

#ifdef __cplusplus
extern "C"
{
#endif
    typedef struct UIMGUI_PUBLIC_API UImGui_ModuleSettings
    {
        size_t maxTransactions;

        bool os;
        bool dbus;
        bool uexec;
        bool theming;
        bool notifications;
        bool polkit;
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

    UIMGUI_PUBLIC_API void UImGui_Modules_save();
    UIMGUI_PUBLIC_API UImGui_ModuleSettings* UImGui_Modules_data();

#ifdef __cplusplus
}
#endif