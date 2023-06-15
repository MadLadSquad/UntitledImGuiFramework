#pragma once
#include <C/CDefines.h>
#include <C/CTypes.h>
#include <C/Interfaces/CInput.h>

#ifdef __cplusplus
extern "C"
{
#endif

    // Event Safety - Any time
    UIMGUI_PUBLIC_API UImGui_String UImGui_Utility_sanitiseFilepath(UImGui_String str);

    // Event Safety - Any time
    UIMGUI_PUBLIC_API UImGui_String UImGui_Utility_keyToText(uint16_t key, bool bLong);

    // Event Safety - Any time
    UIMGUI_PUBLIC_API UImGui_String UImGui_Utility_keyToTextInputAction(UImGui_CInputAction* action, bool bLong);

    // Event Safety - Any time
    UIMGUI_PUBLIC_API void UImGui_Utility_removeConsole();

    // Event Safety - Any time
    // Sleep for X milliseconds
    UIMGUI_PUBLIC_API void UImGui_Utility_sleep(uint64_t milliseconds);
#ifdef __cplusplus
}
#endif