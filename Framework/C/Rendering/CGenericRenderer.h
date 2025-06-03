#pragma once
#include <C/CDefines.h>
#include <C/Internal/RendererData.h>
#ifdef __APPLE__
    #include <OpenGL/GL.h>
#else
    #include <glad/include/glad/gl.h>
#endif

#ifdef __cplusplus
extern "C"
{
#endif

    typedef void(*UImGui_CGenericRenderer_VoidVoidFun)(void);
    typedef void(*UImGui_CGenericRenderer_TickEvent)(float);

    UIMGUI_PUBLIC_API UImGui_CGenericRenderer* UImGui_CGenericRenderer_init(
        UImGui_CGenericRenderer_VoidVoidFun setupWindowIntegration,
        UImGui_CGenericRenderer_VoidVoidFun setupPostWindowIntegration,

        UImGui_CGenericRenderer_VoidVoidFun init,
        UImGui_CGenericRenderer_TickEvent renderStart,
        UImGui_CGenericRenderer_TickEvent renderEnd,
        UImGui_CGenericRenderer_VoidVoidFun destroy,

        UImGui_CGenericRenderer_VoidVoidFun ImGuiNewFrame,
        UImGui_CGenericRenderer_VoidVoidFun ImGuiShutdown,
        UImGui_CGenericRenderer_VoidVoidFun ImGuiInit,
        UImGui_CGenericRenderer_VoidVoidFun ImGuiRenderData,

        UImGui_CGenericRenderer_VoidVoidFun waitOnGPU,
        UImGui_CGenericRenderer_VoidVoidFun destruct
    );
    UIMGUI_PUBLIC_API void UImGui_CGenericRenderer_free(UImGui_CGenericRenderer* data);
#ifdef __cplusplus
}
#endif