#pragma once
#include <C/CTypes.h>
#include "CComponentCommon.h"

#ifdef __cplusplus
extern "C"
{
#endif
    // Event safety - Any time
    UIMGUI_PUBLIC_API UImGui_CComponentHandle UImGui_Inline_makeCInlineComponent(UImGui_ComponentRegularFun construct,
                                                                                 UImGui_ComponentRegularFun begin, UImGui_ComponentTickFun tick, UImGui_ComponentRegularFun end,
                                                                                 UImGui_ComponentRegularFun destruct, UImGui_CComponentData data);

    // Event safety - Any time
    UIMGUI_PUBLIC_API UImGui_CComponentData_P* UImGui_Inline_getCInlineComponentData(UImGui_CComponentHandle handle);

    // Event safety - Any time
    UIMGUI_PUBLIC_API UImGui_String UImGui_Inline_getCInlineComponentName(UImGui_CComponentHandle handle);

    // Event safety - Any time
    UIMGUI_PUBLIC_API void UImGui_Inline_destroyCInlineComponent(UImGui_CComponentHandle handle);
#ifdef __cplusplus
}
#endif