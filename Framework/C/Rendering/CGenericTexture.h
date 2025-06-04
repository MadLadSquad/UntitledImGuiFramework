#pragma once
#include <C/CDefines.h>
#include <C/CTypes.h>
#include <C/Rendering/CTexture.h>

#ifdef __cplusplus
extern "C"
{
#endif
    typedef void UImGui_CGenericTexture;
    typedef void(*UImGui_CGenericTexture_VoidFun)(UImGui_TextureData*);

    typedef void(*UImGui_CGenericTexture_InitFun)(UImGui_TextureData*, UImGui_String, bool);
    typedef uintptr_t(*UImGui_CGenericTexture_GetFun)(UImGui_TextureData*);
    typedef void(*UImGui_CGenericTexture_LoadFun)(UImGui_TextureData*, void*, UImGui_FVector2, uint32_t, bool);

    typedef UImGui_CGenericTexture_VoidFun UImGui_CGenericTexture_Clear;

    // Event safety - any-time
    UIMGUI_PUBLIC_API UImGui_CGenericTexture* UImGui_CGenericTexture_make(
        UImGui_CGenericTexture_InitFun init,
        UImGui_CGenericTexture_GetFun get,
        UImGui_CGenericTexture_LoadFun load,
        UImGui_CGenericTexture_Clear clear
    );

    // Event safety - end
    UIMGUI_PUBLIC_API void UImGui_CGenericTexture_free(UImGui_CGenericTexture* texture);
#ifdef __cplusplus
}
#endif