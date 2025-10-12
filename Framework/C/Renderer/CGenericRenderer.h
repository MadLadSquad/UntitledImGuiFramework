#pragma once
#include <C/CDefines.h>
#include <C/Window/RendererData.h>
#ifdef __APPLE__
    #include <OpenGL/GL.h>
#else
    #include <glad/include/glad/gl.h>
#endif

#ifdef __cplusplus
extern "C"
{
#endif

    struct UImGui_CGenericRenderer_InitInfo;

    typedef void(*UImGui_CGenericRenderer_VoidVoidFun)(struct UImGui_CGenericRenderer_InitInfo*);
    typedef void(*UImGui_CGenericRenderer_TickEvent)(struct UImGui_CGenericRenderer_InitInfo*, float);

    typedef enum UImGui_RendererAPITypeHint
    {
        UIMGUI_RENDERER_API_TYPE_HINT_OPENGL,
        UIMGUI_RENDERER_API_TYPE_HINT_VULKAN,
        UIMGUI_RENDERER_API_TYPE_HINT_WEBGPU,
        UIMGUI_RENDERER_API_TYPE_HINT_METAL,
        UIMGUI_RENDERER_API_TYPE_HINT_D3D,
        UIMGUI_RENDERER_API_TYPE_HINT_OTHER
    } UImGui_RendererAPITypeHint;

    typedef struct UIMGUI_PUBLIC_API UImGui_CGenericRenderer_InitInfo
    {
        UImGui_CGenericRenderer_VoidVoidFun setupWindowIntegration;
        UImGui_CGenericRenderer_VoidVoidFun setupPostWindowIntegration;

        UImGui_CGenericRenderer_VoidVoidFun init;

        UImGui_CGenericRenderer_TickEvent renderStart;
        UImGui_CGenericRenderer_TickEvent renderEnd;

        UImGui_CGenericRenderer_VoidVoidFun destroy;

        UImGui_CGenericRenderer_VoidVoidFun ImGuiNewFrame;
        UImGui_CGenericRenderer_VoidVoidFun ImGuiShutdown;
        UImGui_CGenericRenderer_VoidVoidFun ImGuiInit;
        UImGui_CGenericRenderer_VoidVoidFun ImGuiRenderData;

        UImGui_CGenericRenderer_VoidVoidFun waitOnGPU;
        UImGui_CGenericRenderer_VoidVoidFun destruct;

        UImGui_RendererAPITypeHint rendererAPI;

        void* context;
        size_t contextSize;

        // Do not touch
        UImGui_CGenericRenderer* instance;
    } UImGui_CGenericRenderer_InitInfo;

    UIMGUI_PUBLIC_API void UImGui_CGenericRenderer_init(UImGui_CGenericRenderer_InitInfo* initInfo);
    UIMGUI_PUBLIC_API void UImGui_CGenericRenderer_free(const UImGui_CGenericRenderer_InitInfo* instance);
#ifdef __cplusplus
}
#endif