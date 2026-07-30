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

    // GLFW reports GLFW_KEY_UNKNOWN(-1) for any physical key it has no keycode for - a media key, a vendor key, an
    // unusual layout - which used to be written straight into keys[-1]. Those all funnel into the Keys_UnknownKey slot
    // the enum already reserves for them instead. The upper bound is checked too, because GLFW's keycode space is not
    // the framework's and nothing else guarantees the two stay in step.
    const int index = key < 0 || key >= Keys_COUNT ? Keys_UnknownKey : key;
    wind->keys[index] = static_cast<CKeyState>(action);
}

void UImGui::WindowGLFW::mouseKeyInputCallback(GLFWwindow* window, const int button, const int action, int) noexcept
{
    auto* wind = CAST(WindowGLFW*, glfwGetWindowUserPointer(window));
    if (button < 0 || button >= Keys_COUNT)
        return;

    wind->keys[button] = static_cast<CKeyState>(action);
}

void UImGui::WindowGLFW::mouseCursorPositionCallback(GLFWwindow* window, const double xpos, const double ypos) noexcept
{
    auto* windowInst = static_cast<WindowGLFW*>(glfwGetWindowUserPointer(window));

    static bool bFirst = true;
    if (bFirst)
    {
        windowInst->mouseLastPos = { static_cast<float>(xpos), static_cast<float>(ypos) };
        windowInst->mousePos = windowInst->mouseLastPos;
        bFirst = false;
    }

    // mousePos holds the previous position until it is rotated below, which is what mouseLastPos used to be doing here -
    // so the offset comes out identical. The difference is that the two fields now mean what their names say:
    // getCurrentMousePosition() reads mousePos, which nothing in the codebase ever wrote, so it always returned {0,0};
    // getLastMousePosition() reads mouseLastPos, which was being overwritten with the current position and therefore
    // always agreed with it.
    windowInst->mouseOffset.x = static_cast<float>(xpos) - windowInst->mousePos.x;
    windowInst->mouseOffset.y = windowInst->mousePos.y - static_cast<float>(ypos);

    windowInst->mouseLastPos = windowInst->mousePos;
    windowInst->mousePos = { static_cast<float>(xpos), static_cast<float>(ypos) };
}

void UImGui::WindowGLFW::scrollInputCallback(GLFWwindow* window, const double xoffset, const double yoffset) noexcept
{
    auto* windowInst = static_cast<WindowGLFW*>(glfwGetWindowUserPointer(window));
    windowInst->bScrollEventReceived = true;

    if (xoffset == 0)
    {
        windowInst->keys[Keys_ScrollLeft] = KeyStateReleased;
        windowInst->keys[Keys_ScrollRight] = KeyStateReleased;
    }
    else if (xoffset > 0)
    {
        windowInst->keys[Keys_ScrollRight] = KeyStatePressed;
        windowInst->keys[Keys_ScrollLeft] = KeyStateReleased;
    }
    else if (xoffset < 0)
    {
        windowInst->keys[Keys_ScrollRight] = KeyStateReleased;
        windowInst->keys[Keys_ScrollLeft] = KeyStatePressed;
    }

    if (yoffset == 0)
    {
        windowInst->keys[Keys_ScrollUp] = KeyStateReleased;
        windowInst->keys[Keys_ScrollDown] = KeyStateReleased;
    }
    else if (yoffset > 0)
    {
        windowInst->keys[Keys_ScrollUp] = KeyStatePressed;
        windowInst->keys[Keys_ScrollDown] = KeyStateReleased;
    }
    else if (yoffset < 0)
    {
        windowInst->keys[Keys_ScrollDown] = KeyStatePressed;
        windowInst->keys[Keys_ScrollUp] = KeyStateReleased;
    }


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
