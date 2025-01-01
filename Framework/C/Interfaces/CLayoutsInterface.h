#pragma once
#include <C/CTypes.h>

#ifdef __cplusplus
extern "C"
{
#endif
    // Event Safety - begin, style, post-begin
    UIMGUI_PUBLIC_API bool* UImGui_Layouts_getLoadLayout();
    // Event Safety - begin, style, post-begin
    UIMGUI_PUBLIC_API bool* UImGui_Layouts_getSaveLayout();
    // Event Safety - begin, style, post-begin
    UIMGUI_PUBLIC_API UImGui_String UImGui_Layouts_layoutLocation();
#ifdef __cplusplus
}
#endif