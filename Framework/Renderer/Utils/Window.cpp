#define STB_IMAGE_IMPLEMENTATION
#ifdef _WIN32
    #define GLFW_EXPOSE_NATIVE_WIN32
#else
    #ifdef GLFW_USE_WAYLAND
        #define GLFW_EXPOSE_NATIVE_WAYLAND
    #else
        #define GLFW_EXPOSE_NATIVE_X11
        #include <X11/Xatom.h>
    #endif
#endif

#include "Window.hpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h>



#include <GLFW/glfw3native.h>
#include <ThirdParty/source-libraries/stb_image.h>
#include <yaml.h>
#include <Interfaces/RendererInterface.hpp>
#include <Interfaces/WindowInterface.hpp>

#define _NET_WM_STATE_ADD 1

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

void UImGui::WindowInternal::saveConfig(bool bSaveKeybindings) noexcept
{
    std::ofstream fout("../Config/Core/Window.yaml");
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
                out << (int)f;
            out << YAML::EndSeq;
            out << YAML::EndMap;
        }
        out << YAML::EndSeq << YAML::EndMap;

        fout = std::ofstream("../Config/Core/Keybindings.yaml");
        fout << out.c_str();
        fout.close();
    }
}

void UImGui::WindowInternal::setTitle(UImGui::String title) noexcept
{
    glfwSetWindowTitle(windowMain, title);
    windowData.name = title;
}

UImGui::FVector2 UImGui::WindowInternal::getMousePositionChange() noexcept
{
    FVector2 ret = mouseOffset;
    mouseOffset = { 0.0f, 0.0f };

    return ret;
}

UImGui::FVector2 UImGui::WindowInternal::getScroll() noexcept
{
    FVector2 ret = scroll;
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

    // Add GLFW window flags and enable OpenGL
    // TODO: Support Vulkan here
    glewExperimental = GL_TRUE;
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, true);
    glfwWindowHint(GLFW_SAMPLES, 16);
    glfwWindowHint(GLFW_RESIZABLE, windowData.bResizeable);
    glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, windowData.bSurfaceTransparent);
    glfwWindowHint(GLFW_VISIBLE, !windowData.bHidden);
    glfwWindowHint(GLFW_FOCUSED, windowData.bFocused);
    glfwWindowHint(GLFW_DECORATED, windowData.bDecorated);
    glfwWindowHint(GLFW_MAXIMIZED, windowData.bMaximised);

    Logger::log("Window settings configured", UVK_LOG_TYPE_NOTE);
    GLFWmonitor* monitor = nullptr;
    if (windowData.fullscreen)
        monitor = glfwGetPrimaryMonitor();

    windowMain = glfwCreateWindow((int)windowSize.x, (int)windowSize.y, windowData.name.c_str(), monitor, nullptr);
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
    // TODO: Support Vulkan here
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

    // Init glew
    // TODO: Support Vulkan here
    if (glewInit() != GLEW_OK)
    {
        glfwDestroyWindow(windowMain);
        glfwTerminate();
        Logger::log("GLEW initialisation failed!", UVK_LOG_TYPE_ERROR);
        return;
    }
    // Set viewport and global pointer to use in callbacks
    glViewport(0, 0, tempx, tempy);
    glfwSetWindowUserPointer(windowMain, this);
}

void UImGui::WindowInternal::destroyWindow() noexcept
{
    glfwDestroyWindow(windowMain);
    glfwTerminate();
}

void UImGui::WindowInternal::configureCallbacks() noexcept
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

void UImGui::WindowInternal::framebufferSizeCallback(GLFWwindow* window, int width, int height) noexcept
{
    auto* windowInst = static_cast<WindowInternal*>(glfwGetWindowUserPointer(window));

    windowInst->windowSize.x = static_cast<float>(width);
    windowInst->windowSize.y = static_cast<float>(height);
    glViewport(0, 0, width, height);

    for (auto& a : windowInst->windowResizeCallbackList)
        a(width, height);
}

void UImGui::WindowInternal::keyboardInputCallback(GLFWwindow* window, int key, int scanCode, int action, int mods) noexcept
{
    auto* wind = (WindowInternal*)glfwGetWindowUserPointer(window);
    wind->keys[key] = action;
}

void UImGui::WindowInternal::mouseKeyInputCallback(GLFWwindow* window, int button, int action, int mods) noexcept
{
    auto* wind = (WindowInternal*)glfwGetWindowUserPointer(window);
    wind->keys[button] = action;
}

void UImGui::WindowInternal::mouseCursorPositionCallback(GLFWwindow* window, double xpos, double ypos) noexcept
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

void UImGui::WindowInternal::scrollInputCallback(GLFWwindow* window, double xoffset, double yoffset) noexcept
{
    auto* windowInst = static_cast<WindowInternal*>(glfwGetWindowUserPointer(window));

    windowInst->scroll = { static_cast<float>(xoffset), static_cast<float>(yoffset) };
}

void UImGui::WindowInternal::windowPositionCallback(GLFWwindow* window, int xpos, int ypos) noexcept
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
        out = YAML::LoadFile("../Config/Core/Window.yaml");
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
        out = YAML::LoadFile("../Config/Core/Keybindings.yaml");
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

void UImGui::WindowInternal::close() noexcept
{
    glfwSetWindowShouldClose(windowMain, true);
}

void UImGui::WindowInternal::updateKeyState() noexcept
{
    for (auto& a : inputActionList)
    {
        if (!a.keyCodes.empty())
        {
            for (auto& f : a.keyCodes)
                if (keys[f] != keys[a.keyCodes[0]])
                    goto finish_inner_loop;
            a.state = keys[a.keyCodes[0]];
        }
finish_inner_loop:;
    }
}

void UImGui::WindowInternal::setIcon(UImGui::String name) noexcept
{
    GLFWimage images[1];
    images[0].pixels = stbi_load((UImGui::FString("../Content/") + name).c_str(), &images[0].width, &images[0].height, nullptr, 4);
    glfwSetWindowIcon(windowMain, 1, images);
    stbi_image_free(images[0].pixels);
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
#endif
}

void UImGui::WindowInternal::disableWindowMoving() noexcept
{
#ifdef GLFW_EXPOSE_NATIVE_X11

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

void UImGui::WindowInternal::setShowWindowInPager(bool bShowInPagerr) noexcept
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
#endif
}

void UImGui::WindowInternal::setShowWindowOnTaskbar(bool bShowOnTaskbarr) noexcept
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
#endif
}

void UImGui::WindowInternal::windowSizeCallback(GLFWwindow* window, int width, int height) noexcept
{
    auto* windowInst = static_cast<WindowInternal*>(glfwGetWindowUserPointer(window));
    windowInst->windowSizeInScreenCoords = { (float)width, (float)height };
    for (auto& a : windowInst->windowResizeInScreenCoordCallbackList)
        a(width, height);
}

void UImGui::WindowInternal::windowCloseCallback(GLFWwindow* window) noexcept
{
    auto* windowInst = static_cast<WindowInternal*>(glfwGetWindowUserPointer(window));
    for (auto& a : windowInst->windowCloseCallbackList)
        a();
}

void UImGui::WindowInternal::windowFocusCallback(GLFWwindow* window, int focused) noexcept
{
    auto* windowInst = static_cast<WindowInternal*>(glfwGetWindowUserPointer(window));
    for (auto& a : windowInst->windowFocusCallbackList)
        a(focused);
}

void UImGui::WindowInternal::windowIconifyCallback(GLFWwindow* window, int iconified) noexcept
{
    auto* windowInst = static_cast<WindowInternal*>(glfwGetWindowUserPointer(window));
    for (auto& a : windowInst->windowIconifiedCallbackList)
        a(iconified);
}

void UImGui::WindowInternal::windowContentScaleCallback(GLFWwindow* window, float x, float y) noexcept
{
    auto* windowInst = static_cast<WindowInternal*>(glfwGetWindowUserPointer(window));
    for (auto& a : windowInst->windowContentScaleChangeCallbackList)
        a({ x, y });
}

void UImGui::WindowInternal::windowRefreshCallback(GLFWwindow* window) noexcept
{
    auto* windowInst = static_cast<WindowInternal*>(glfwGetWindowUserPointer(window));
    for (auto& a : windowInst->windowRefreshCallbackList)
        a();
}

void UImGui::WindowInternal::windowMaximisedCallback(GLFWwindow* window, int maximised) noexcept
{
    auto* windowInst = static_cast<WindowInternal*>(glfwGetWindowUserPointer(window));
    for (auto& a : windowInst->windowMaximisedCallbackList)
        a(maximised);
}

void UImGui::WindowInternal::monitorCallback(GLFWmonitor* monitor, int event) noexcept
{
    auto dt = (Monitor*)glfwGetMonitorUserPointer(monitor);
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
}

void UImGui::WindowInternal::windowOSDragDropCallback(GLFWwindow* window, int count, const char** paths) noexcept
{
    auto* windowInst = static_cast<WindowInternal*>(glfwGetWindowUserPointer(window));
    windowInst->dragDropPaths.clear();

    for (int i = 0; i < count; i++)
        windowInst->dragDropPaths.emplace_back(paths[i]);
    for (auto& a : windowInst->dragDropPathCallbackList)
        a(windowInst->dragDropPaths);
}

void UImGui::WindowInternal::windowErrorCallback(int code, const char* description) noexcept
{
    Logger::log("Encountered GLFW window error, ", UVKLog::UVK_LOG_TYPE_ERROR, code, ": ", description);
    for (auto& a : Window::get().windowErrorCallbackList)
        a(code, description);
}

UImGui::Monitor::Monitor(GLFWmonitor* monitor) noexcept
{
    this->monitor = monitor;
    glfwSetMonitorUserPointer(this->monitor, (void*)this);
}

UImGui::FVector2 UImGui::Monitor::getPhysicalSize() noexcept
{
    int width = 0;
    int height = 0;
    glfwGetMonitorPhysicalSize(monitor, &width, &height);

    return UImGui::FVector2(static_cast<float>(width), static_cast<float>(height));
}

UImGui::FVector2 UImGui::Monitor::getContentScale() noexcept
{
    FVector2 f = {};
    glfwGetMonitorContentScale(monitor, &f.x, &f.y);
    return f;
}

UImGui::FVector2 UImGui::Monitor::getVirtualPosition() noexcept
{
    int x = 0;
    int y = 0;
    glfwGetMonitorPos(monitor, &x, &y);

    return UImGui::FVector2(static_cast<float>(x), static_cast<float>(y));
}

UImGui::FVector4 UImGui::Monitor::getWorkArea() noexcept
{
    int x = 0;
    int y = 0;
    int width = 0;
    int height = 0;

    glfwGetMonitorWorkarea(monitor, &x, &y, &width, &height);
    return UImGui::FVector4
    (
            static_cast<float>(x),static_cast<float>(y),
            static_cast<float>(width), static_cast<float>(height)
    );
}

UImGui::FString UImGui::Monitor::getName() noexcept
{
    return {glfwGetMonitorName(monitor) };
}

void UImGui::Monitor::pushEvent(const std::function<void(Monitor&, MonitorState)>& f) noexcept
{
    events.push_back(f);
}
