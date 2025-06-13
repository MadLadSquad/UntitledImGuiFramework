#include "CLayoutsInterface.h"
#include <Interfaces/LayoutsInterface.hpp>

bool* UImGui_Layouts_getLoadLayout()
{
    return &UImGui::Layouts::getLoadLayout();
}

bool* UImGui_Layouts_getSaveLayout()
{
    return &UImGui::Layouts::getSaveLayout();
}

UImGui_String UImGui_Layouts_layoutLocation()
{
    return UImGui::Layouts::layoutLocation().c_str();
}

void UImGui_Layouts_loadLayout(const UImGui_String layout)
{
    UImGui::Layouts::loadLayout(layout);
}

void UImGui_Layouts_saveLayout(const UImGui_String layout)
{
    UImGui::Layouts::saveLayout(layout);
}