#import "MacOSWindowPlatform.h"
#import <Foundation/Foundation.h>
#import <Cocoa/Cocoa.h>

void UImGui::MacOSWindow::setShowWindowOnTaskbar(void* window, bool bShow)
{
    id w = (id)window;
}

void UImGui::MacOSWindow::setShowWindowInPager(void* window, bool bShow)
{
    id w = (id)window;
}

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