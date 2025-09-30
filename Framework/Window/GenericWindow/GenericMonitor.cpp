#include "GenericMonitor.hpp"
#include "GenericWindow.hpp"
#include <Core/Interfaces/WindowInterface.hpp>

UImGui::FVector4 UImGui::Monitor::getWorkArea() noexcept
{
#ifndef __EMSCRIPTEN__
    return Window::get()->monitor->getWorkArea(data);
#else
    return FVector4{ 0.0f, 0.0f, 0.0f, 0.0f };
#endif
}

double UImGui::Monitor::getContentScale() noexcept
{
#ifndef __EMSCRIPTEN__
    return Window::get()->monitor->getContentScale(data);
#else
    return 1.0;
#endif
}

UImGui::String UImGui::Monitor::getName() noexcept
{
#ifndef __EMSCRIPTEN__
    return Window::get()->monitor->getName(data);
#else
    return "";
#endif
}

UImGui::FVector2 UImGui::Monitor::getSize() noexcept
{
#ifndef __EMSCRIPTEN__
    return Window::get()->monitor->getSize(data);
#else
    return FVector2{ 0.0f, 0.0f };
#endif
}

float UImGui::Monitor::getPixelDensity() noexcept
{
#ifndef __EMSCRIPTEN__
    return Window::get()->monitor->getPixelDensity(data);
#else
    return 1.0f;
#endif
}

UImGui::MonitorData& UImGui::Monitor::get() noexcept
{
    return data;
}
