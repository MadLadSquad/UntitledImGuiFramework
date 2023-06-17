#pragma once
#include <C/CTypes.h>
#include "CComponentCommon.h"

#ifdef __cplusplus
extern "C"
{
#endif
    // Event safety - Any time
    UIMGUI_PUBLIC_API UImGui_CComponentHandle UImGui_WindowComponent_makeCWindowComponent(UImGui_ComponentRegularFun construct,
                                                                                          UImGui_ComponentRegularFun begin, UImGui_ComponentTickFun tick, UImGui_ComponentRegularFun end,
                                                                                          UImGui_ComponentRegularFun destruct, UImGui_CComponentData data);

    // Event safety - Any time
    UIMGUI_PUBLIC_API UImGui_CComponentData_P* UImGui_WindowComponent_getCWindowComponentData(UImGui_CComponentHandle handle);

    // Event safety - Any time
    UIMGUI_PUBLIC_API UImGui_String UImGui_WindowComponent_getCWindowComponentName(UImGui_CComponentHandle handle);

    // Event safety - Any time
    UIMGUI_PUBLIC_API void UImGui_WindowComponent_destroyCWindowComponent(UImGui_CComponentHandle handle);
#ifdef __cplusplus
}
#endif