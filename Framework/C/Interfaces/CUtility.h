#pragma once
#include <C/CDefines.h>
#include <C/CTypes.h>
#include <C/Interfaces/CInput.h>

#ifdef __cplusplus
extern "C"
{
#endif
    typedef void UImGui_CGlobal;

    // Event safety - Any time
    // WARNING: By calling this function you become the owner of the string, and you should dispose of it correctly
    // using the UImGui_Allocator_deallocate function
    UIMGUI_PUBLIC_API UImGui_String UImGui_Utility_loadFileToString(UImGui_String location);

    // Event Safety - Any time
    // WARNING: By calling this function you become the owner of the string, and you should dispose of it correctly
    // using the UImGui_Allocator_deallocate function
    UIMGUI_PUBLIC_API UImGui_String UImGui_Utility_sanitiseFilepath(UImGui_String str);

    // Event Safety - Any time
    UIMGUI_PUBLIC_API UImGui_String UImGui_Utility_keyToText(CKeys key, bool bLong);

    // Event Safety - Any time
    UIMGUI_PUBLIC_API UImGui_String UImGui_Utility_keyToTextInputAction(const UImGui_CInputAction* action, bool bLong);

    // Event Safety - Any time
    UIMGUI_PUBLIC_API void UImGui_Utility_removeConsole();

    // Event Safety - Any time
    // Sleep for X milliseconds
    UIMGUI_PUBLIC_API void UImGui_Utility_sleep(uint64_t milliseconds);

    UIMGUI_PUBLIC_API void UImGui_Utility_loadContext(void* context);

    /**
     * @brief Converts a string to lower case using the default locale settings
     * @warning str will be overwritten, reassign to the return value
     * @note Event Safety - Any time
     * @note The returned string has to be freed
     * @returns A lower case string
     */
    UIMGUI_PUBLIC_API UImGui_String UImGui_Utility_toLower(char* str);

    /**
     * @brief Converts a string to upper case using the default locale settings
     * @warning str will be overwritten, reassign to the return value
     * @note Event Safety - Any time
     * @note The returned string has to be freed
     * @returns An upper case string
     */
    UIMGUI_PUBLIC_API UImGui_String UImGui_Utility_toUpper(char* str);

    // Event Safety - Any time
    UIMGUI_PUBLIC_API UImGui_CGlobal* UImGui_Global_get(UImGui_CGlobal* parent);
#ifdef __cplusplus
}
#endif