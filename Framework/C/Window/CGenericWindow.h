#pragma once
#include <C/Window/CMonitor.h>
#include <C/Renderer/CRendererUtils.h>
#include <C/Interfaces/CInput.h>
#ifndef __EMSCRIPTEN__
    #include <vulkan/vulkan.h>
#endif

#ifdef __cplusplus
extern "C"
{
#endif

    typedef void UImGui_CGenericWindow;
    struct UImGui_CGenericWindowInitInfo;

    // Note: all push*Callback functions take a void* instead of a function pointer. This is because arguments are
    // passed from C++ as std::function<...>* and therefore they need to be cast back into their underlying C++ type.
    // Therefore, all implementations of this function have to be implemented from C++, which is not ideal, since it
    // overcomplicates interfacing from non C/C++ languages.
    typedef struct UIMGUI_PUBLIC_API UImGui_CGenericWindowInitInfo
    {
        void(*createWindow)(struct UImGui_CGenericWindowInitInfo*);
        void(*destroyWindow)(struct UImGui_CGenericWindowInitInfo*);

#ifndef __EMSCRIPTEN__
        void(*ImGuiInitFor_Vulkan)(struct UImGui_CGenericWindowInitInfo*);
#endif
        void(*ImGuiInitFor_OpenGL)(struct UImGui_CGenericWindowInitInfo*);
        void(*ImGuiInitFor_Other)(struct UImGui_CGenericWindowInitInfo*);

        void(*ImGuiInstallCallbacks)(struct UImGui_CGenericWindowInitInfo*);
        void(*ImGuiNewFrame)(struct UImGui_CGenericWindowInitInfo*);
        void(*ImGuiShutdown)(struct UImGui_CGenericWindowInitInfo*);

        bool(*shouldRender)(struct UImGui_CGenericWindowInitInfo*);
        void(*pollEvents)(struct UImGui_CGenericWindowInitInfo*, double*, double*, double*);
        void(*waitEventsTimeout)(struct UImGui_CGenericWindowInitInfo*, double);
        void(*waitEvents)(struct UImGui_CGenericWindowInitInfo*);

        UImGui_OpenGLContext*(*OpenGL_createContext)(struct UImGui_CGenericWindowInitInfo*);
        UImGui_OpenGLContext*(*OpenGL_getCurrentContext)(struct UImGui_CGenericWindowInitInfo*);
        void(*OpenGL_setCurrentContext)(struct UImGui_CGenericWindowInitInfo*, UImGui_OpenGLContext*);
        void(*OpenGL_destroyContext)(struct UImGui_CGenericWindowInitInfo*, UImGui_OpenGLContext*);

        void(*OpenGL_swapBuffers)(struct UImGui_CGenericWindowInitInfo*);
        void(*OpenGL_setSwapInterval)(struct UImGui_CGenericWindowInitInfo*, int);
        void(*OpenGL_setHints)(struct UImGui_CGenericWindowInitInfo*, int, int, UImGui_RendererClientAPI, UImGui_OpenGLProfile, bool, uint32_t);
        UImGui_OpenGL_GetProcAddressFun(*OpenGL_getProcAddressFunction)(struct UImGui_CGenericWindowInitInfo*);

        void(*setupManualRenderingHints)(struct UImGui_CGenericWindowInitInfo*);

#ifndef __EMSCRIPTEN__
        VkResult(*Vulkan_createWindowSurface)(struct UImGui_CGenericWindowInitInfo*, VkInstance, const VkAllocationCallbacks*, VkSurfaceKHR*);
        void(*Vulkan_fillInstanceAndLayerExtensions)(struct UImGui_CGenericWindowInitInfo*, const char**, size_t, const char**, size_t);
#endif

        CKeyState(*getKey)(struct UImGui_CGenericWindowInitInfo*, CKeys);

        UImGui_FVector2(*getMousePositionChange)(struct UImGui_CGenericWindowInitInfo*);
        UImGui_FVector2(*getCurrentMousePosition)(struct UImGui_CGenericWindowInitInfo*);
        UImGui_FVector2(*getLastMousePosition)(struct UImGui_CGenericWindowInitInfo*);

        UImGui_FVector2(*getScroll)(struct UImGui_CGenericWindowInitInfo*);

        void(*setCursorVisibility)(struct UImGui_CGenericWindowInitInfo*, UImGui_CursorVisibilityState);

        void(*setRawMouseMotion)(struct UImGui_CGenericWindowInitInfo*, bool);
        bool(*getRawMouseMotion)(struct UImGui_CGenericWindowInitInfo*);

        void(*setTitle)(struct UImGui_CGenericWindowInitInfo*, UImGui_String);
        UImGui_String(*getTitle)(struct UImGui_CGenericWindowInitInfo*);
        void(*setTitleSetting)(struct UImGui_CGenericWindowInitInfo*, UImGui_String);
        UImGui_String(*getTitleSetting)(struct UImGui_CGenericWindowInitInfo*);

        void(*setIcon)(struct UImGui_CGenericWindowInitInfo*, UImGui_String);
        UImGui_String(*getIconLocation)(struct UImGui_CGenericWindowInitInfo*);
        void(*setIconLocationSetting)(struct UImGui_CGenericWindowInitInfo*, UImGui_String);
        UImGui_String(*getIconLocationSetting)(struct UImGui_CGenericWindowInitInfo*);

        float(*getAspectRatio)(struct UImGui_CGenericWindowInitInfo*);

        UImGui_FVector2(*getCurrentWindowPosition)(struct UImGui_CGenericWindowInitInfo*);
        UImGui_FVector2(*getLastWindowPosition)(struct UImGui_CGenericWindowInitInfo*);
        UImGui_FVector2(*getWindowPositionChange)(struct UImGui_CGenericWindowInitInfo*);

        void(*setCurrentWindowPosition)(struct UImGui_CGenericWindowInitInfo*, UImGui_FVector2);
        void(*pushWindowPositionChangeCallback)(struct UImGui_CGenericWindowInitInfo*, const void*);

        UImGui_FVector2(*getWindowSize)(struct UImGui_CGenericWindowInitInfo*);
        UImGui_FVector2*(*getWindowSizeSetting)(struct UImGui_CGenericWindowInitInfo*);

        bool(*getWindowFullscreen)(struct UImGui_CGenericWindowInitInfo*);
        bool*(*getWindowFullscreenSetting)(struct UImGui_CGenericWindowInitInfo*);
        void(*setWindowFullscreen)(struct UImGui_CGenericWindowInitInfo*, bool);

        void(*saveSettings)(struct UImGui_CGenericWindowInitInfo*, bool);
        void(*openConfig)(struct UImGui_CGenericWindowInitInfo*);
        void(*refreshSettings)(struct UImGui_CGenericWindowInitInfo*);

        void(*close)(struct UImGui_CGenericWindowInitInfo*);
        void(*pushWindowCloseCallback)(struct UImGui_CGenericWindowInitInfo*, const void*);

        void(*Platform_setWindowAlwaysOnTop)(struct UImGui_CGenericWindowInitInfo*);
        void(*Platform_setWindowAlwaysOnBotton)(struct UImGui_CGenericWindowInitInfo*);

        void(*Platform_setWindowShowingOnPager)(struct UImGui_CGenericWindowInitInfo*, bool);
        bool(*Platform_getWindowShowingOnPager)(struct UImGui_CGenericWindowInitInfo*);

        void(*Platform_setWindowShowingOnTaskbar)(struct UImGui_CGenericWindowInitInfo*, bool);
        bool(*Platform_getWindowShowingOnTaskbar)(struct UImGui_CGenericWindowInitInfo*);

        void(*Platform_setWindowType)(struct UImGui_CGenericWindowInitInfo*, UImGui_String);
        size_t(*Platform_getWindowID)(struct UImGui_CGenericWindowInitInfo*);

        void(*setWindowSizeInScreenCoords)(struct UImGui_CGenericWindowInitInfo*, UImGui_FVector2);
        UImGui_FVector2(*getWindowSizeInScreenCoords)(struct UImGui_CGenericWindowInitInfo*);
        void(*pushWindowResizedInScreenCoordsCallback)(struct UImGui_CGenericWindowInitInfo*, const void*);

        void(*setWindowResizeable)(struct UImGui_CGenericWindowInitInfo*, bool);
        bool*(*getWindowResizeableSetting)(struct UImGui_CGenericWindowInitInfo*);
        bool(*getWindowCurrentlyResizeable)(struct UImGui_CGenericWindowInitInfo*);
        void(*pushWindowResizeCallback)(struct UImGui_CGenericWindowInitInfo*, const void*);

        void(*requestWindowAttention)(struct UImGui_CGenericWindowInitInfo*);

        void(*hideWindow)(struct UImGui_CGenericWindowInitInfo*);
        void(*showWindow)(struct UImGui_CGenericWindowInitInfo*);
        bool*(*getWindowHiddenSetting)(struct UImGui_CGenericWindowInitInfo*);
        bool(*getWindowCurrentlyHidden)(struct UImGui_CGenericWindowInitInfo*);

        bool*(*windowSurfaceTransparentSetting)(struct UImGui_CGenericWindowInitInfo*);

        void(*focusWindow)(struct UImGui_CGenericWindowInitInfo*);
        bool*(*getWindowFocusSetting)(struct UImGui_CGenericWindowInitInfo*);
        bool(*getWindowCurrentlyFocused)(struct UImGui_CGenericWindowInitInfo*);
        void(*pushWindowFocusCallback)(struct UImGui_CGenericWindowInitInfo*, const void*);

        void(*iconifyWindow)(struct UImGui_CGenericWindowInitInfo*);
        void(*restoreWindowState)(struct UImGui_CGenericWindowInitInfo*);
        void(*pushWindowIconifyCallback)(struct UImGui_CGenericWindowInitInfo*, const void*);
        bool(*getWindowIconified)(struct UImGui_CGenericWindowInitInfo*);

        UImGui_FVector2(*getWindowContentScale)(struct UImGui_CGenericWindowInitInfo*);
        void(*pushWindowContentScaleCallback)(struct UImGui_CGenericWindowInitInfo*, const void*);

        void(*setSizeLimits)(struct UImGui_CGenericWindowInitInfo*, UImGui_FVector2, UImGui_FVector2);
        void(*setSizeLimitByAspectRatio)(struct UImGui_CGenericWindowInitInfo*, UImGui_FVector2);
        UImGui_FVector4*(*getSizeLimits)(struct UImGui_CGenericWindowInitInfo*);
        UImGui_FVector2*(*getAspectRatioSizeLimits)(struct UImGui_CGenericWindowInitInfo*);

        UImGui_FVector4(*getWindowDecorationFrameDistances)(struct UImGui_CGenericWindowInitInfo*);
        bool(*getCurrentWindowDecoratedState)(struct UImGui_CGenericWindowInitInfo*);
        bool*(*getWindowDecoratedSetting)(struct UImGui_CGenericWindowInitInfo*);
        void(*setWindowDecorated)(struct UImGui_CGenericWindowInitInfo*, bool);

        void(*pushWindowRefreshCallback)(struct UImGui_CGenericWindowInitInfo*, const void*);

        void(*maximiseWindow)(struct UImGui_CGenericWindowInitInfo*);
        bool*(*getWindowMaximizedSetting)(struct UImGui_CGenericWindowInitInfo*);
        void(*pushWindowMaximiseCallback)(struct UImGui_CGenericWindowInitInfo*, const void*);
        bool(*getWindowCurrentlyMaximised)(struct UImGui_CGenericWindowInitInfo*);

        UImGui_MonitorData(*getWindowMonitor)(struct UImGui_CGenericWindowInitInfo*);
        UImGui_MonitorData(*getPrimaryMonitor)(struct UImGui_CGenericWindowInitInfo*);
        UImGui_MonitorData*(*getMonitors)(struct UImGui_CGenericWindowInitInfo*, size_t*);

        void(*pushWindowOSDragDropCallback)(struct UImGui_CGenericWindowInitInfo*, const void*);

        void*(*getInternal)(struct UImGui_CGenericWindowInitInfo*);
        UImGui_CGenericWindow*(*get)(struct UImGui_CGenericWindowInitInfo*);

        void* context;
        size_t contextSize;

        UImGui_CGenericMonitor* monitor;
        UImGui_CGenericWindow* instance;
    } UImGui_CGenericWindowInitInfo;

    /**
     * @brief Creates a GenericWindow instance. Memory management over the InitInfo struct falls on the user
     * @param initInfo - A struct containing function pointers for each GenericWindow event. push*Callback functions
     * get a void* which points to the corresponding C++ std::function instance. Casts need to be done across FFI
     * boundaries which is not ideal. Memory management over the InitInfo struct falls on the user
     * @note Event Safety - Any time
     */
    UIMGUI_PUBLIC_API void UImGui_CGenericWindow_create(struct UImGui_CGenericWindowInitInfo* initInfo);

    /**
     * @brief Frees the GenericWindow instance part of the InitInfo struct. Memory management over the InitInfo struct
     * falls on the user.
     * @param instance - The InitInfo struct used to create the GenericWindow struct. The instance is stored as part of
     * this struct, but only it will be freed. Ownership over the InitInfo struct instance is placed upon the user.
     * @note Event Safety - Any time
     */
    UIMGUI_PUBLIC_API void UImGui_CGenericWindow_destroy(const struct UImGui_CGenericWindowInitInfo* instance);
#ifdef __cplusplus
}
#endif