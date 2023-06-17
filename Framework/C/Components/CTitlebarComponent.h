#pragma once
#include <C/CTypes.h>
#include "CComponentCommon.h"

#ifdef __cplusplus
extern "C"
{
#endif
    // Event safety - Any time
    UIMGUI_PUBLIC_API UImGui_CComponentHandle UImGui_Titlebar_makeCTitlebarComponent(UImGui_ComponentRegularFun construct,
                                                                                     UImGui_ComponentRegularFun begin, UImGui_ComponentTickFun tick, UImGui_ComponentRegularFun end,
                                                                                     UImGui_ComponentRegularFun destruct, UImGui_CComponentData data);

    // Event safety - Any time
    UIMGUI_PUBLIC_API UImGui_CComponentData_P* UImGui_Titlebar_getCTitlebarComponentData(UImGui_CComponentHandle handle);

    // Event safety - Any time
    UIMGUI_PUBLIC_API UImGui_String UImGui_Titlebar_getCTitlebarComponentName(UImGui_CComponentHandle handle);

    // Event safety - Any time
    UIMGUI_PUBLIC_API void UImGui_Titlebar_destroyCTitlebarComponent(UImGui_CComponentHandle handle);
#ifdef __cplusplus
}
#endif