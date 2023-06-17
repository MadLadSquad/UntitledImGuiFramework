#pragma once
#include <C/CTypes.h>
#include <C/CDefines.h>
#include "CComponentCommon.h"

#ifdef __cplusplus
extern "C"
{
#endif
    typedef struct UImGui_CInitInfo UImGui_CInitInfo;

    typedef void(*UImGui_CInstanceRegularFun)(UImGui_CInitInfo*);
    typedef void(*UImGui_CInstanceTickFun)(UImGui_CInitInfo*, float);

    typedef struct UIMGUI_PUBLIC_API UImGui_CInitInfo
    {
        UImGui_CComponentHandle* inlineComponents;
        size_t inlineComponentsSize;

        UImGui_CComponentHandle* titlebarComponents;
        size_t titlebarComponentsSize;

        UImGui_CComponentHandle* windowComponents;
        size_t windowComponentsSize;

        UImGui_CInstanceRegularFun* constructFuncs;
        size_t constructSize;

        UImGui_CInstanceRegularFun* beginFuncs;
        size_t beginSize;

        UImGui_CInstanceTickFun* tickFuncs;
        size_t tickSize;

        UImGui_CInstanceRegularFun* endFuncs;
        size_t endSize;

        UImGui_CInstanceRegularFun* destructFuncs;
        size_t destructSize;

        void* globalData;
        bool bGlobalAllocatedOnHeap;
    } UImGui_CInitInfo;

    // Event Safety - Any time
    UIMGUI_PUBLIC_API void UImGui_Instance_setCInitInfo(UImGui_CInitInfo* initInfo);
    // Event Safety - Any time
    UIMGUI_PUBLIC_API void* UImGui_Instance_getCppInitInfoGlobalData(bool* bAllocatedOnHeap);

    // Event Safety - Any time
    UIMGUI_PUBLIC_API char** UImGui_Instance_getCLIArguments(int* argc);
#ifdef __cplusplus
};
#endif
