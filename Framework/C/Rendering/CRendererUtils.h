#pragma once
#include <C/CDefines.h>

#ifdef __cplusplus
extern "C"
{
#endif

#define UIMGUI_EMSCRIPTEN_LATEST_OPENGL_VERSION 2, 0
#define UIMGUI_EMSCRIPTEN_LATEST_GLSL_VERSION "#version 100"

#define UIMGUI_APPLE_LATEST_OPENGL_VERSION 4, 1
#define UIMGUI_APPLE_LATEST_GLSL_VERSION "#version 410"

#define UIMGUI_ANY_LATEST_OPENGL_VERSION 4, 5
#define UIMGUI_ANY_LATEST_GLSL_VERSION "#version 450"

#ifdef __EMSCRIPTEN__
    #define UIMGUI_LATEST_OPENGL_VERSION UIMGUI_EMSCRIPTEN_LATEST_OPENGL_VERSION
    #define UIMGUI_LATEST_GLSL_VERSION UIMGUI_EMSCRIPTEN_LATEST_GLSL_VERSION
#else
    #ifdef __APPLE__
        #define UIMGUI_LATEST_OPENGL_VERSION UIMGUI_APPLE_LATEST_OPENGL_VERSION
        #define UIMGUI_LATEST_GLSL_VERSION UIMGUI_APPLE_LATEST_GLSL_VERSION
    #else
        #define UIMGUI_LATEST_OPENGL_VERSION UIMGUI_ANY_LATEST_OPENGL_VERSION
        #define UIMGUI_LATEST_GLSL_VERSION UIMGUI_ANY_LATEST_GLSL_VERSION
    #endif
#endif

    struct GLFWwindow;

    typedef enum UImGui_RendererClientAPI
    {
        UIMGUI_RENDERER_CLIENT_API_MANUAL = 0,
        UIMGUI_RENDERER_CLIENT_API_OPENGL = 0x00030001,
        UIMGUI_RENDERER_CLIENT_API_OPENGL_ES = 0x00030002
    } UImGui_RendererClientAPI;

    typedef enum UImGui_OpenGLProfile
    {
        UIMGUI_OPENGL_PROFILE_ANY = 0,
        UIMGUI_OPENGL_PROFILE_CORE = 0x00032001,
        UIMGUI_OPENGL_PROFILE_COMPAT = 0x00032002,
    } UImGui_OpenGLProfile;

    // Call this inside the window hints interface function of the GenericRenderer class
    //
    // Use this for every graphics API, except for OpenGL. For OpenGL you should use: UImGui_RendererUtils_setOpenGLHints
    // Event safety - startup, post-startup
    UIMGUI_PUBLIC_API void UImGui_RendererUtils_setupManually();

    // Call this inside the window hints interface function of the GenericRenderer class
    //
    // Recommended args:
    // Emscripten/Web targets - UIMGUI_LATEST_OPENGL_VERSION, UIMGUI_RENDERER_CLIENT_API_OPENGL_ES, UIMGUI_OPENGL_PROFILE_ANY, false
    // Desktop - UIMGUI_LATEST_OPENGL_VERSION, UIMGUI_RENDERER_CLIENT_API_OPENGL, UIMGUI_OPENGL_PROFILE_CORE, true
    //
    // Event safety - startup, post-startup
    UIMGUI_PUBLIC_API void UImGui_RendererUtils_OpenGL_setHints(int majorVersion, int minorVersion, UImGui_RendererClientAPI clientApi, UImGui_OpenGLProfile profile, bool bForwardCompatible);

    // Swaps buffers for OpenGL.
    // Event safety - post-begin
    UIMGUI_PUBLIC_API void UImGui_RendererUtils_OpenGL_swapFramebuffer();

    // Check for WebGPU support
    // Event safety - any time
    UIMGUI_PUBLIC_API bool UImGui_RendererUtils_WebGPU_supported();
#ifdef __cplusplus
}
#endif