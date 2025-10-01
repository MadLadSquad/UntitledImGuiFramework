#include "WindowGLFW.hpp"
#ifdef _WIN32
    #define GLFW_EXPOSE_NATIVE_WIN32
#elif __APPLE__
    #define GLFW_EXPOSE_NATIVE_COCOA
#elif !__EMSCRIPTEN__
    #if __has_include(<wayland-client.h>)
        #define GLFW_EXPOSE_NATIVE_WAYLAND
    #endif
    #if __has_include(<X11/Xatom.h>)
        #define GLFW_EXPOSE_NATIVE_X11
        #include <X11/Xatom.h>
        #define _NET_WM_STATE_ADD 1
    #endif
#endif

#ifdef __APPLE__
    #include <OpenGL/GL.h>
    #include "../GenericWindow/macOS/MacOSWindowPlatform.h"
#else
    #include <glad/include/glad/gl.h>
#endif
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

#include <cstring>

void UImGui::WindowGLFW::Platform_setWindowAlwaysOnTop() noexcept
{
#ifdef GLFW_EXPOSE_NATIVE_X11
    if (glfwGetPlatform() == GLFW_PLATFORM_X11)
    {
        Display* display = glfwGetX11Display();
        const ::Window root = DefaultRootWindow(display);
        const ::Window win = glfwGetX11Window(window);

        const Atom wmStateAbove = XInternAtom(display, "_NET_WM_STATE_ABOVE", 1);
        if (wmStateAbove == None)
            Logger::log("Cannot find atom for _NET_WM_STATE_ABOVE!", ULOG_LOG_TYPE_ERROR);

        const Atom wmNetWmState = XInternAtom(display, "_NET_WM_STATE", 1);
        if (wmNetWmState == None)
            Logger::log("Cannot find atom for _NET_WM_STATE!", ULOG_LOG_TYPE_ERROR);

        if (wmStateAbove != None)
        {
            XClientMessageEvent xclient = {};

            xclient.type = ClientMessage;
            xclient.window = win;
            xclient.message_type = wmNetWmState;
            xclient.format = 32;
            xclient.data.l[0] = 1;
            xclient.data.l[1] = static_cast<long>(wmStateAbove);
            xclient.data.l[2] = 0;
            xclient.data.l[3] = 0;
            xclient.data.l[4] = 0;
            XSendEvent(display, root, false, SubstructureRedirectMask | SubstructureNotifyMask, reinterpret_cast<XEvent*>(&xclient));
            XFlush(display);
        }
        return;
    }
#endif
#ifdef GLFW_EXPOSE_NATIVE_WAYLAND
    if (glfwGetPlatform() == GLFW_PLATFORM_WAYLAND)
    {
        // TODO: Implement for 2.0
    }
#endif
#ifdef GLFW_EXPOSE_NATIVE_WIN32
    auto win = glfwGetWin32Window(window);
    SetWindowPos(win, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
#elif defined(GLFW_EXPOSE_NATIVE_COCOA)
    MacOSWindow::setWindowAlwaysAbove(glfwGetCocoaWindow(window));
#endif
}

void UImGui::WindowGLFW::Platform_setWindowAlwaysOnBottom() noexcept
{
#ifdef GLFW_EXPOSE_NATIVE_X11
    if (glfwGetPlatform() == GLFW_PLATFORM_X11)
    {
        Display* display = glfwGetX11Display();
        const ::Window win = glfwGetX11Window(window);
        const ::Window root = DefaultRootWindow(display);

        const Atom wmNetWmState = XInternAtom(display, "_NET_WM_STATE", 1);
        if (wmNetWmState == None)
        {
            Logger::log("Couldn't find the \"_NET_WM_STATE\" Atom!", ULOG_LOG_TYPE_ERROR);
            return;
        }

        const auto wmStateSticky = XInternAtom(display, "_NET_WM_STATE_STICKY", 1);
        if (wmStateSticky == None)
        {
            Logger::log("Couldn't find the \"_NET_WM_STATE_STICKY\" Atom!", ULOG_LOG_TYPE_ERROR);
            return;
        }

        const Atom wmStateBelow = XInternAtom(display, "_NET_WM_STATE_BELOW", 1);
        if (wmStateBelow == None)
        {
            Logger::log("Couldn't find the \"_NET_WM_STATE_BELOW\" Atom!", ULOG_LOG_TYPE_ERROR);
            return;
        }

        XClientMessageEvent xclient = {};

        xclient.type = ClientMessage;
        xclient.window = win;
        xclient.message_type = wmNetWmState;
        xclient.format = 32;
        xclient.data.l[0] = _NET_WM_STATE_ADD;
        xclient.data.l[1] = static_cast<long>(wmStateBelow);

        XSendEvent(display, root, False, SubstructureRedirectMask | SubstructureNotifyMask, reinterpret_cast<XEvent*>(&xclient));

        xclient.type = ClientMessage;
        xclient.window = win;
        xclient.message_type = wmNetWmState;
        xclient.format = 32;
        xclient.data.l[0] = _NET_WM_STATE_ADD;
        xclient.data.l[1] = static_cast<long>(wmStateSticky);

        XSendEvent(display, root, False, SubstructureRedirectMask | SubstructureNotifyMask, reinterpret_cast<XEvent*>(&xclient));
        XFlush(display);
        return;
    }
#endif
#ifdef GLFW_EXPOSE_NATIVE_WAYLAND
    if (glfwGetPlatform() == GLFW_PLATFORM_WAYLAND)
    {
        // TODO: Implement for 2.0
    }
#endif
#ifdef GLFW_EXPOSE_NATIVE_WIN32
    auto win = glfwGetWin32Window(window);
    SetWindowPos(win, HWND_BOTTOM, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
    //DefWindowProcA(win, WM_WINDOWPOSCHANGING, 0, 0);
#elif defined(GLFW_EXPOSE_NATIVE_COCOA)
    MacOSWindow::setWindowAlwaysBelow(glfwGetCocoaWindow(window));
#endif
}

void UImGui::WindowGLFW::Platform_setWindowShowingOnPager(const bool bShowInPager) noexcept
{
    this->bShowOnPager = bShowInPager;
#ifdef GLFW_EXPOSE_NATIVE_X11
    if (glfwGetPlatform() == GLFW_PLATFORM_X11 && !bShowOnPager)
    {
        Display* display = glfwGetX11Display();
        const ::Window win = glfwGetX11Window(window);
        const ::Window root = DefaultRootWindow(display);

        const Atom wmNetWmState = XInternAtom(display, "_NET_WM_STATE", 1);
        if (wmNetWmState == None)
        {
            Logger::log("Couldn't find the \"_NET_WM_STATE\" Atom!", ULOG_LOG_TYPE_ERROR);
            return;
        }

        const Atom wmStateSkipPager = XInternAtom(display, "_NET_WM_STATE_SKIP_PAGER", 1);
        if (wmStateSkipPager == None)
        {
            Logger::log("Couldn't find the \"_NET_WM_STATE_SKIP_PAGER\" Atom!", ULOG_LOG_TYPE_ERROR);
            return;
        }
        XClientMessageEvent xclient = {};

        xclient.type = ClientMessage;
        xclient.window = win;
        xclient.message_type = wmNetWmState;
        xclient.format = 32;
        xclient.data.l[0] = _NET_WM_STATE_ADD;
        xclient.data.l[1] = static_cast<long>(wmStateSkipPager);

        XSendEvent(display, root, False, SubstructureRedirectMask | SubstructureNotifyMask, reinterpret_cast<XEvent*>(&xclient));
        XFlush(display);
        return;
    }
#endif
#ifdef GLFW_EXPOSE_NATIVE_WIN32
    if (!bShowOnPager)
    {
        auto win = glfwGetWin32Window(window);
        LONG_PTR style = GetWindowLongPtr(win, GWL_EXSTYLE);
        SetWindowLongPtr(win, GWL_EXSTYLE, (style & ~WS_EX_APPWINDOW) | WS_EX_TOOLWINDOW);
    }
    else
    {
        auto win = glfwGetWin32Window(window);
        LONG_PTR style = GetWindowLongPtr(win, GWL_EXSTYLE);
        SetWindowLongPtr(win, GWL_EXSTYLE, (style & WS_EX_APPWINDOW) | ~WS_EX_TOOLWINDOW);
    }
#endif
}

bool UImGui::WindowGLFW::Platform_getWindowShowingOnPager() noexcept
{
    return bShowOnPager;
}

void UImGui::WindowGLFW::Platform_setWindowShowingOnTaskbar(const bool bShowOnTaskbar) noexcept
{
    this->bShowOnTaskbar = bShowOnTaskbar;
#ifdef GLFW_EXPOSE_NATIVE_X11
    if (glfwGetPlatform() == GLFW_PLATFORM_X11 && !bShowOnTaskbar)
    {
        Display* display = glfwGetX11Display();
        const ::Window win = glfwGetX11Window(window);
        const ::Window root = DefaultRootWindow(display);

        const Atom wmNetWmState = XInternAtom(display, "_NET_WM_STATE", 1);
        if (wmNetWmState == None)
        {
            Logger::log("Couldn't find the \"_NET_WM_STATE\" Atom!", ULOG_LOG_TYPE_ERROR);
            return;
        }

        const Atom wmStateSkipTaskbar = XInternAtom(display, "_NET_WM_STATE_SKIP_TASKBAR", 1);
        if (wmStateSkipTaskbar == None)
        {
            Logger::log("Couldn't find the \"NET_WM_STATE_SKIP_TASKBAR\" Atom!", ULOG_LOG_TYPE_ERROR);
            return;
        }

        XClientMessageEvent xclient = {};

        xclient.type = ClientMessage;
        xclient.window = win;
        xclient.message_type = wmNetWmState;
        xclient.format = 32;
        xclient.data.l[0] = _NET_WM_STATE_ADD;
        xclient.data.l[1] = static_cast<long>(wmStateSkipTaskbar);

        XSendEvent(display, root, False, SubstructureRedirectMask | SubstructureNotifyMask, reinterpret_cast<XEvent*>(&xclient));
        XFlush(display);
        return;
    }
#endif
#ifdef GLFW_EXPOSE_NATIVE_WIN32
    if (!bShowOnPager)
    {
        auto win = glfwGetWin32Window(window);
        LONG_PTR style = GetWindowLongPtr(win, GWL_EXSTYLE);
        SetWindowLongPtr(win, GWL_EXSTYLE, (style & ~WS_EX_APPWINDOW) | WS_EX_TOOLWINDOW);
    }
    else
    {
        auto win = glfwGetWin32Window(window);
        LONG_PTR style = GetWindowLongPtr(win, GWL_EXSTYLE);
        SetWindowLongPtr(win, GWL_EXSTYLE, (style & WS_EX_APPWINDOW) | ~WS_EX_TOOLWINDOW);
    }
#endif
}

bool UImGui::WindowGLFW::Platform_getWindowShowingOnTaskbar() noexcept
{
    return bShowOnPager;
}

void UImGui::WindowGLFW::Platform_setWindowType(String type) noexcept
{
#ifdef GLFW_EXPOSE_NATIVE_X11
    if (glfwGetPlatform() == GLFW_PLATFORM_X11)
    {
        Display* display = glfwGetX11Display();
        const ::Window win = glfwGetX11Window(window);

        const Atom windowType = XInternAtom(display, "_NET_WM_WINDOW_TYPE", 1);
        if (windowType == None)
        {
            Logger::log("Couldn't find atom of type \"_NET_WM_WINDOW_TYPE\"!", ULOG_LOG_TYPE_ERROR);
            return;
        }

        Atom windowTypeT = XInternAtom(display, type, 1);
        if (windowTypeT == None)
        {
            Logger::log("Couldn't find atom of type \"", ULOG_LOG_TYPE_ERROR, type, "\"!");
            return;
        }

        XChangeProperty(display, win, windowType, XA_ATOM, 32, PropModeReplace, reinterpret_cast<unsigned char*>(&windowTypeT), 1);
    }
#endif
}

size_t UImGui::WindowGLFW::Platform_getWindowID() noexcept
{
#ifdef GLFW_EXPOSE_NATIVE_X11
    if (glfwGetPlatform() == GLFW_PLATFORM_X11)
    {
        Display* display = glfwGetX11Display();
        const ::Window win = glfwGetX11Window(window);
        const Atom pid = XInternAtom(display, "_NET_WM_PID", 1);
        if (pid == None)
        {
            Logger::log("Couldn't find the \"_NET_WM_PID\" Atom!", ULOG_LOG_TYPE_ERROR);
            return -1;
        }
        Atom type;
        int format;
        uint64_t nItems;
        uint64_t bytesAfter;
        unsigned char* propPID = nullptr;

        const auto result = XGetWindowProperty(display, win, pid, 0, 1, False, XA_CARDINAL, &type, &format, &nItems, &bytesAfter, &propPID);
        if (result == Success && propPID != nullptr)
        {
            const uint64_t xid = *reinterpret_cast<uint64_t*>(propPID);
            XFree(propPID);
            return xid;
        }
        Logger::log("Failed to get \"_NET_WM_PID\" of the current window or the XID is output by XGetWindowProperty is null.", ULOG_LOG_TYPE_ERROR);
        return -1;
    }
#endif
#ifdef GLFW_EXPOSE_NATIVE_WAYLAND
    if (glfwGetPlatform() == GLFW_PLATFORM_WAYLAND)
    {
        // TODO: Implement for 2.0
    }
#endif
#ifdef GLFW_EXPOSE_NATIVE_WIN32
    return GetWindowLong(glfwGetWin32Window(window), GWL_ID);
#elif defined(GLFW_EXPOSE_NATIVE_COCOA)
    return (intptr_t)glfwGetCocoaWindow(window);
#endif
    return 0;
}

void* UImGui::WindowGLFW::Platform_getNativeWindowHandle() noexcept
{
#ifdef __APPLE__
    return glfwGetCocoaWindow(window);
#elifdef _WIN32
    return glfwGetWin32Window(window);
#elifdef __EMSCRIPTEN__
    return (void*)"#canvas";
#else
    return (glfwGetPlatform() == GLFW_PLATFORM_WAYLAND) ? glfwGetWaylandWindow(window) : reinterpret_cast<void*>(glfwGetX11Window(window));
#endif
}

UImGui::WindowPlatform UImGui::WindowGLFW::Platform_getCurrentWindowPlatform() noexcept
{
#ifdef __APPLE__
    return UIMGUI_WINDOW_PLATFORM_COCOA;
#elifdef _WIN32
    return UIMGUI_WINDOW_PLATFORM_WIN32;
#elifdef __EMSCRIPTEN__
    return UIMGUI_WINDOW_PLATFORM_EMSCRIPTEN;
#else
    return (glfwGetPlatform() == GLFW_PLATFORM_WAYLAND) ? UIMGUI_WINDOW_PLATFORM_WAYLAND : UIMGUI_WINDOW_PLATFORM_X11;
#endif
}

void* UImGui::WindowGLFW::Platform_getNativeDisplay() noexcept
{
#if defined(__EMSCRIPTEN__) || defined(__APPLE__) || defined(_WIN32)
    return nullptr;
#else
    return (glfwGetPlatform() == GLFW_PLATFORM_WAYLAND) ? CAST(void*, glfwGetWaylandDisplay()) : CAST(void*, glfwGetX11Display());
#endif
}
