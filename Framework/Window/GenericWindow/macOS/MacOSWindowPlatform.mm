#include "MacOSWindowPlatform.h"
#import <Foundation/Foundation.h>
#import <Cocoa/Cocoa.h>

void UImGui::MacOSWindow::setWindowAlwaysBelow(void* window)
{
    id w = (id)window;
    [w setLevel:NSWindowBelow];
}

void UImGui::MacOSWindow::setWindowAlwaysAbove(void* window)
{
    id w = (id)window;
    [w makeKeyAndOrderFront:nil];
    [w setLevel:NSStatusWindowLevel];
}