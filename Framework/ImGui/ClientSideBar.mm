#include <Core/Interfaces/WindowInterface.hpp>
#include "ClientSideBar.hpp"

#import <Foundation/Foundation.h>
#import <Cocoa/Cocoa.h>
#import <objc/runtime.h>

// Each button uses about 20 virtual pixels for itself and about 5 for outside padding on the X axis
#define MACOS_CLIENT_SIDE_BAR_PADDING_WIDTH 70.0f

static void disableOrEnableButton(float& width, NSButton* button, const UImGui_ClientSideBarFlags flags, const UImGui_ClientSideBarFlags flag)
{
    if (flags & flag)
        [button setHidden: NO];
    else
    {
        // We have 3 buttons, duh
        width -= MACOS_CLIENT_SIDE_BAR_PADDING_WIDTH / 3.0f;
        [button setHidden: YES];
    }
}

extern "C" float UImGui_Cocoa_setUpClientSideBarMacOS(const UImGui_ClientSideBarFlags flags)
{
    static bool bFirst = true;
    static float width = MACOS_CLIENT_SIDE_BAR_PADDING_WIDTH;
    if (bFirst)
    {
        auto* nswin = (NSWindow*)UImGui::Window::Platform::getNativeWindowHandle();

        nswin.titleVisibility = NSWindowTitleHidden;
        nswin.titlebarAppearsTransparent = YES;
        nswin.styleMask |= NSWindowStyleMaskFullSizeContentView;

        NSButton* closeButton = [nswin standardWindowButton:NSWindowCloseButton];
        NSButton* minimiseButton  = [nswin standardWindowButton:NSWindowMiniaturizeButton];
        NSButton* zoomButton  = [nswin standardWindowButton:NSWindowZoomButton];

        disableOrEnableButton(width, closeButton, flags, UIMGUI_CLIENT_SIDE_BAR_FLAG_CLOSE_BUTTON);
        disableOrEnableButton(width, minimiseButton, flags, UIMGUI_CLIENT_SIDE_BAR_FLAG_MINIMISE_BUTTON);
        disableOrEnableButton(width, zoomButton, flags, UIMGUI_CLIENT_SIDE_BAR_FLAG_MAXIMISE_BUTTON);

        // Since this is floating point math there is space for errors and we should never make separators with width
        // that is less than 1.0f
        width = width <= 1.0f ? 1.0f : width;

        bFirst = false;
    }
    return width;
}
