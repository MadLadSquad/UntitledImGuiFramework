#include "VKUtility.hpp"

bool UImGui::QueueFamilyIndices::valid() const noexcept
{
    return graphicsFamily >= 0 && presentationFamily >= 0;
}
