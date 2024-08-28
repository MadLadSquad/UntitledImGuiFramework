#pragma once
#include <C/CTypes.h>

#ifdef __cplusplus
extern "C"
{
#endif
    /**
     * @brief Loads a plugin from a location string
     * @param location - the file location for the plugin shared library
     * @note Event safety - post-startup
     * @return A boolean that is true on success and false on error
     */
    UIMGUI_PUBLIC_API bool UImGui_Plugins_load(UImGui_String location);

    /**
     * @brief A helper function that automatically loads all plugins that are added by the user through the standard
     * plugins interface
     * @note Event safety - post-startup
     */
    UIMGUI_PUBLIC_API void UImGui_Plugins_loadStandard();

#ifdef __cplusplus
}
#endif