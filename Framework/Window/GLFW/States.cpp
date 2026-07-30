#include "WindowGLFW.hpp"
#include <imgui.h>
#include <GLFW/glfw3.h>

void UImGui::WindowGLFW::focusWindow() noexcept
{
    glfwFocusWindow(window);
}

bool UImGui::WindowGLFW::getWindowFullscreen() noexcept
{
    return getWindowMonitor().get().id;
}

bool& UImGui::WindowGLFW::getWindowFullscreenSetting() noexcept
{
    return windowData.fullscreen;
}

void UImGui::WindowGLFW::setWindowFullscreen(const bool bFullscreen) noexcept
{
    GLFWmonitor* current = glfwGetWindowMonitor(window);
    if (bFullscreen == (current != nullptr))
        return;

    if (bFullscreen)
    {
        // Remembered in screen coordinates, which is what glfwSetWindowMonitor expects back. windowSizeS is the
        // framebuffer size and is not interchangeable with it on a scaled display.
        glfwGetWindowPos(window, &windowedRect[0], &windowedRect[1]);
        glfwGetWindowSize(window, &windowedRect[2], &windowedRect[3]);

        GLFWmonitor* monitor = glfwGetPrimaryMonitor();
        if (monitor == nullptr)
        {
            Logger::log("Couldn't switch to fullscreen because no monitor was found!", ULOG_LOG_TYPE_WARNING);
            return;
        }

        const GLFWvidmode* mode = glfwGetVideoMode(monitor);
        if (mode == nullptr)
        {
            Logger::log("Couldn't switch to fullscreen because the monitor's video mode couldn't be queried!", ULOG_LOG_TYPE_WARNING);
            return;
        }

        glfwSetWindowMonitor(window, monitor, 0, 0, mode->width, mode->height, mode->refreshRate);
    }
    else
    {
        // A window created fullscreen has no windowed geometry to go back to, so fall back to the configured size and
        // let the window manager place it
        if (windowedRect[2] <= 0 || windowedRect[3] <= 0)
        {
            windowedRect[2] = CAST(int, windowSizeS.x);
            windowedRect[3] = CAST(int, windowSizeS.y);
        }

        glfwSetWindowMonitor(window, nullptr, windowedRect[0], windowedRect[1], windowedRect[2], windowedRect[3], GLFW_DONT_CARE);
    }
}

bool& UImGui::WindowGLFW::getWindowFocusedSetting() noexcept
{
    return windowData.bFocused;
}

bool UImGui::WindowGLFW::getWindowCurrentlyFocused() noexcept
{
    return glfwGetWindowAttrib(window, GLFW_FOCUSED);
}

void UImGui::WindowGLFW::pushWindowFocusCallback(const std::function<void(bool)>& f) noexcept
{
    windowFocusCallbackList.push_back(f);
}

void UImGui::WindowGLFW::iconifyWindow() noexcept
{
    glfwIconifyWindow(window);
}

void UImGui::WindowGLFW::restoreWindowState() noexcept
{
    glfwRestoreWindow(window);
}

void UImGui::WindowGLFW::pushWindowIconifyCallback(const std::function<void(bool)>& f) noexcept
{
    windowIconifiedCallbackList.push_back(f);
}

bool UImGui::WindowGLFW::getWindowIconified() noexcept
{
    return glfwGetWindowAttrib(window, GLFW_ICONIFIED);
}

bool UImGui::WindowGLFW::getCurrentWindowDecoratedState() noexcept
{
    return glfwGetWindowAttrib(window, GLFW_DECORATED);
}

bool& UImGui::WindowGLFW::getWindowDecoratedSetting() noexcept
{
    return windowData.bDecorated;
}

void UImGui::WindowGLFW::setWindowDecorated(const bool bDecorated) noexcept
{
    glfwSetWindowAttrib(window, GLFW_DECORATED, bDecorated);
}

UImGui::FVector4 UImGui::WindowGLFW::getWindowDecorationFrameDistances() noexcept
{
    int x = 0, y = 0, z = 0, w = 0;
    glfwGetWindowFrameSize(window, &x, &y, &z, &w);
    const FVector4 val = { CAST(float, x), CAST(float, y), CAST(float, z), CAST(float, w) };
    return val;
}

void UImGui::WindowGLFW::pushWindowRefreshCallback(const std::function<void()>& f) noexcept
{
    windowRefreshCallbackList.push_back(f);
}

void UImGui::WindowGLFW::maximiseWindow() noexcept
{
    glfwMaximizeWindow(window);
}

bool& UImGui::WindowGLFW::getWindowMaximisedSetting() noexcept
{
    return windowData.bMaximised;
}

void UImGui::WindowGLFW::pushWindowMaximiseCallback(const std::function<void(bool)>& f) noexcept
{
    windowMaximisedCallbackList.push_back(f);
}

bool UImGui::WindowGLFW::getWindowCurrentlyMaximised() noexcept
{
    return glfwGetWindowAttrib(window, GLFW_MAXIMIZED);
}

void UImGui::WindowGLFW::requestWindowAttention() noexcept
{
    glfwRequestWindowAttention(window);
}

void UImGui::WindowGLFW::hideWindow() noexcept
{
    glfwHideWindow(window);
}

void UImGui::WindowGLFW::showWindow() noexcept
{
    glfwShowWindow(window);
}

bool& UImGui::WindowGLFW::getWindowHiddenSetting() noexcept
{
    return windowData.bHidden;
}

bool UImGui::WindowGLFW::getWindowCurrentlyHidden() noexcept
{
    return !glfwGetWindowAttrib(window, GLFW_VISIBLE);
}

void UImGui::WindowGLFW::saveSettings(const bool bSaveKeybinds) noexcept
{
    GenericWindow::saveSettings(bSaveKeybinds);
}

void UImGui::WindowGLFW::refreshSettings() noexcept
{
    setTitle(windowData.name.c_str());
    setIcon(windowData.iconLocation.c_str());

    setWindowSizeInScreenCoords(windowSizeS);
    setWindowFullscreen(windowData.fullscreen);
    setWindowResizeable(windowData.bResizeable);

    setWindowSurfaceTransparent(windowData.bSurfaceTransparent);
    if (windowData.bSurfaceTransparent)
        glfwSetWindowOpacity(window, ImGui::GetStyle().Colors[ImGuiCol_WindowBg].w);

    windowData.bHidden ? hideWindow() : showWindow();
    if (windowData.bFocused)
        focusWindow();

    setSizeLimitByAspectRatio(windowData.aspectRatioSizeLimit);
    const auto sizeLimits = windowData.sizeLimits;
    setSizeLimits({ sizeLimits.x, sizeLimits.y }, { sizeLimits.z, sizeLimits.w });

    setWindowDecorated(windowData.bDecorated);
    if (windowData.bMaximised)
        maximiseWindow();
    else
        restoreWindowState();
}

void UImGui::WindowGLFW::close() noexcept
{
    glfwSetWindowShouldClose(window, true);
}

void UImGui::WindowGLFW::pushWindowCloseCallback(const std::function<void()>& f) noexcept
{
    windowCloseCallbackList.push_back(f);
}

bool UImGui::WindowGLFW::getWindowSurfaceTransparent() noexcept
{
    // The real state of the framebuffer, which is decided at creation time and cannot change afterwards. It is deliberately
    // not the same thing as getWindowSurfaceTransparentSetting(), which is the requested value that gets saved to config
    return glfwGetWindowAttrib(window, GLFW_TRANSPARENT_FRAMEBUFFER);
}

void UImGui::WindowGLFW::setWindowSurfaceTransparent(const bool bTransparent) noexcept
{
    // Setting the surface transparency settings is only possible during the window creation
    // phase and is controlled by the Window.yaml setting
}

bool& UImGui::WindowGLFW::getWindowSurfaceTransparentSetting() noexcept
{
    return windowData.bSurfaceTransparent;
}

void UImGui::WindowGLFW::pushWindowOSDragDropCallback(const std::function<void(const FString&)>& f) noexcept
{
    dragDropPathCallbackList.push_back(f);
}
