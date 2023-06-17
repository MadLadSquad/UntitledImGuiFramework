#pragma once
#include <C/CTypes.h>
#include <C/CDefines.h>

#ifdef __cplusplus
extern "C"
{
#endif
    typedef struct UIMGUI_PUBLIC_API UImGui_CComponentData
    {
        UImGui_ComponentState state;

        UImGui_String name;
        uint64_t id;
    } UImGui_CComponentData;

    typedef struct UIMGUI_PUBLIC_API UImGui_CComponentData_P
    {
        UImGui_ComponentState* state;
        uint64_t* id;
    } UImGui_CComponentData_P;

    typedef void* UImGui_CComponentHandle;
    typedef void(*UImGui_ComponentRegularFun)(UImGui_CComponentData_P*);
    typedef void(*UImGui_ComponentTickFun)(UImGui_CComponentData_P*, float);
#ifdef __cplusplus
}
#endif