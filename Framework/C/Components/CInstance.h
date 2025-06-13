#pragma once
#include <C/CTypes.h>
#include <C/CDefines.h>
#include "CComponentCommon.h"
#include <C/Internal/RendererData.h>
#include <C/Rendering/CGenericTexture.h>

#ifdef __cplusplus
extern "C"
{
#endif
    struct UImGui_CInitInfo;
    typedef void(*UImGui_CInstanceRegularFun)(struct UImGui_CInitInfo*);
    typedef void(*UImGui_CInstanceTickFun)(struct UImGui_CInitInfo*, float);

    /**
     * @brief C alternative of the InitInfo struct. std::vector members are replaced by pointers and size variables
     * @note This struct doesn't allow for modification of the directory strings
     */
    typedef struct UIMGUI_PUBLIC_API UImGui_CInitInfo
    {
        UImGui_CComponentHandle** inlineComponents;
        size_t inlineComponentsSize;

        UImGui_CComponentHandle** titlebarComponents;
        size_t titlebarComponentsSize;

        UImGui_CComponentHandle** windowComponents;
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

        UImGui_CGenericRenderer* customRenderer;
        UImGui_CGenericTexture* customTexture;
    } UImGui_CInitInfo;

    // Event Safety - Any time
    UIMGUI_PUBLIC_API void UImGui_Instance_setCInitInfo(UImGui_CInitInfo* initInfo);
    // Event Safety - Any time
    UIMGUI_PUBLIC_API void* UImGui_Instance_getCppInitInfoGlobalData(bool* bAllocatedOnHeap);

    // Event Safety - Any time
    UIMGUI_PUBLIC_API char** UImGui_Instance_getCLIArguments(int* argc);

    // Event Safety - Any time
    UIMGUI_PUBLIC_API UImGui_String UImGui_InitInfo_getFrameworkLibraryDir();
    // Event Safety - Any time
    UIMGUI_PUBLIC_API UImGui_String UImGui_InitInfo_getApplicationDir();
    // Event Safety - Any time
    UIMGUI_PUBLIC_API UImGui_String UImGui_InitInfo_getApplicationLibraryDir();

    // Event Safety - Any time
    UIMGUI_PUBLIC_API UImGui_String UImGui_InitInfo_getConfigDir();
    // Event Safety - Any time
    UIMGUI_PUBLIC_API UImGui_String UImGui_InitInfo_getProjectDir();

    // Event Safety - Any time
    UIMGUI_PUBLIC_API UImGui_String UImGui_InitInfo_getContentDir();

    // Event Safety - Any time
    UIMGUI_PUBLIC_API UImGui_String UImGui_InitInfo_getFrameworkIncludeDir();
    // Event Safety - Any time
    UIMGUI_PUBLIC_API UImGui_String UImGui_InitInfo_getApplicationIncludeDir();

#ifdef __cplusplus
};
#endif
