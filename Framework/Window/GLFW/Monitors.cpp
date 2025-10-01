#include "WindowGLFW.hpp"
#include <GLFW/glfw3.h>
#ifdef _WIN32
    #define GLFW_EXPOSE_NATIVE_WIN32
#elif __APPLE__
    #define GLFW_EXPOSE_NATIVE_COCOA
#elif !__EMSCRIPTEN__
    #if __has_include(<wayland-client.h>)
        #define GLFW_EXPOSE_NATIVE_WAYLAND
    #endif
    #if __has_include(<X11/Xatom.h>)
        #define GLFW_EXPOSE_NATIVE_X11
        #include <X11/Xatom.h>
        #define _NET_WM_STATE_ADD 1
    #endif
#endif
#include <GLFW/glfw3native.h>

UImGui::Monitor UImGui::WindowGLFW::getWindowMonitor() noexcept
{
    Monitor m{};
#ifndef __EMSCRIPTEN__
    m.get().id = reinterpret_cast<uintptr_t>(glfwGetWindowMonitor(window));
#endif
    return m;
}

UImGui::Monitor UImGui::WindowGLFW::getPrimaryMonitor() noexcept
{
    Monitor m{};
#ifndef __EMSCRIPTEN__
    m.get().id = reinterpret_cast<uintptr_t>(glfwGetPrimaryMonitor());
#endif
    return m;
}

const UImGui::TVector<UImGui::Monitor>& UImGui::WindowGLFW::getMonitors() noexcept
{
#ifndef __EMSCRIPTEN__
    int count = 0;
    GLFWmonitor** glfwMonitors = glfwGetMonitors(&count);
    monitors.clear();
    for (int i = 0; i < count; i++)
    {
        auto m = monitors.emplace_back();
        m.get().id = reinterpret_cast<uintptr_t>(glfwMonitors[i]);
    }
#endif
    return monitors;
}

UImGui::FVector4 UImGui::MonitorGLFW::getWorkArea(MonitorData& data) noexcept
{
    int x = 0, y = 0, w = 0, h = 0;
#ifndef __EMSCRIPTEN__
    glfwGetMonitorWorkarea(reinterpret_cast<GLFWmonitor*>(data.id), &x, &y, &w, &h);
#endif
    return { CAST(float, x), CAST(float, y), CAST(float, w), CAST(float, h) };
}

double UImGui::MonitorGLFW::getContentScale(MonitorData& data) noexcept
{
    float x = 1.0f, y = 1.0f;
#ifndef __EMSCRIPTEN__
    glfwGetMonitorContentScale(reinterpret_cast<GLFWmonitor*>(data.id), &x, &y);
#endif
    return x / y;
}

UImGui::String UImGui::MonitorGLFW::getName(MonitorData& data) noexcept
{
#ifndef __EMSCRIPTEN__
    return glfwGetMonitorName(reinterpret_cast<GLFWmonitor*>(data.id));
#else
    return "";
#endif
}

UImGui::FVector2 UImGui::MonitorGLFW::getSize(MonitorData& data) noexcept
{
    const auto area = getWorkArea(data);
    return { CAST(float, area.z), CAST(float, area.w) };
}

float UImGui::MonitorGLFW::getPixelDensity(MonitorData& data) noexcept
{
    return 1.0f;
}

void* UImGui::MonitorGLFW::getPlatformHandle(MonitorData& data) noexcept
{
#ifdef __EMSCRIPTEN__
    return (void*)"#canvas";
#elifdef _WIN32
    return reinterpret_cast<void*>(glfwGetWin32Monitor(reinterpret_cast<GLFWmonitor*>(data.id)));
#elifdef __APPLE__
    return reinterpret_cast<void*>(glfwGetCocoaMonitor(reinterpret_cast<GLFWmonitor*>(data.id)));
#else
    if (glfwGetPlatform() == GLFW_PLATFORM_WAYLAND)
        return glfwGetWaylandMonitor(reinterpret_cast<GLFWmonitor*>(data.id));
    return reinterpret_cast<void*>(glfwGetX11Monitor(reinterpret_cast<GLFWmonitor*>(data.id)));
#endif
}
