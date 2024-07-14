#pragma once

#ifdef __cplusplus
extern "C"
{
#else
    #include <stdbool.h>
#endif
// Dll macro magic
#ifdef _WIN32
    #ifdef UIMGUI_COMPILE_LIB
        #define UIMGUI_PUBLIC_API __declspec(dllexport)
    #else
        #define UIMGUI_PUBLIC_API __declspec(dllimport)
    #endif
#else
    #define UIMGUI_PUBLIC_API
#endif

#define IMGUI_API UIMGUI_PUBLIC_API

#define X11_WINDOW_TYPE_DESKTOP "_NET_WM_WINDOW_TYPE_DESKTOP"
#define X11_WINDOW_TYPE_DOCK "_NET_WM_WINDOW_TYPE_DOCK"
#define X11_WINDOW_TYPE_TOOLBAR "_NET_WM_WINDOW_TYPE_TOOLBAR"
#define X11_WINDOW_TYPE_MENU "_NET_WM_WINDOW_TYPE_MENU"
#define X11_WINDOW_TYPE_UTILITY "_NET_WM_WINDOW_TYPE_UTILITY"
#define X11_WINDOW_TYPE_SPLASH "_NET_WM_WINDOW_TYPE_SPLASH"
#define X11_WINDOW_TYPE_DIALOG "_NET_WM_WINDOW_TYPE_DIALOG"
#define X11_WINDOW_TYPE_DROPDOWN_MENU "_NET_WM_WINDOW_TYPE_DROPDOWN_MENU"
#define X11_WINDOW_TYPE_POPUP_MENU "_NET_WM_WINDOW_TYPE_POPUP_MENU"
#define X11_WINDOW_TYPE_TOOLTIP "_NET_WM_WINDOW_TYPE_TOOLTIP"
#define X11_WINDOW_TYPE_NOTIFICATION "_NET_WM_WINDOW_TYPE_NOTIFICATION"
#define X11_WINDOW_TYPE_COMBO "_NET_WM_WINDOW_TYPE_COMBO"
#define X11_WINDOW_TYPE_DND "_NET_WM_WINDOW_TYPE_DND"
#define X11_WINDOW_TYPE_NORMAL "_NET_WM_WINDOW_TYPE_NORMAL"

#define UNUSED(x) (void)(x);
#define CARRAY_SIZE(x) ((int)(sizeof(x) / sizeof(*(x))))

/**
 * @brief The ComponentState enum defines 3 fields that represent the event state of the given component, the given
 * component can then check its own state(if in PAUSED or RUNNING state) and call specific components of its event
 * functions. The OFF state is there to make it easy to fully shut down a component until the program closes
 */
typedef enum UImGui_ComponentState
{
    // The component is not running but its events are still running
    UIMGUI_COMPONENT_STATE_PAUSED,
    // The component is running
    UIMGUI_COMPONENT_STATE_RUNNING,
    // The component is not running and its events are not running, only the constructor and destructor are called
    UIMGUI_COMPONENT_STATE_OFF,
} UImGui_ComponentState;

/**
 * @brief An enum that defines component types to be used by various functions
 * @var UIMGUI_COMPONENT_TYPE_INLINE - Defines an inline component
 * @var UIMGUI_COMPONENT_TYPE_TITLEBAR - Defines a titlebar component
 * @var UIMGUI_COMPONENT_PYE_WINDOW - Defines a window component
 */
typedef enum [[maybe_unused]] UImGui_ComponentType
{
    UIMGUI_COMPONENT_TYPE_INLINE,
    UIMGUI_COMPONENT_TYPE_TITLEBAR,
    UIMGUI_COMPONENT_TYPE_WINDOW
} UImGui_ComponentType;

#ifdef __cplusplus
};
#endif