#pragma once
#include <C/CTypes.h>
#include <C/CDefines.h>

#ifdef __cplusplus
extern "C"
{
#endif
    /**
     * @brief A structure that defines the default data of every UI component
     */
    typedef struct UIMGUI_PUBLIC_API UImGui_CComponentData
    {
        UImGui_ComponentState state;

        UImGui_String name;
        uint64_t id;
    } UImGui_CComponentData;

    /**
     * @brief A structure that gives you mutable access to the state and ID of a UI component. For access to the name
     * of the component use the corresponding getCTitlebarComponentName function
     */
    typedef struct UIMGUI_PUBLIC_API UImGui_CComponentData_P
    {
        UImGui_ComponentState* state;
        uint64_t* id;
    } UImGui_CComponentData_P;

    typedef void UImGui_CComponentHandle;
    typedef void(*UImGui_ComponentRegularFun)(UImGui_CComponentData_P*);
    typedef void(*UImGui_ComponentTickFun)(UImGui_CComponentData_P*, float);
#ifdef __cplusplus
}
#endif