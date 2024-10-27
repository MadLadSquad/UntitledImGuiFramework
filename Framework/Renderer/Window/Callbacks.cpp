#include "Window.hpp"
#include <GLFW/glfw3.h>
#include <Interfaces/RendererInterface.hpp>
#include <Interfaces/WindowInterface.hpp>
#include <Defines.hpp>

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
    else
        Renderer::get().vulkan.draw.bRebuildSwapchain = true;

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
#ifndef DEVELOPMENT
    if (code != GLFW_FEATURE_UNAVAILABLE)
#endif
    Logger::log("Encountered GLFW window error, ", ULOG_LOG_TYPE_ERROR, code, ": ", description);
    for (auto& a : Window::get().windowErrorCallbackList)
        a(code, description);
}