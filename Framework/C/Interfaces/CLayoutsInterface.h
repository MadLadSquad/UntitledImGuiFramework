#pragma once
#include <C/CTypes.h>

#ifdef __cplusplus
extern "C"
{
#endif
    // Get/Set whether layouts should be loaded
    // Event Safety - Construct, post-construct
    UIMGUI_PUBLIC_API bool* UImGui_Layouts_getLoadLayout();

    // Get/Set whether layouts should be saved
    // Event Safety - Construct, post-construct
    UIMGUI_PUBLIC_API bool* UImGui_Layouts_getSaveLayout();

    // Event Safety - begin, style, post-begin
    UIMGUI_PUBLIC_API UImGui_String UImGui_Layouts_layoutLocation();

    // Event Safety - begin, style, post-begin
    UIMGUI_PUBLIC_API void UImGui_Layouts_loadLayout(UImGui_String layout);

    // Event Safety - begin, style, post-begin
    UIMGUI_PUBLIC_API void UImGui_Layouts_saveLayout(UImGui_String layout);

#ifdef __cplusplus
}
#endif