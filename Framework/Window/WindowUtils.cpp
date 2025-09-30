#include "WindowUtils.hpp"
#include <Core/Interfaces/WindowInterface.hpp>

bool UImGui::WindowUtils::shouldRender() noexcept
{
    return Window::get()->shouldRender();
}

void UImGui::WindowUtils::pollEvents(double& now, double& deltaTime, double& lastTime) noexcept
{
    return Window::get()->pollEvents(now, deltaTime, lastTime);
}

void UImGui::WindowUtils::waitEventsTimeout(const double timeout) noexcept
{
    return Window::get()->waitEventsTimeout(timeout);
}

void UImGui::WindowUtils::waitEvents() noexcept
{
    return Window::get()->waitEvents();
}
