#include "WindowGLFW.hpp"
#include <GLFW/glfw3.h>

CKeyState UImGui::WindowGLFW::getKey(const CKeys key) noexcept
{
    // CKeys is a plain C enum, so nothing stops a caller from passing an arbitrary int through here
    if (key < 0 || key >= Keys_COUNT)
        return KeyStateReleased;

    return keys[key];
}

void UImGui::WindowGLFW::setCursorVisibility(const CursorVisibilityState visibility) noexcept
{
    glfwSetInputMode(window, GLFW_CURSOR, visibility);
}

void UImGui::WindowGLFW::setRawMouseMotion(const bool bEnable) noexcept
{
    if (glfwRawMouseMotionSupported())
        glfwSetInputMode(window, GLFW_RAW_MOUSE_MOTION, bEnable);
}

bool UImGui::WindowGLFW::getRawMouseMotion() noexcept
{
    return glfwGetInputMode(window, GLFW_RAW_MOUSE_MOTION);
}
