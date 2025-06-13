#pragma once
#include <C/CTypes.h>

#ifdef __cplusplus
extern "C"
{
#endif
    typedef struct UIMGUI_PUBLIC_API UImGui_CPlugin
    {
        const char* name;
        void* handle;
    } UImGui_CPlugin;

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

    /**
     * @brief Returns a list of plugins
     * @param size - A pointer that will get filled with the size of the array of C Plugin structs
     * @note Does not give you access to the "attach" and "detach" functions. These can only be accessed through the C++ API
     * @note Event safety - post-startup
     * @return A list of C Plugin structs
     */
    UIMGUI_PUBLIC_API UImGui_CPlugin* UImGui_Plugins_getPlugins(size_t* size);

#ifdef __cplusplus
}
#endif