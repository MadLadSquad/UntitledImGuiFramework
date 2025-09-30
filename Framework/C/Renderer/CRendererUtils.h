#pragma once
#include <C/CDefines.h>
#include <C/Window/RendererData.h>
#ifndef __EMSCRIPTEN__
    #include <vulkan/vulkan.h>
#endif

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
    typedef void UImGui_OpenGLContext;

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

    typedef void(*UImGui_OpenGLProc)();
    typedef UImGui_OpenGLProc(*UImGui_OpenGL_GetProcAddressFun)(const char*);

    // Call this inside the window hints interface function of the GenericRenderer class
    //
    // Use this for every graphics API, except for OpenGL. For OpenGL, you should use: UImGui_RendererUtils_setOpenGLHints
    // Event safety - startup, post-startup
    UIMGUI_PUBLIC_API void UImGui_RendererUtils_setupManually();

    // Renderer a new dear imgui frame
    // Event safety - tick
    UIMGUI_PUBLIC_API void UImGui_RendererUtils_beginImGuiFrame();

    // Initialise dear imgui for rendering with a renderer that is not OpenGL or Vulkan
    // CAUTION: For OpenGL or Vulkan, use the specialisations under their respective namespaces
    // Event safety - style, begin
    UIMGUI_PUBLIC_API void UImGui_RendererUtils_ImGuiInitOther();

    // Install window callbacks for dear imgui(only needed for some renderers, such as WebGPU or OpenGL)
    // Event safety - style, begin
    UIMGUI_PUBLIC_API void UImGui_RendererUtils_ImGuiInstallCallbacks();

    // Returns a pointer to the current renderer
    // Event safety - any-time
    UIMGUI_PUBLIC_API UImGui_CGenericRenderer* UImGui_RendererUtils_getRenderer();

    // Call this inside the window hints interface function of the GenericRenderer class
    //
    // Recommended args:
    // Emscripten/Web targets - UIMGUI_LATEST_OPENGL_VERSION, UIMGUI_RENDERER_CLIENT_API_OPENGL_ES, UIMGUI_OPENGL_PROFILE_ANY, false
    // Desktop - UIMGUI_LATEST_OPENGL_VERSION, UIMGUI_RENDERER_CLIENT_API_OPENGL, UIMGUI_OPENGL_PROFILE_CORE, true
    //
    // Event safety - startup, post-startup
    UIMGUI_PUBLIC_API void UImGui_RendererUtils_OpenGL_setHints(int majorVersion, int minorVersion, UImGui_RendererClientAPI clientApi, UImGui_OpenGLProfile profile, bool bForwardCompatible, uint32_t samples);

    // Swaps buffers for OpenGL.
    // Event safety - post-begin
    UIMGUI_PUBLIC_API void UImGui_RendererUtils_OpenGL_swapFramebuffers();

    // Create an OpenGL context(call this in post-window creation)
    // Event safety - startup, post-startup
    UIMGUI_PUBLIC_API UImGui_OpenGLContext* UImGui_RendererUtils_OpenGL_createContext();

    // Set current OpenGL context(call this in post-window creation)
    // Event safety - startup, post-startup
    UIMGUI_PUBLIC_API void UImGui_RendererUtils_OpenGL_setCurrentContext(UImGui_OpenGLContext* ctx);

    // Destroy the current OpenGL context
    // Event safety - post-startup
    UIMGUI_PUBLIC_API void UImGui_RendererUtils_OpenGL_destroyContext(UImGui_OpenGLContext* ctx);

    // Get the current OpenGL context
    // Event safety - startup, post-startup
    UIMGUI_PUBLIC_API UImGui_OpenGLContext* UImGui_RendererUtils_OpenGL_getCurrentContext();

    // Set the swap interval for the OpenGL renderer
    // Event safety - startup, post-startup
    UIMGUI_PUBLIC_API void UImGui_RendererUtils_OpenGL_setSwapInterval(int interval);

    // Returns the function for getting the OpenGL proc address
    // Event safety - startup, post-startup
    UIMGUI_PUBLIC_API UImGui_OpenGL_GetProcAddressFun UImGui_RendererUtils_OpenGL_getProcAddressFunction();

    // Check for WebGPU support
    // Event safety - any time
    UIMGUI_PUBLIC_API bool UImGui_RendererUtils_WebGPU_supported();


    #ifndef __EMSCRIPTEN__
        // Initialise dear imgui for rendering with Vulkan
        // Event safety - style, begin
        UIMGUI_PUBLIC_API void UImGui_RendererUtils_Vulkan_ImGuiInit();

        // Event safety - post-startup
        UIMGUI_PUBLIC_API VkResult UImGui_RendererUtils_Vulkan_createWindowSurface(VkInstance instance, const VkAllocationCallbacks* allocator, VkSurfaceKHR* surface);

        // The arrays need to be freed with UImGui_Allocator_free after use
        // Event safety - post-startup
        UIMGUI_PUBLIC_API void UImGui_RendererUtils_Vulkan_fillInstanceAndLayerExtensions(const char*** instanceExtensions, size_t* instanceExtensionsSize, const char*** instanceLayers, size_t* instanceLayersSize);
    #endif
#ifdef __cplusplus
}
#endif
