#include "Window.hpp"
#ifdef _WIN32
    #define GLFW_EXPOSE_NATIVE_WIN32
#elif __APPLE__
    #define GLFW_EXPOSE_NATIVE_COCOA
#elif !__EMSCRIPTEN__
    #ifdef GLFW_USE_WAYLAND
        #define GLFW_EXPOSE_NATIVE_WAYLAND
    #else
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

void UImGui::WindowInternal::setWindowAlwaysOnTop() noexcept
{
#ifdef GLFW_EXPOSE_NATIVE_X11
    Display* display = glfwGetX11Display();
    ::Window root = DefaultRootWindow(display);
    ::Window window = glfwGetX11Window(windowMain);

    Atom wmStateAbove = XInternAtom(display, "_NET_WM_STATE_ABOVE", 1);
    if (wmStateAbove == None)
        Logger::log("Cannot find atom for _NET_WM_STATE_ABOVE!", ULOG_LOG_TYPE_ERROR);

    Atom wmNetWmState = XInternAtom(display, "_NET_WM_STATE", 1);
    if (wmNetWmState == None)
        Logger::log("Cannot find atom for _NET_WM_STATE!", ULOG_LOG_TYPE_ERROR);

    if (wmStateAbove != None)
    {
        XClientMessageEvent xclient;
        memset(&xclient, 0, sizeof(xclient));

        xclient.type = ClientMessage;
        xclient.window = window;
        xclient.message_type = wmNetWmState;
        xclient.format = 32;
        xclient.data.l[0] = 1;
        xclient.data.l[1] = static_cast<long>(wmStateAbove);
        xclient.data.l[2] = 0;
        xclient.data.l[3] = 0;
        xclient.data.l[4] = 0;
        XSendEvent(display, root, false, SubstructureRedirectMask | SubstructureNotifyMask, (XEvent*)&xclient);
        XFlush(display);
    }
#else
    #ifdef GLFW_EXPOSE_NATIVE_WIN32
        auto window = glfwGetWin32Window(windowMain);
        SetWindowPos(window, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
    #elif !__EMSCRIPTEN__
        MacOSWindow::setWindowAlwaysAbove(glfwGetCocoaWindow(windowMain));
    #endif
#endif
}

void UImGui::WindowInternal::setWindowAlwaysBelow() noexcept
{
#ifdef GLFW_EXPOSE_NATIVE_X11
    Display* display = glfwGetX11Display();
    ::Window window = glfwGetX11Window(windowMain);
    ::Window root = DefaultRootWindow(display);

    Atom wmNetWmState = XInternAtom(display, "_NET_WM_STATE", 1);
    if (wmNetWmState == None)
    {
        Logger::log("Couldn't find the \"_NET_WM_STATE\" Atom!", ULOG_LOG_TYPE_ERROR);
        return;
    }

    Atom wmStateSticky = XInternAtom(display, "_NET_WM_STATE_STICKY", 1);
    if (wmStateSticky == None)
    {
        Logger::log("Couldn't find the \"_NET_WM_STATE_STICKY\" Atom!", ULOG_LOG_TYPE_ERROR);
        return;
    }

    Atom wmStateBelow = XInternAtom(display, "_NET_WM_STATE_BELOW", 1);
    if (wmStateBelow == None)
    {
        Logger::log("Couldn't find the \"_NET_WM_STATE_BELOW\" Atom!", ULOG_LOG_TYPE_ERROR);
        return;
    }

    XClientMessageEvent xclient;
    memset(&xclient, 0, sizeof(xclient));

    xclient.type = ClientMessage;
    xclient.window = window;
    xclient.message_type = wmNetWmState;
    xclient.format = 32;
    xclient.data.l[0] = _NET_WM_STATE_ADD;
    xclient.data.l[1] = (long)wmStateBelow;

    XSendEvent(display, root, False, SubstructureRedirectMask | SubstructureNotifyMask, (XEvent *)&xclient);

    xclient.type = ClientMessage;
    xclient.window = window;
    xclient.message_type = wmNetWmState;
    xclient.format = 32;
    xclient.data.l[0] = _NET_WM_STATE_ADD;
    xclient.data.l[1] = (long)wmStateSticky;

    XSendEvent(display, root, False, SubstructureRedirectMask | SubstructureNotifyMask, (XEvent *)&xclient);
    XFlush(display);
#else
    #ifdef GLFW_EXPOSE_NATIVE_WIN32
        auto window = glfwGetWin32Window(windowMain);
            SetWindowPos(window, HWND_BOTTOM, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
            //DefWindowProcA(window, WM_WINDOWPOSCHANGING, 0, 0);
    #elif !__EMSCRIPTEN__
        MacOSWindow::setWindowAlwaysBelow(glfwGetCocoaWindow(windowMain));
    #endif
#endif
}

void UImGui::WindowInternal::setWindowType(const char* type) noexcept
{
#ifdef GLFW_EXPOSE_NATIVE_X11
    Display* display = glfwGetX11Display();
    ::Window window = glfwGetX11Window(windowMain);

    Atom windowType = XInternAtom(display, "_NET_WM_WINDOW_TYPE", 1);
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

    XChangeProperty(display, window, windowType, XA_ATOM, 32, PropModeReplace, (unsigned char*)&windowTypeT, 1);
#endif
}

void UImGui::WindowInternal::setShowWindowInPager(const bool bShowInPagerr) noexcept
{
    bShowOnPager = bShowInPagerr;
#ifdef GLFW_EXPOSE_NATIVE_X11
    if (!bShowOnPager)
    {
        Display* display = glfwGetX11Display();
        ::Window window = glfwGetX11Window(windowMain);
        ::Window root = DefaultRootWindow(display);

        Atom wmNetWmState = XInternAtom(display, "_NET_WM_STATE", 1);
        if (wmNetWmState == None)
        {
            Logger::log("Couldn't find the \"_NET_WM_STATE\" Atom!", ULOG_LOG_TYPE_ERROR);
            return;
        }

        Atom wmStateSkipPager = XInternAtom(display, "_NET_WM_STATE_SKIP_PAGER", 1);
        if (wmStateSkipPager == None)
        {
            Logger::log("Couldn't find the \"_NET_WM_STATE_SKIP_PAGER\" Atom!", ULOG_LOG_TYPE_ERROR);
            return;
        }
        XClientMessageEvent xclient;
        memset(&xclient, 0, sizeof(xclient));

        xclient.type = ClientMessage;
        xclient.window = window;
        xclient.message_type = wmNetWmState;
        xclient.format = 32;
        xclient.data.l[0] = _NET_WM_STATE_ADD;
        xclient.data.l[1] = (long)wmStateSkipPager;

        XSendEvent(display, root, False, SubstructureRedirectMask | SubstructureNotifyMask, (XEvent *)&xclient);
        XFlush(display);
    }
#else
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
#endif
}

void UImGui::WindowInternal::setShowWindowOnTaskbar(const bool bShowOnTaskbarr) noexcept
{
    bShowOnTaskbar = bShowOnTaskbarr;
#ifdef GLFW_EXPOSE_NATIVE_X11
    if (!bShowOnTaskbar)
    {
        Display* display = glfwGetX11Display();
        ::Window window = glfwGetX11Window(windowMain);
        ::Window root = DefaultRootWindow(display);

        Atom wmNetWmState = XInternAtom(display, "_NET_WM_STATE", 1);
        if (wmNetWmState == None)
        {
            Logger::log("Couldn't find the \"_NET_WM_STATE\" Atom!", ULOG_LOG_TYPE_ERROR);
            return;
        }

        Atom wmStateSkipTaskbar = XInternAtom(display, "_NET_WM_STATE_SKIP_TASKBAR", 1);
        if (wmStateSkipTaskbar == None)
        {
            Logger::log("Couldn't find the \"NET_WM_STATE_SKIP_TASKBAR\" Atom!", ULOG_LOG_TYPE_ERROR);
            return;
        }

        XClientMessageEvent xclient;
        memset(&xclient, 0, sizeof(xclient));

        xclient.type = ClientMessage;
        xclient.window = window;
        xclient.message_type = wmNetWmState;
        xclient.format = 32;
        xclient.data.l[0] = _NET_WM_STATE_ADD;
        xclient.data.l[1] = (long)wmStateSkipTaskbar;

        XSendEvent(display, root, False, SubstructureRedirectMask | SubstructureNotifyMask, (XEvent *)&xclient);
        XFlush(display);
    }
#else
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
#endif
}

size_t UImGui::WindowInternal::getWindowID() noexcept
{
#ifdef GLFW_EXPOSE_NATIVE_X11
    Display* display = glfwGetX11Display();
    ::Window window = glfwGetX11Window(windowMain);
    Atom pid = XInternAtom(display, "_NET_WM_PID", 1);
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

    auto result = XGetWindowProperty(display, window, pid, 0, 1, False, XA_CARDINAL, &type, &format, &nItems, &bytesAfter, &propPID);
    if (result == Success && propPID != nullptr)
    {
        uint64_t xid = *((uint64_t*)propPID);
        XFree(propPID);
        return xid;
    }
    Logger::log("Failed to get \"_NET_WM_PID\" of the current window or the XID is output by XGetWindowProperty is null.", ULOG_LOG_TYPE_ERROR);
    return -1;
#else
    #ifdef GLFW_EXPOSE_NATIVE_WIN32
        return GetWindowLong(glfwGetWin32Window(windowMain), GWL_ID);
    #elif !__EMSCRIPTEN__
        return (intptr_t)glfwGetCocoaWindow(windowMain);
    #else
        return NULL;
    #endif
#endif
}