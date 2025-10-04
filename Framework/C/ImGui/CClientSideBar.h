#pragma once
#include <C/CDefines.h>
#include <C/CTypes.h>

#ifdef __cplusplus
extern "C"
{
#endif
    typedef enum UImGui_ClientSideBarFlags
    {
        UIMGUI_CLIENT_SIDE_BAR_FLAG_NONE                = 0,
        UIMGUI_CLIENT_SIDE_BAR_FLAG_MINIMISE_BUTTON     = 1 << 0,
        UIMGUI_CLIENT_SIDE_BAR_FLAG_MAXIMISE_BUTTON     = 1 << 1,
        UIMGUI_CLIENT_SIDE_BAR_FLAG_CLOSE_BUTTON        = 1 << 2,
        UIMGUI_CLIENT_SIDE_BAR_FLAG_MOVEABLE            = 1 << 3, // Ignored on macOS
        UIMGUI_CLIENT_SIDE_BAR_FLAG_ALL                 = UIMGUI_CLIENT_SIDE_BAR_FLAG_MINIMISE_BUTTON
                                                        | UIMGUI_CLIENT_SIDE_BAR_FLAG_MAXIMISE_BUTTON
                                                        | UIMGUI_CLIENT_SIDE_BAR_FLAG_CLOSE_BUTTON
                                                        | UIMGUI_CLIENT_SIDE_BAR_FLAG_MOVEABLE
    } UImGui_ClientSideBarFlags;

    
    // Set the client-side bar's flags. Note that we already default to UIMGUI_CLIENT_SIDE_BAR_FLAG_ALL so for most
    // cases calling this function will not be necessary
    // Event Safety - Any time
    UIMGUI_PUBLIC_API void UImGui_ClientSideBar_SetFlags(UImGui_ClientSideBarFlags flags);

    // Starts rendering the automatic main client-side bar. For more control consider using the *Manual* functions
    // Event Safety - Tick
    UIMGUI_PUBLIC_API bool UImGui_ClientSideBar_Begin();

    // Finishes rendering the automatic main client-side bar. For more control consider using the *Manual* functions
    // The function needs to be called with the result of the previous call for it to terminate successfully
    // Default arguments: bRendered, { 1.0, 0.482, 0.388f, 1.0f }, { 0.753f, 0.110f, 0.157f, 1.0f }
    // Event Safety - Tick
    UIMGUI_PUBLIC_API void UImGui_ClientSideBar_End(bool bRendered, UImGui_FVector4 destructiveColour, UImGui_FVector4 destructiveColourActive);

    // Sets up the style for the bar before starting to render it.
    // Event Safety - Tick
    UIMGUI_PUBLIC_API void UImGui_ClientSideBar_BeginManualStyle();

    // Pops the style for the bar after rendering.
    // Event Safety - Tick
    UIMGUI_PUBLIC_API void UImGui_ClientSideBar_EndManualStyle();

    // Starts rendering the client-side bar. Make sure to call BeginManualStyle before it.
    // Event Safety - Tick
    UIMGUI_PUBLIC_API void UImGui_ClientSideBar_BeginManualRender();

    // Finishes rendering the bar and commits the result. Make sure to call EndManualStyle after it.
    // Default arguments: { 1.0, 0.482, 0.388f, 1.0f }, { 0.753f, 0.110f, 0.157f, 1.0f }
    // Event Safety - Tick
    UIMGUI_PUBLIC_API void UImGui_ClientSideBar_EndManualRender(UImGui_FVector4 destructiveColour, UImGui_FVector4 destructiveColourActive);
#ifdef __cplusplus
}
#endif