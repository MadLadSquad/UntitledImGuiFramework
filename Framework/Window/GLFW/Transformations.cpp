#include "WindowGLFW.hpp"
#include <GLFW/glfw3.h>

float UImGui::WindowGLFW::getAspectRatio() noexcept
{
    return windowSizeS.x / windowSizeS.y;
}

UImGui::FVector2 UImGui::WindowGLFW::getCurrentWindowPosition() noexcept
{
    return windowCurrentPos;
}

UImGui::FVector2 UImGui::WindowGLFW::getLastWindowPosition() noexcept
{
    return windowLastPos;
}

UImGui::FVector2 UImGui::WindowGLFW::getWindowPositionChange() noexcept
{
    return
    {
        windowCurrentPos.x - windowLastPos.x,
        windowCurrentPos.y - windowLastPos.y
    };
}

void UImGui::WindowGLFW::setCurrentWindowPosition(const FVector2 pos) noexcept
{
    windowCurrentPos = pos;
    glfwSetWindowPos(window, pos.x, pos.y);
}

void UImGui::WindowGLFW::pushWindowPositionChangeCallback(const std::function<void(FVector2)>& f) noexcept
{
    windowPositionChangeCallbackList.push_back(f);
}

UImGui::FVector2 UImGui::WindowGLFW::getWindowSize() noexcept
{
    return windowSizeS;
}

UImGui::FVector2& UImGui::WindowGLFW::getWindowSizeSetting() noexcept
{
    return windowSizeS;
}

void UImGui::WindowGLFW::setWindowSizeInScreenCoords(const FVector2 sz) noexcept
{
    windowSizeInScreenCoords = sz;
    glfwSetWindowSize(window, CAST(int, sz.x), CAST(int, sz.y));
}

UImGui::FVector2 UImGui::WindowGLFW::getWindowSizeInScreenCoords() noexcept
{
    return windowSizeInScreenCoords;
}

void UImGui::WindowGLFW::pushWindowResizedInScreenCoordsCallback(const std::function<void(int, int)>& f) noexcept
{
    windowResizeInScreenCoordCallbackList.push_back(f);
}

void UImGui::WindowGLFW::setWindowResizeable(const bool bResizeable) noexcept
{
    glfwSetWindowAttrib(window, GLFW_RESIZABLE, bResizeable);
}

bool& UImGui::WindowGLFW::getWindowResizeableSetting() noexcept
{
    return windowData.bResizeable;
}

bool UImGui::WindowGLFW::getWindowCurrentlyResizeable() noexcept
{
    return glfwGetWindowAttrib(window, GLFW_RESIZABLE);
}

void UImGui::WindowGLFW::pushWindowResizeCallback(const std::function<void(int, int)>& f) noexcept
{
    windowResizeCallbackList.push_back(f);
}

UImGui::FVector2 UImGui::WindowGLFW::getWindowContentScale() noexcept
{
    FVector2 ret;
    glfwGetWindowContentScale(window, &ret.x, &ret.y);
    return ret;
}

void UImGui::WindowGLFW::pushWindowContentScaleCallback(const std::function<void(FVector2)>& f) noexcept
{
    windowContentScaleChangeCallbackList.push_back(f);
}

void UImGui::WindowGLFW::setSizeLimits(const FVector2 min, const FVector2 max) noexcept
{
    glfwSetWindowSizeLimits(window, CAST(int, min.x), CAST(int, min.y), CAST(int, max.x), CAST(int, max.y));
}

void UImGui::WindowGLFW::setSizeLimitByAspectRatio(const FVector2 ratio) noexcept
{
    glfwSetWindowAspectRatio(window, CAST(int, ratio.x), CAST(int, ratio.y));
}

UImGui::FVector4& UImGui::WindowGLFW::getSizeLimits() noexcept
{
    return windowData.sizeLimits;
}

UImGui::FVector2& UImGui::WindowGLFW::getAspectRatioSizeLimits() noexcept
{
    return windowData.aspectRatioSizeLimit;
}
