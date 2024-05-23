#include "ClientSideBar.hpp"
#include <imgui.h>
#include <Interfaces/WindowInterface.hpp>
#include <Instance.hpp>

#define UPDATE_PADDING (width += ImGui::GetItemRectSize().x + style.WindowPadding.x)
#define ADD_PADDING_TO_ITEM_RECT(x, y, z) auto (x) = ImGui::GetItemRectMin(); \
auto (y) = ImGui::GetItemRectMax();                                           \
auto (z) = style.FramePadding;                                                \
(x) += (z);                                                                   \
(y) -= (z);

void UImGui::ClientSideBar::Begin() noexcept
{
    ImGui::BeginGroup();
}

void UImGui::ClientSideBar::End(float deltaTime, UImGui::ClientSideBarFlags flags, FVector4 destructiveColor, FVector4 destructiveColorActive) noexcept
{
    // Create an invisible button that fills up all available space but leaves enough for the buttons
    static float width = 0;
    ImGui::InvisibleButton("uimgui_internal_main_bar_spacing", { ImGui::GetContentRegionAvail().x - width, ImGui::GetFrameHeight() });
    auto& style = ImGui::GetStyle();
    width = 0;

    ImGui::PushStyleColor(ImGuiCol_Button, style.Colors[ImGuiCol_MenuBarBg]); // Dear imgui does some fuckery when ImGui::BeginMainMenuBar is called
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, style.Colors[ImGuiCol_HeaderActive]);
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, style.Colors[ImGuiCol_HeaderHovered]);

    if (flags & UIMGUI_CLIENT_SIDE_BAR_FLAG_MINIMISE_BUTTON)
        renderMinimiseButton(width, style);
    if (flags & UIMGUI_CLIENT_SIDE_BAR_FLAG_MAXIMISE_BUTTON)
        renderMaximiseButton(width, style);
    if (flags & UIMGUI_CLIENT_SIDE_BAR_FLAG_CLOSE_BUTTON)
        renderCloseButton(width, style, destructiveColor, destructiveColorActive);

    ImGui::PopStyleColor(3);
    ImGui::EndGroup();
    if (flags & UIMGUI_CLIENT_SIDE_BAR_FLAG_MOVEABLE && ImGui::IsItemHovered() && UImGui::Input::getKey(Keys_MouseButtonLeft))
    {
        // TODO: Implement
    }
}

void UImGui::ClientSideBar::renderMinimiseButton(float& width, const ImGuiStyle& style) noexcept
{
    if (ImGui::SmallButton(" ##uimgui_internal_invisible_minimise_button"))
        UImGui::Window::iconifyWindow();
    UPDATE_PADDING;
    ADD_PADDING_TO_ITEM_RECT(min, max, padding);

    auto* drawList = ImGui::GetWindowDrawList();
    drawList->AddLine({ min.x, max.y }, max, ImGui::ColorConvertFloat4ToU32(style.Colors[ImGuiCol_Text]));
}

void UImGui::ClientSideBar::renderMaximiseButton(float& width, const ImGuiStyle& style) noexcept
{
    static bool bFirst = true;
    static bool bWindowed = false;
    if (bFirst)
    {
        bWindowed = !UImGui::Window::getWindowCurrentlyMaximised();
        bFirst = false;
    }

    if (ImGui::SmallButton(" ##uimgui_internal_invisible_maximise_button"))
    {
        if (bWindowed)
            UImGui::Window::maximiseWindow();
        else
            UImGui::Window::restoreWindowState();
        bWindowed = !bWindowed;
    }
    UPDATE_PADDING;
    ADD_PADDING_TO_ITEM_RECT(min, max, padding);

    auto* drawList = ImGui::GetWindowDrawList();
    drawList->AddLine(min, { min.x, max.y }, ImGui::ColorConvertFloat4ToU32(style.Colors[ImGuiCol_Text]));
    drawList->AddLine(min, { max.x, min.y }, ImGui::ColorConvertFloat4ToU32(style.Colors[ImGuiCol_Text]));
    drawList->AddLine(max, { min.x, max.y }, ImGui::ColorConvertFloat4ToU32(style.Colors[ImGuiCol_Text]));
    drawList->AddLine(max, { max.x, min.y }, ImGui::ColorConvertFloat4ToU32(style.Colors[ImGuiCol_Text]));
}

void UImGui::ClientSideBar::renderCloseButton(float& width, const ImGuiStyle& style, FVector4 destructiveColor, FVector4 destructiveColorActive) noexcept
{
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImGui::ColorConvertFloat4ToU32({ destructiveColor.x, destructiveColor.y, destructiveColor.z, destructiveColor.w }));
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImGui::ColorConvertFloat4ToU32({ destructiveColorActive.x, destructiveColorActive.y, destructiveColorActive.z, destructiveColorActive.w }));

    if (ImGui::SmallButton(" ##uimgui_internal_invisible_close_button"))
        UImGui::Instance::shutdown();
    UPDATE_PADDING;
    ADD_PADDING_TO_ITEM_RECT(min, max, padding);

    auto* drawList = ImGui::GetWindowDrawList();
    drawList->AddLine(min, max, ImGui::ColorConvertFloat4ToU32(style.Colors[ImGuiCol_Text]));
    drawList->AddLine({ min.x, max.y }, { max.x, min.y }, ImGui::ColorConvertFloat4ToU32(style.Colors[ImGuiCol_Text]));

    ImGui::PopStyleColor(2);
}
