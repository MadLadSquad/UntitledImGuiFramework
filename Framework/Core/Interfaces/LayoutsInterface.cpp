#include "LayoutsInterface.hpp"
#include "WindowInterface.hpp"
#include "imgui.h"

bool& UImGui::Layouts::getLoadLayout() noexcept
{
    return Window::get()->windowData.bLoadLayout;
}

bool& UImGui::Layouts::getSaveLayout() noexcept
{
    return Window::get()->windowData.bSaveLayout;
}

UImGui::FString& UImGui::Layouts::layoutLocation() noexcept
{
    return Window::get()->windowData.layoutLocation;
}

void UImGui::Layouts::loadLayout(const String layout) noexcept
{
    ImGui::LoadIniSettingsFromDisk(layout);
}

void UImGui::Layouts::saveLayout(const String layout) noexcept
{
    ImGui::SaveIniSettingsToDisk(layout);
}
