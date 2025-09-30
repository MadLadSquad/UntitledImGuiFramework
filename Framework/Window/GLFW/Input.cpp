#include "WindowGLFW.hpp"
#include <GLFW/glfw3.h>

CKeyState UImGui::WindowGLFW::getKey(const CKeys key) noexcept
{
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
