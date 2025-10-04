#include "CWindowUtils.h"
#include <Window/WindowUtils.hpp>

bool UImGui_WindowUtils_shouldRender()
{
    return UImGui::WindowUtils::shouldRender();
}

void UImGui_WindowUtils_pollEvents(double* now, double* deltaTime, double* lastTime)
{
    UImGui::WindowUtils::pollEvents(*now, *deltaTime, *lastTime);
}

void UImGui_WindowUtils_waitEventsTimeout(const double timeout)
{
    UImGui::WindowUtils::waitEventsTimeout(timeout);
}

void UImGui_WindowUtils_waitEvents()
{
    UImGui::WindowUtils::waitEvents();
}
