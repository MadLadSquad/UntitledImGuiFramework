#pragma once
#include <C/CDefines.h>

#ifdef __cplusplus
extern "C"
{
#endif
    typedef enum UImGui_ClientSideBarFlags
    {
        UIMGUI_CLIENT_SIDE_BAR_FLAG_NONE = 0,
        UIMGUI_CLIENT_SIDE_BAR_FLAG_MINIMISE_BUTTON,
        UIMGUI_CLIENT_SIDE_BAR_FLAG_MAXIMISE_BUTTON,
        UIMGUI_CLIENT_SIDE_BAR_FLAG_CLOSE_BUTTON,
        UIMGUI_CLIENT_SIDE_BAR_FLAG_MOVEABLE,
        UIMGUI_CLIENT_SIDE_BAR_FLAG_ALL = UIMGUI_CLIENT_SIDE_BAR_FLAG_MINIMISE_BUTTON
                                        | UIMGUI_CLIENT_SIDE_BAR_FLAG_MAXIMISE_BUTTON
                                        | UIMGUI_CLIENT_SIDE_BAR_FLAG_CLOSE_BUTTON
                                        | UIMGUI_CLIENT_SIDE_BAR_FLAG_MOVEABLE
    } UImGui_ClientSideBarFlags;

    // Initialises the client-side bar
    // Event Safety - Post-begin
    UIMGUI_PUBLIC_API void UImGui_ClientSideBar_Begin();

    // Renders the bar. In C++, flags defaults to UIMGUI_CLIENT_SIDE_BAR_FLAG_ALL
    // Event Safety - Post-begin
    UIMGUI_PUBLIC_API void UImGui_ClientSideBar_End(float deltaTime, UImGui_ClientSideBarFlags flags) noexcept;
#ifdef __cplusplus
}
#endif