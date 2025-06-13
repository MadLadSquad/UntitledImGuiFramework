#pragma once
#include <C/CTypes.h>
#include "CComponentCommon.h"

#ifdef __cplusplus
extern "C"
{
#endif
    /**
     * @brief Allocates and creates a new inline component from the provided callback functions and returns a handle
     * to it
     * @param construct - A function to be called in the constructor(only really useful during reallocation)
     * @param begin - A "begin" event callback function
     * @param tick - A "tick" event callback function
     * @param end - An "end" event callback function
     * @param destruct - A function to be called during the destructor
     * @param data - C data for the component. Check out the definition of UImGui_CComponentData
     * @return A handle to the component
     * @note Event safety - Any time
     */
    UIMGUI_PUBLIC_API UImGui_CComponentHandle* UImGui_Inline_makeCInlineComponent(UImGui_ComponentRegularFun construct,
                                                                                 UImGui_ComponentRegularFun begin, UImGui_ComponentTickFun tick, UImGui_ComponentRegularFun end,
                                                                                 UImGui_ComponentRegularFun destruct, UImGui_CComponentData data);

    /**
     * @param handle - A C component handle that should be acquired from UImGui_Inline_makeCInlineComponent
     * @return A pointer to the C data for the component. Check out the definition of UImGui_CComponentData
     * @note Event safety - Any time
     */
    UIMGUI_PUBLIC_API const UImGui_CComponentData_P* UImGui_Inline_getCInlineComponentData(const UImGui_CComponentHandle* handle);

    /**
     * @brief Gets the name of the component
     * @param handle - A C component handle that should be acquired from UImGui_Inline_makeCInlineComponent
     * @return A string containing the name of the component
     * @note Event safety - Any time
     */
    UIMGUI_PUBLIC_API UImGui_String UImGui_Inline_getCInlineComponentName(const UImGui_CComponentHandle* handle);

    /**
     * @brief Frees a C component handle acquired from UImGui_Inline_makeCInlineComponent
     * @param handle - A C component handle that should be acquired from UImGui_Inline_makeCInlineComponent
     * @note Event safety - Any time
     */
    UIMGUI_PUBLIC_API void UImGui_Inline_destroyCInlineComponent(const UImGui_CComponentHandle* handle);
#ifdef __cplusplus
}
#endif