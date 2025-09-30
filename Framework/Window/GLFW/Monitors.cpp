#include "WindowGLFW.hpp"
#include <GLFW/glfw3.h>

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