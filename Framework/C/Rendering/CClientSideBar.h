#pragma once
#include <C/CDefines.h>
#include <C/CTypes.h>

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

    // Renders the bar. In C++, flags defaults to UIMGUI_CLIENT_SIDE_BAR_FLAG_ALL, { 1.0, 0.482, 0.388f, 1.0f }, { 0.753f, 0.110f, 0.157f, 1.0f }
    // Event Safety - Post-begin
    UIMGUI_PUBLIC_API void UImGui_ClientSideBar_End(UImGui_ClientSideBarFlags flags, UImGui_FVector4 destructiveColour, UImGui_FVector4 destructiveColourActive);
#ifdef __cplusplus
}
#endif