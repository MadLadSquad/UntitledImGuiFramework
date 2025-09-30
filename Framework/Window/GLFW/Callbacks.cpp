#include "WindowGLFW.hpp"
#include <GLFW/glfw3.h>

void UImGui::WindowGLFW::configureCallbacks() const noexcept
{
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
    glfwSetKeyCallback(window, keyboardInputCallback);
    glfwSetCursorPosCallback(window, mouseCursorPositionCallback);
    glfwSetMouseButtonCallback(window, mouseKeyInputCallback);
    glfwSetScrollCallback(window, scrollInputCallback);
    glfwSetWindowPosCallback(window, windowPositionCallback);

    glfwSetWindowSizeCallback(window, windowSizeCallback);
    glfwSetWindowCloseCallback(window, windowCloseCallback);
    glfwSetWindowFocusCallback(window, windowFocusCallback);
    glfwSetWindowIconifyCallback(window, windowIconifyCallback);
    glfwSetWindowContentScaleCallback(window, windowContentScaleCallback);
    glfwSetWindowRefreshCallback(window, windowRefreshCallback);
    glfwSetWindowMaximizeCallback(window, windowMaximisedCallback);

    //glfwSetMonitorCallback(monitorCallback);

    glfwSetDropCallback(window, windowOSDragDropCallback);
}

void UImGui::WindowGLFW::framebufferSizeCallback(GLFWwindow* window, const int width, const int height) noexcept
{
    auto* windowInst = static_cast<WindowGLFW*>(glfwGetWindowUserPointer(window));

    windowInst->windowSizeS.x = static_cast<float>(width);
    windowInst->windowSizeS.y = static_cast<float>(height);

    for (auto& a : windowInst->windowResizeCallbackList)
        a(width, height);
}

void UImGui::WindowGLFW::keyboardInputCallback(GLFWwindow* window, const int key, const int, const int action, int) noexcept
{
    auto* wind = CAST(WindowGLFW*, glfwGetWindowUserPointer(window));
    wind->keys[key] = static_cast<CKeyState>(action);
}

void UImGui::WindowGLFW::mouseKeyInputCallback(GLFWwindow* window, const int button, const int action, int) noexcept
{
    auto* wind = CAST(WindowGLFW*, glfwGetWindowUserPointer(window));
    wind->keys[button] = static_cast<CKeyState>(action);
}

void UImGui::WindowGLFW::mouseCursorPositionCallback(GLFWwindow* window, const double xpos, const double ypos) noexcept
{
    auto* windowInst = static_cast<WindowGLFW*>(glfwGetWindowUserPointer(window));

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

void UImGui::WindowGLFW::scrollInputCallback(GLFWwindow* window, const double xoffset, const double yoffset) noexcept
{
    auto* windowInst = static_cast<WindowGLFW*>(glfwGetWindowUserPointer(window));
    windowInst->scroll = { static_cast<float>(xoffset), static_cast<float>(yoffset) };
}

void UImGui::WindowGLFW::windowPositionCallback(GLFWwindow* window, const int xpos, const int ypos) noexcept
{
    auto* windowInst = static_cast<WindowGLFW*>(glfwGetWindowUserPointer(window));

    windowInst->windowLastPos.x = windowInst->windowCurrentPos.x;
    windowInst->windowLastPos.y = windowInst->windowCurrentPos.y;

    windowInst->windowCurrentPos.x = static_cast<float>(xpos);
    windowInst->windowCurrentPos.y = static_cast<float>(ypos);

    for (auto& a : windowInst->windowPositionChangeCallbackList)
        a({ static_cast<float>(xpos), static_cast<float>(ypos) });
}

void UImGui::WindowGLFW::windowSizeCallback(GLFWwindow* window, const int width, const int height) noexcept
{
    auto* windowInst = static_cast<WindowGLFW*>(glfwGetWindowUserPointer(window));
    windowInst->windowSizeInScreenCoords = { CAST(float, width), CAST(float, height) };
    for (auto& a : windowInst->windowResizeInScreenCoordCallbackList)
        a(width, height);
}

void UImGui::WindowGLFW::windowCloseCallback(GLFWwindow* window) noexcept
{
    for (auto& a : static_cast<WindowGLFW*>(glfwGetWindowUserPointer(window))->windowCloseCallbackList)
        a();
}

void UImGui::WindowGLFW::windowFocusCallback(GLFWwindow* window, const int focused) noexcept
{
    for (auto& a : static_cast<WindowGLFW*>(glfwGetWindowUserPointer(window))->windowFocusCallbackList)
        a(focused);
}

void UImGui::WindowGLFW::windowIconifyCallback(GLFWwindow* window, const int iconified) noexcept
{
    for (auto& a : static_cast<WindowGLFW*>(glfwGetWindowUserPointer(window))->windowIconifiedCallbackList)
        a(iconified);
}

void UImGui::WindowGLFW::windowContentScaleCallback(GLFWwindow* window, const float x, const float y) noexcept
{
    for (auto& a : static_cast<WindowGLFW*>(glfwGetWindowUserPointer(window))->windowContentScaleChangeCallbackList)
        a({ x, y });
}

void UImGui::WindowGLFW::windowRefreshCallback(GLFWwindow* window) noexcept
{
    for (auto& a : static_cast<WindowGLFW*>(glfwGetWindowUserPointer(window))->windowRefreshCallbackList)
        a();
}

void UImGui::WindowGLFW::windowMaximisedCallback(GLFWwindow* window, const int maximised) noexcept
{
    for (auto& a : static_cast<WindowGLFW*>(glfwGetWindowUserPointer(window))->windowMaximisedCallbackList)
        a(maximised);
}

void UImGui::WindowGLFW::windowOSDragDropCallback(GLFWwindow* window, const int count, const char** paths) noexcept
{
    const auto* windowInst = static_cast<WindowGLFW*>(glfwGetWindowUserPointer(window));
    for (auto& a : windowInst->dragDropPathCallbackList)
        for (int i = 0; i < count; i++)
            a(paths[i]);
}
