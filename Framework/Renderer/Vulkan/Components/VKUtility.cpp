#include "VKUtility.hpp"
#ifndef __EMSCRIPTEN__
bool UImGui::QueueFamilyIndices::valid() const noexcept
{
    return graphicsFamily >= 0 && presentationFamily >= 0;
}
#endif