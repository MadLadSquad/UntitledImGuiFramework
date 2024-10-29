#include "Window.hpp"
#ifdef _WIN32
    #define GLFW_EXPOSE_NATIVE_WIN32
#elif __APPLE__
    #define GLFW_EXPOSE_NATIVE_COCOA
#elif !__EMSCRIPTEN__
    #ifdef __has_include(<wayland-client.h>)
        #define GLFW_EXPOSE_NATIVE_WAYLAND
    #endif
    #ifdef __has_include(<X11/Xatom.h>)
        #define GLFW_EXPOSE_NATIVE_X11
        #include <X11/Xatom.h>
        #define _NET_WM_STATE_ADD 1
    #endif
#endif

#ifdef __APPLE__
    #include <OpenGL/GL.h>
    #include "macOS/MacOSWindowPlatform.h"
#else
    #include <glad/include/glad/gl.h>
#endif
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

#include <cstring>

void UImGui::WindowInternal::setWindowAlwaysOnTop() const noexcept
{
#ifdef GLFW_EXPOSE_NATIVE_X11
    if (glfwGetPlatform() == GLFW_PLATFORM_X11)
    {
        Display* display = glfwGetX11Display();
        const ::Window root = DefaultRootWindow(display);
        ::Window window = glfwGetX11Window(windowMain);

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
            xclient.window = window;
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
    auto window = glfwGetWin32Window(windowMain);
    SetWindowPos(window, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
#elif GLFW_EXPOSE_NATIVE_COCOA
    MacOSWindow::setWindowAlwaysAbove(glfwGetCocoaWindow(windowMain));
#endif
}

void UImGui::WindowInternal::setWindowAlwaysBelow() const noexcept
{
#ifdef GLFW_EXPOSE_NATIVE_X11
    if (glfwGetPlatform() == GLFW_PLATFORM_X11)
    {
        Display* display = glfwGetX11Display();
        ::Window window = glfwGetX11Window(windowMain);
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
        xclient.window = window;
        xclient.message_type = wmNetWmState;
        xclient.format = 32;
        xclient.data.l[0] = _NET_WM_STATE_ADD;
        xclient.data.l[1] = static_cast<long>(wmStateBelow);

        XSendEvent(display, root, False, SubstructureRedirectMask | SubstructureNotifyMask, reinterpret_cast<XEvent*>(&xclient));

        xclient.type = ClientMessage;
        xclient.window = window;
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
    auto window = glfwGetWin32Window(windowMain);
    SetWindowPos(window, HWND_BOTTOM, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
    //DefWindowProcA(window, WM_WINDOWPOSCHANGING, 0, 0);
#elif GLFW_EXPOSE_NATIVE_COCOA
    MacOSWindow::setWindowAlwaysBelow(glfwGetCocoaWindow(windowMain));
#endif
}

void UImGui::WindowInternal::setWindowType(const char* type) const noexcept
{
#ifdef GLFW_EXPOSE_NATIVE_X11
    if (glfwGetPlatform() == GLFW_PLATFORM_X11)
    {
        Display* display = glfwGetX11Display();
        const ::Window window = glfwGetX11Window(windowMain);

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

        XChangeProperty(display, window, windowType, XA_ATOM, 32, PropModeReplace, reinterpret_cast<unsigned char*>(&windowTypeT), 1);
    }
#endif
}

void UImGui::WindowInternal::setShowWindowInPager(const bool bShowInPagerr) noexcept
{
    bShowOnPager = bShowInPagerr;
#ifdef GLFW_EXPOSE_NATIVE_X11
    if (glfwGetPlatform() == GLFW_PLATFORM_X11 && !bShowOnPager)
    {
        Display* display = glfwGetX11Display();
        ::Window window = glfwGetX11Window(windowMain);
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
        xclient.window = window;
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
        auto window = glfwGetWin32Window(windowMain);
        LONG_PTR style = GetWindowLongPtr(window, GWL_EXSTYLE);
        SetWindowLongPtr(window, GWL_EXSTYLE, (style & ~WS_EX_APPWINDOW) | WS_EX_TOOLWINDOW);
    }
    else
    {
        auto window = glfwGetWin32Window(windowMain);
        LONG_PTR style = GetWindowLongPtr(window, GWL_EXSTYLE);
        SetWindowLongPtr(window, GWL_EXSTYLE, (style & WS_EX_APPWINDOW) | ~WS_EX_TOOLWINDOW);
    }
#endif
}

void UImGui::WindowInternal::setShowWindowOnTaskbar(const bool bShowOnTaskbarr) noexcept
{
    bShowOnTaskbar = bShowOnTaskbarr;
#ifdef GLFW_EXPOSE_NATIVE_X11
    if (glfwGetPlatform() == GLFW_PLATFORM_X11 && !bShowOnTaskbar)
    {
        Display* display = glfwGetX11Display();
        ::Window window = glfwGetX11Window(windowMain);
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
        xclient.window = window;
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
        auto window = glfwGetWin32Window(windowMain);
        LONG_PTR style = GetWindowLongPtr(window, GWL_EXSTYLE);
        SetWindowLongPtr(window, GWL_EXSTYLE, (style & ~WS_EX_APPWINDOW) | WS_EX_TOOLWINDOW);
    }
    else
    {
        auto window = glfwGetWin32Window(windowMain);
        LONG_PTR style = GetWindowLongPtr(window, GWL_EXSTYLE);
        SetWindowLongPtr(window, GWL_EXSTYLE, (style & WS_EX_APPWINDOW) | ~WS_EX_TOOLWINDOW);
    }
#endif
}

size_t UImGui::WindowInternal::getWindowID() const noexcept
{
#ifdef GLFW_EXPOSE_NATIVE_X11
    if (glfwGetPlatform() == GLFW_PLATFORM_X11)
    {
        Display* display = glfwGetX11Display();
        const ::Window window = glfwGetX11Window(windowMain);
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

        const auto result = XGetWindowProperty(display, window, pid, 0, 1, False, XA_CARDINAL, &type, &format, &nItems, &bytesAfter, &propPID);
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
        return GetWindowLong(glfwGetWin32Window(windowMain), GWL_ID);
#elif GLFW_EXPOSE_NATIVE_COCOA
        return (intptr_t)glfwGetCocoaWindow(windowMain);
#endif
    return 0;
}