#define STB_IMAGE_IMPLEMENTATION
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

#include "Window.hpp"
#include "Global.hpp"
#ifndef __APPLE__
    #include <GL/glew.h>
#else
    #include <OpenGL/GL.h>
    #include "macOS/MacOSWindowPlatform.h"
#endif
#include <GLFW/glfw3.h>

#include <GLFW/glfw3native.h>
#include <ThirdParty/source-libraries/stb_image.h>
#include <yaml-cpp/yaml.h>
#include <Interfaces/RendererInterface.hpp>
#include <Interfaces/WindowInterface.hpp>

#include <Components/Instance.hpp>

UImGui::WindowInternal::WindowInternal() noexcept
{
    keys.fill(0);
}

GLFWwindow* UImGui::WindowInternal::data() const noexcept
{
    return windowMain;
}

bool& UImGui::WindowInternal::resized() noexcept
{
    return bResized;
}

#define SAVE_CONFIG_YAML_BASIC(x, y) out << YAML::Key << #x << YAML::Value << windowData.y

void UImGui::WindowInternal::saveConfig(bool bSaveKeybindings) const noexcept
{
    std::ofstream fout(internalGlobal.instance->initInfo.configDir + "Core/Window.yaml");
    {
        YAML::Emitter out;
        out << YAML::BeginMap;

        SAVE_CONFIG_YAML_BASIC(layout-location, layoutLocation);
        SAVE_CONFIG_YAML_BASIC(icon, iconLocation);

        out << YAML::Key << "width" << YAML::Value << windowSize.x;
        out << YAML::Key << "height" << YAML::Value << windowSize.y;

        SAVE_CONFIG_YAML_BASIC(fullscreen, fullscreen);
        SAVE_CONFIG_YAML_BASIC(window-name, name);
        SAVE_CONFIG_YAML_BASIC(resizeable, bResizeable);
        SAVE_CONFIG_YAML_BASIC(transparent-surface, bSurfaceTransparent);
        SAVE_CONFIG_YAML_BASIC(hidden, bHidden);
        SAVE_CONFIG_YAML_BASIC(focusedisplay, bFocused);
        SAVE_CONFIG_YAML_BASIC(size-limits, sizeLimits);
        SAVE_CONFIG_YAML_BASIC(aspect-ratio-size-limit, aspectRatioSizeLimit);
        SAVE_CONFIG_YAML_BASIC(decoratedisplay, bDecorated);
        SAVE_CONFIG_YAML_BASIC(maximisedisplay, bMaximised);

        out << YAML::EndMap;

        fout << out.c_str();
        fout.close();
    }

    if (bSaveKeybindings)
    {
        YAML::Emitter out;
        out << YAML::BeginMap << YAML::Key << "bindings" << YAML::BeginSeq;

        for (auto& a : inputActionList)
        {
            out << YAML::BeginMap << YAML::Key << "key" << YAML::Value << a.name;
            out << YAML::Key << "val" << YAML::Value << YAML::Flow << YAML::BeginSeq;
            for (auto& f : a.keyCodes)
                out << static_cast<int>(f);
            out << YAML::EndSeq;
            out << YAML::EndMap;
        }
        out << YAML::EndSeq << YAML::EndMap;

        fout = std::ofstream(internalGlobal.instance->initInfo.configDir + "Core/Keybindings.yaml");
        fout << out.c_str();
        fout.close();
    }
}

void UImGui::WindowInternal::setTitle(const String title) noexcept
{
    glfwSetWindowTitle(windowMain, title);
    windowData.name = title;
}

UImGui::FVector2 UImGui::WindowInternal::getMousePositionChange() noexcept
{
    const FVector2 ret = mouseOffset;
    mouseOffset = { 0.0f, 0.0f };

    return ret;
}

UImGui::FVector2 UImGui::WindowInternal::getScroll() noexcept
{
    const FVector2 ret = scroll;
    scroll = { 0.0f, 0.0f };
    return ret;
}

void UImGui::WindowInternal::createWindow() noexcept
{
    // Load all config we need
    openConfig();

    // Init GLFW
    if (!glfwInit())
    {
        Logger::log("GLFW initialisation failed!", UVK_LOG_TYPE_ERROR);
        glfwTerminate();
        return;
    }
    Logger::log("Setting up the window", UVK_LOG_TYPE_NOTE);

    if (Renderer::data().bVulkan)
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API); // Have to set this to NO_API because that's how Vulkan is done in it
    else
    {
#if !__APPLE__ && !__EMSCRIPTEN__
        // Add GLFW window flags and enable OpenGL
        glewExperimental = GL_TRUE;
#endif
#ifdef __EMSCRIPTEN__
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
        glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
#else
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        #ifdef __APPLE__
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
        #else
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
        #endif
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, true);
#endif
        glfwWindowHint(GLFW_SAMPLES, static_cast<int>(Renderer::data().msaaSamples));
    }

#ifndef __EMSCRIPTEN__
    glfwWindowHint(GLFW_RESIZABLE, windowData.bResizeable);
    glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, windowData.bSurfaceTransparent);
    glfwWindowHint(GLFW_VISIBLE, !windowData.bHidden);
    glfwWindowHint(GLFW_FOCUSED, windowData.bFocused);
    glfwWindowHint(GLFW_DECORATED, windowData.bDecorated);
    glfwWindowHint(GLFW_MAXIMIZED, windowData.bMaximised);
#endif

    Logger::log("Window settings configured", UVK_LOG_TYPE_NOTE);
    GLFWmonitor* monitor = nullptr;
#ifndef __EMSCRIPTEN__
    if (windowData.fullscreen)
        monitor = glfwGetPrimaryMonitor();
#endif

    windowMain = glfwCreateWindow(static_cast<int>(windowSize.x), static_cast<int>(windowSize.y), windowData.name.c_str(), monitor, nullptr);
    if (!windowMain)
    {
        Logger::log("GLFW window creation failed!", UVK_LOG_TYPE_ERROR);
        glfwTerminate();
        return;
    }
    Logger::log("Created window", UVK_LOG_TYPE_NOTE);

    // Load window icon
    setIcon(windowData.iconLocation.c_str());

    Window::setSizeLimits({ windowData.sizeLimits.x, windowData.sizeLimits.y }, { windowData.sizeLimits.z, windowData.sizeLimits.w });
    Window::setSizeLimitByAspectRatio(windowData.aspectRatioSizeLimit);

    Logger::log("Window was created successfully", UVK_LOG_TYPE_SUCCESS);

    // Set framebuffer size
    int tempx = static_cast<int>(windowSize.x);
    int tempy = static_cast<int>(windowSize.y);

    glfwGetFramebufferSize(windowMain, &tempx, &tempy);

    windowSize.x = static_cast<float>(tempx);
    windowSize.y = static_cast<float>(tempy);

    // Set the context
    glfwMakeContextCurrent(windowMain);

    // Set swap interval
    if (Renderer::data().bUsingVSync)
        glfwSwapInterval(1);

    // Set callbacks
    configureCallbacks();

    if (!Renderer::data().bVulkan)
    {
#if !__APPLE__ && !__EMSCRIPTEN__
        if (glewInit() != GLEW_OK)
        {
            glfwDestroyWindow(windowMain);
            glfwTerminate();
            Logger::log("GLEW initialisation failed!", UVK_LOG_TYPE_ERROR);
            return;
        }
#endif
        glEnable(GL_MULTISAMPLE);
        glEnable(GL_DEPTH_TEST);
        // Set viewport and global pointer to use in callbacks
        glViewport(0, 0, tempx, tempy);
    }
    glfwSetWindowUserPointer(windowMain, this);
}

void UImGui::WindowInternal::destroyWindow() const noexcept
{
    glfwDestroyWindow(windowMain);
    glfwTerminate();
}

void UImGui::WindowInternal::configureCallbacks() const noexcept
{
    glfwSetFramebufferSizeCallback(windowMain, framebufferSizeCallback);
    glfwSetKeyCallback(windowMain, keyboardInputCallback);
    glfwSetCursorPosCallback(windowMain, mouseCursorPositionCallback);
    glfwSetMouseButtonCallback(windowMain, mouseKeyInputCallback);
    glfwSetScrollCallback(windowMain, scrollInputCallback);
    glfwSetWindowPosCallback(windowMain, windowPositionCallback);

    glfwSetWindowSizeCallback(windowMain, windowSizeCallback);
    glfwSetWindowCloseCallback(windowMain, windowCloseCallback);
    glfwSetWindowFocusCallback(windowMain, windowFocusCallback);
    glfwSetWindowIconifyCallback(windowMain, windowIconifyCallback);
    glfwSetWindowContentScaleCallback(windowMain, windowContentScaleCallback);
    glfwSetWindowRefreshCallback(windowMain, windowRefreshCallback);
    glfwSetWindowMaximizeCallback(windowMain, windowMaximisedCallback);

    glfwSetMonitorCallback(monitorCallback);

    glfwSetDropCallback(windowMain, windowOSDragDropCallback);

    glfwSetErrorCallback(windowErrorCallback);
}

void UImGui::WindowInternal::framebufferSizeCallback(GLFWwindow* window, const int width, const int height) noexcept
{
    auto* windowInst = static_cast<WindowInternal*>(glfwGetWindowUserPointer(window));

    windowInst->windowSize.x = static_cast<float>(width);
    windowInst->windowSize.y = static_cast<float>(height);

    if (!Renderer::data().bVulkan)
        glViewport(0, 0, width, height);

    for (auto& a : windowInst->windowResizeCallbackList)
        a(width, height);
}

void UImGui::WindowInternal::keyboardInputCallback(GLFWwindow* window, const int key, int scanCode, const int action, int mods) noexcept
{
    auto* wind = CAST(WindowInternal*, glfwGetWindowUserPointer(window));
    wind->keys[key] = action;
}

void UImGui::WindowInternal::mouseKeyInputCallback(GLFWwindow* window, const int button, const int action, int mods) noexcept
{
    auto* wind = CAST(WindowInternal*, glfwGetWindowUserPointer(window));
    wind->keys[button] = action;
}

void UImGui::WindowInternal::mouseCursorPositionCallback(GLFWwindow* window, const double xpos, const double ypos) noexcept
{
    auto* windowInst = static_cast<WindowInternal*>(glfwGetWindowUserPointer(window));

    if (windowInst->bFirstMove)
    {
        windowInst->mouseLastPos.x = static_cast<float>(xpos);
        windowInst->mouseLastPos.y = static_cast<float>(ypos);
        windowInst->bFirstMove = false;
    }

    windowInst->mouseOffset.x = static_cast<float>(xpos) - windowInst->mouseLastPos.x;
    windowInst->mouseOffset.y = windowInst->mouseLastPos.y - static_cast<float>(ypos);

    windowInst->mouseLastPos.x = static_cast<float>(xpos);
    windowInst->mouseLastPos.y = static_cast<float>(ypos);
}

void UImGui::WindowInternal::scrollInputCallback(GLFWwindow* window, const double xoffset, const double yoffset) noexcept
{
    auto* windowInst = static_cast<WindowInternal*>(glfwGetWindowUserPointer(window));

    windowInst->scroll = { static_cast<float>(xoffset), static_cast<float>(yoffset) };
}

void UImGui::WindowInternal::windowPositionCallback(GLFWwindow* window, const int xpos, const int ypos) noexcept
{
    auto* windowInst = static_cast<WindowInternal*>(glfwGetWindowUserPointer(window));

    windowInst->windowLastPos.x = windowInst->windowCurrentPos.x;
    windowInst->windowLastPos.y = windowInst->windowCurrentPos.y;

    windowInst->windowCurrentPos.x = static_cast<float>(xpos);
    windowInst->windowCurrentPos.y = static_cast<float>(ypos);

    for (auto& a : windowInst->windowPositionChangeCallbackList)
        a({ static_cast<float>(xpos), static_cast<float>(ypos) });
}

#define OPEN_CONFIG_GET_YAML_BASIC(x, y, z) if (out[#x]) windowData.y = out[#x].as<z>()

void UImGui::WindowInternal::openConfig()
{
    YAML::Node out;

    try
    {
        out = YAML::LoadFile(UImGui::internalGlobal.instance->initInfo.configDir + "Core/Window.yaml");
    }
    catch (YAML::BadFile&)
    {
        Logger::log("Couldn't open the Window.yaml config file, please fix this error before shipping for production! Starting with default settings!", UVK_LOG_TYPE_ERROR);
        goto skip_window_config;
    }

    if (out["width"] && out["height"])
    {
        windowSize.x = out["width"].as<float>();
        windowSize.y = out["height"].as<float>();
    }

    OPEN_CONFIG_GET_YAML_BASIC(icon, iconLocation, FString);
    OPEN_CONFIG_GET_YAML_BASIC(layout-location, layoutLocation, FString);
    OPEN_CONFIG_GET_YAML_BASIC(fullscreen, fullscreen, bool);
    OPEN_CONFIG_GET_YAML_BASIC(window-name, name, FString);
    OPEN_CONFIG_GET_YAML_BASIC(resizeable, bResizeable, bool);
    OPEN_CONFIG_GET_YAML_BASIC(transparent-surface, bSurfaceTransparent, bool);
    OPEN_CONFIG_GET_YAML_BASIC(visible, bHidden, bool);
    OPEN_CONFIG_GET_YAML_BASIC(focusedisplay, bFocused, bool);
    OPEN_CONFIG_GET_YAML_BASIC(size-limits, sizeLimits, FVector4);
    OPEN_CONFIG_GET_YAML_BASIC(aspect-ratio-size-limit, aspectRatioSizeLimit, FVector2);
    OPEN_CONFIG_GET_YAML_BASIC(decoratedisplay, bDecorated, bool);
    OPEN_CONFIG_GET_YAML_BASIC(maximisedisplay, bMaximised, bool);
skip_window_config:

    try
    {
        out = YAML::LoadFile(internalGlobal.instance->initInfo.configDir + "Core/Keybindings.yaml");
    }
    catch (YAML::BadFile&)
    {
        Logger::log("Couldn't open the Keybindings.yaml config file, please fix this error before shipping for production! Starting with default settings!", UVK_LOG_TYPE_ERROR);
        return;
    }

    auto binds = out["bindings"];
    if (binds)
    {
        for (const YAML::Node& a : binds)
        {
            InputAction action;
            action.name = a["key"].as<std::string>();
            action.keyCodes = a["val"].as<std::vector<uint16_t>>();
            inputActionList.push_back(action);
        }
    }
}

void UImGui::WindowInternal::close() const noexcept
{
    glfwSetWindowShouldClose(windowMain, true);
}

void UImGui::WindowInternal::updateKeyState() noexcept
{
    for (auto& a : inputActionList)
    {
        if (!a.keyCodes.empty())
        {
            for (const auto& f : a.keyCodes)
                if (keys[f] != keys[a.keyCodes[0]])
                    goto finish_inner_loop;
            a.state = keys[a.keyCodes[0]];
        }
finish_inner_loop:;
    }
}

void UImGui::WindowInternal::setIcon(const String name) const noexcept
{
#ifndef __EMSCRIPTEN__
    GLFWimage images[1];
    images[0].pixels = stbi_load((internalGlobal.instance->initInfo.contentDir + name).c_str(), &images[0].width, &images[0].height, nullptr, 4);
    glfwSetWindowIcon(windowMain, 1, images);
    stbi_image_free(images[0].pixels);
#endif
}

void UImGui::WindowInternal::setWindowAlwaysOnTop() noexcept
{
#ifdef GLFW_EXPOSE_NATIVE_X11
    Display* display = glfwGetX11Display();
    ::Window root = DefaultRootWindow(display);
    ::Window window = glfwGetX11Window(windowMain);

    Atom wmStateAbove = XInternAtom(display, "_NET_WM_STATE_ABOVE", 1);
    if (wmStateAbove == None)
        Logger::log("Cannot find atom for _NET_WM_STATE_ABOVE!", UVK_LOG_TYPE_ERROR);

    Atom wmNetWmState = XInternAtom(display, "_NET_WM_STATE", 1);
    if (wmNetWmState == None)
        Logger::log("Cannot find atom for _NET_WM_STATE!", UVK_LOG_TYPE_ERROR);

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
        Logger::log("Couldn't find the \"_NET_WM_STATE\" Atom!", UVKLog::UVK_LOG_TYPE_ERROR);
        return;
    }

    Atom wmStateSticky = XInternAtom(display, "_NET_WM_STATE_STICKY", 1);
    if (wmStateSticky == None)
    {
        Logger::log("Couldn't find the \"_NET_WM_STATE_STICKY\" Atom!", UVKLog::UVK_LOG_TYPE_ERROR);
        return;
    }

    Atom wmStateBelow = XInternAtom(display, "_NET_WM_STATE_BELOW", 1);
    if (wmStateBelow == None)
    {
        Logger::log("Couldn't find the \"_NET_WM_STATE_BELOW\" Atom!", UVKLog::UVK_LOG_TYPE_ERROR);
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
        Logger::log("Couldn't find atom of type \"_NET_WM_WINDOW_TYPE\"!", UVKLog::UVK_LOG_TYPE_ERROR);
        return;
    }

    Atom windowTypeT = XInternAtom(display, type, 1);
    if (windowTypeT == None)
    {
        Logger::log("Couldn't find atom of type \"", UVKLog::UVK_LOG_TYPE_ERROR, type, "\"!");
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
            Logger::log("Couldn't find the \"_NET_WM_STATE\" Atom!", UVKLog::UVK_LOG_TYPE_ERROR);
            return;
        }

        Atom wmStateSkipPager = XInternAtom(display, "_NET_WM_STATE_SKIP_PAGER", 1);
        if (wmStateSkipPager == None)
        {
            Logger::log("Couldn't find the \"_NET_WM_STATE_SKIP_PAGER\" Atom!", UVKLog::UVK_LOG_TYPE_ERROR);
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
            Logger::log("Couldn't find the \"_NET_WM_STATE\" Atom!", UVKLog::UVK_LOG_TYPE_ERROR);
            return;
        }

        Atom wmStateSkipTaskbar = XInternAtom(display, "_NET_WM_STATE_SKIP_TASKBAR", 1);
        if (wmStateSkipTaskbar == None)
        {
            Logger::log("Couldn't find the \"NET_WM_STATE_SKIP_TASKBAR\" Atom!", UVKLog::UVK_LOG_TYPE_ERROR);
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
        Logger::log("Couldn't find the \"_NET_WM_PID\" Atom!", UVK_LOG_TYPE_ERROR);
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
    Logger::log("Failed to get \"_NET_WM_PID\" of the current window or the XID is output by XGetWindowProperty is null.", UVK_LOG_TYPE_ERROR);
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

void UImGui::WindowInternal::windowSizeCallback(GLFWwindow* window, const int width, const int height) noexcept
{
    auto* windowInst = static_cast<WindowInternal*>(glfwGetWindowUserPointer(window));
    windowInst->windowSizeInScreenCoords = { CAST(float, width), CAST(float, height) };
    for (auto& a : windowInst->windowResizeInScreenCoordCallbackList)
        a(width, height);
}

void UImGui::WindowInternal::windowCloseCallback(GLFWwindow* window) noexcept
{
    for (auto& a : static_cast<WindowInternal*>(glfwGetWindowUserPointer(window))->windowCloseCallbackList)
        a();
}

void UImGui::WindowInternal::windowFocusCallback(GLFWwindow* window, const int focused) noexcept
{
    for (auto& a : static_cast<WindowInternal*>(glfwGetWindowUserPointer(window))->windowFocusCallbackList)
        a(focused);
}

void UImGui::WindowInternal::windowIconifyCallback(GLFWwindow* window, const int iconified) noexcept
{
    for (auto& a : static_cast<WindowInternal*>(glfwGetWindowUserPointer(window))->windowIconifiedCallbackList)
        a(iconified);
}

void UImGui::WindowInternal::windowContentScaleCallback(GLFWwindow* window, const float x, const float y) noexcept
{
    for (auto& a : static_cast<WindowInternal*>(glfwGetWindowUserPointer(window))->windowContentScaleChangeCallbackList)
        a({ x, y });
}

void UImGui::WindowInternal::windowRefreshCallback(GLFWwindow* window) noexcept
{
    for (auto& a : static_cast<WindowInternal*>(glfwGetWindowUserPointer(window))->windowRefreshCallbackList)
        a();
}

void UImGui::WindowInternal::windowMaximisedCallback(GLFWwindow* window, const int maximised) noexcept
{
    for (auto& a : static_cast<WindowInternal*>(glfwGetWindowUserPointer(window))->windowMaximisedCallbackList)
        a(maximised);
}

void UImGui::WindowInternal::monitorCallback(GLFWmonitor* monitor, int event) noexcept
{
#ifndef __EMSCRIPTEN__
    auto* dt = CAST(Monitor*, glfwGetMonitorUserPointer(monitor));
    for (auto& a : Window::get().windowMonitorCallbackList)
        a(*dt, static_cast<MonitorState>(event));

    for (auto& a : dt->events)
        a(*dt, static_cast<MonitorState>(event));

    // Remove current monitors
    Window::get().monitors.clear();

    // Get new monitors from glfw
    int count;
    GLFWmonitor** monitors = glfwGetMonitors(&count);

    // Update monitors list
    for (size_t i = 0; i < count; i++)
        Window::get().monitors.emplace_back(monitors[i]);
#endif
}

void UImGui::WindowInternal::windowOSDragDropCallback(GLFWwindow* window, const int count, const char** paths) noexcept
{
    auto* windowInst = static_cast<WindowInternal*>(glfwGetWindowUserPointer(window));
    windowInst->dragDropPaths.clear();

    for (int i = 0; i < count; i++)
        windowInst->dragDropPaths.emplace_back(paths[i]);

    for (auto& a : windowInst->dragDropPathCallbackList)
        a(windowInst->dragDropPaths);
    for (auto& a : windowInst->dragDropPathCCallbackList)
        a(paths, count);
}

void UImGui::WindowInternal::windowErrorCallback(int code, const char* description) noexcept
{
    Logger::log("Encountered GLFW window error, ", UVKLog::UVK_LOG_TYPE_ERROR, code, ": ", description);
    for (auto& a : Window::get().windowErrorCallbackList)
        a(code, description);
}

UImGui::Monitor::Monitor(GLFWmonitor* monitor) noexcept
{
#ifndef __EMSCRIPTEN__
    this->monitor = monitor;
    glfwSetMonitorUserPointer(this->monitor, (void*)this);
#endif
}

UImGui::FVector2 UImGui::Monitor::getPhysicalSize() const noexcept
{
#ifndef __EMSCRIPTEN__
    int width = 0;
    int height = 0;
    glfwGetMonitorPhysicalSize(monitor, &width, &height);

    return FVector2{ static_cast<float>(width), static_cast<float>(height) };
#else
    return { 0.0f, 0.0f };
#endif
}

UImGui::FVector2 UImGui::Monitor::getContentScale() const noexcept
{
#ifndef __EMSCRIPTEN__
    FVector2 f = {};
    glfwGetMonitorContentScale(monitor, &f.x, &f.y);
    return f;
#else
    return { 0.0f, 0.0f };
#endif
}

UImGui::FVector2 UImGui::Monitor::getVirtualPosition() const noexcept
{
#ifndef __EMSCRIPTEN__
    int x = 0;
    int y = 0;
    glfwGetMonitorPos(monitor, &x, &y);

    return FVector2{ static_cast<float>(x), static_cast<float>(y) };
#else
    return { 0.0f, 0.0f };
#endif
}

UImGui::FVector4 UImGui::Monitor::getWorkArea() const noexcept
{
#ifndef __EMSCRIPTEN__
    int x = 0;
    int y = 0;
    int width = 0;
    int height = 0;

    glfwGetMonitorWorkarea(monitor, &x, &y, &width, &height);
    return FVector4
    {
            static_cast<float>(x),static_cast<float>(y),
            static_cast<float>(width), static_cast<float>(height)
    };
#else
    return { 0.0f, 0.0f, 0.0f, 0.0f };
#endif
}

UImGui::FString UImGui::Monitor::getName() const noexcept
{
#ifndef __EMSCRIPTEN__
    return { glfwGetMonitorName(monitor) };
#else
    return {};
#endif
}

void UImGui::Monitor::pushEvent(const std::function<void(Monitor&, MonitorState)>& f) noexcept
{
#ifndef __EMSCRIPTEN__
    events.push_back(f);
#endif
}

UImGui_CMonitorData UImGui::Monitor::CInternalGetMonitorClassDoNotTouch::UImGui_Window_getWindowMonitor()
{
#ifndef __EMSCRIPTEN__
    const auto tmp = Window::getWindowMonitor();
    return UImGui_CMonitorData
    {
            .additionalData = tmp.additionalData,
            .additionalDataSize = tmp.additionalDataSize,
            .monitor = tmp.monitor,
    };
#else
    return {};
#endif
}

void UImGui::Monitor::CInternalGetMonitorClassDoNotTouch::pushGlobalMonitorCallbackFun(const UImGui::Monitor& monitor,
                                                                                       const UImGui::MonitorState state,
                                                                                       const UImGui_Window_pushGlobalMonitorCallbackFun f)
{
#ifndef __EMSCRIPTEN__
    UImGui_CMonitorData dt;
    UImGui_Monitor_initWithMonitor_Internal(&dt, monitor.monitor);
    dt.additionalData = monitor.additionalData;
    dt.additionalDataSize = monitor.additionalDataSize;

    f(&dt, state);
#endif
}

void UImGui::Monitor::CInternalGetMonitorClassDoNotTouch::UImGui_Monitor_pushEvent(UImGui_CMonitorData* data,
                                                                                   const UImGui_Monitor_EventsFun f)
{
#ifndef __EMSCRIPTEN__
    for (auto& a : UImGui::Window::getMonitors())
    {
        if (a.monitor == data->monitor)
        {
            a.pushEvent([&](Monitor& fMonitor, const MonitorState state) -> void
            {
                UImGui_CMonitorData dt;
                UImGui_Monitor_initWithMonitor_Internal(&dt, data->monitor);
                dt.additionalData = data->additionalData;
                dt.additionalDataSize = data->additionalDataSize;

                f(&dt, state);
            });
            return;
        }
    }
    Logger::log("Invalid internal monitor address, used when pushing a monitor-local event! Address: ", UVK_LOG_TYPE_ERROR, data->monitor);
#endif
}

void UImGui::Monitor::CInternalGetMonitorClassDoNotTouch::UImGui_Monitor_setWindowMonitor(const UImGui_CMonitorData* monitor)
{
#ifndef __EMSCRIPTEN__
    Monitor m;
    m.monitor = monitor->monitor;

    UImGui::Window::setWindowMonitor(m);
#endif
}

UImGui_CMonitorData* UImGui::Monitor::CInternalGetMonitorClassDoNotTouch::UImGui_Window_getMonitors(size_t* size)
{
#ifndef __EMSCRIPTEN__
    auto& monitors = UImGui::internalGlobal.deallocationStruct.monitors;
    monitors.clear();
    for (const auto& a : Window::getMonitors())
    {
        monitors.push_back(
        {
            .additionalData = a.additionalData,
            .additionalDataSize = a.additionalDataSize,
            .monitor = a.monitor
        });
    }
    *size = monitors.size();
    return monitors.data();
#else
    return nullptr;
#endif
}
