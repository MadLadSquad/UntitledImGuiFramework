#include "ClientSideBar.hpp"
#include <imgui.h>
#include <Interfaces/WindowInterface.hpp>
#include <Components/Instance.hpp>

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

void UImGui::ClientSideBar::End(const ClientSideBarFlags flags, const FVector4 destructiveColour, const FVector4 destructiveColourActive) noexcept
{
    // Create an invisible button that fills up all available space but leaves enough for the buttons
    static float width = 0;
    ImGui::InvisibleButton("uimgui_internal_main_bar_spacing", { ImGui::GetContentRegionAvail().x - width, ImGui::GetFrameHeight() });
    const auto& style = ImGui::GetStyle();
    width = 0;

    ImGui::PushStyleColor(ImGuiCol_Button, style.Colors[ImGuiCol_MenuBarBg]); // Dear imgui does some fuckery when ImGui::BeginMainMenuBar is called
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, style.Colors[ImGuiCol_HeaderActive]);
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, style.Colors[ImGuiCol_HeaderHovered]);

    if (flags & UIMGUI_CLIENT_SIDE_BAR_FLAG_MINIMISE_BUTTON)
        renderMinimiseButton(width, style);
    if (flags & UIMGUI_CLIENT_SIDE_BAR_FLAG_MAXIMISE_BUTTON)
        renderMaximiseButton(width, style);
    if (flags & UIMGUI_CLIENT_SIDE_BAR_FLAG_CLOSE_BUTTON)
        renderCloseButton(width, style, destructiveColour, destructiveColourActive);

    ImGui::PopStyleColor(3);
    ImGui::EndGroup();

    // Mouse dragging code courtesy of https://github.com/ashifolfi/lynx-animator/blob/main/src/MainWindow.cpp
    static bool bDragging = false;
    if (flags & UIMGUI_CLIENT_SIDE_BAR_FLAG_MOVEABLE && ((ImGui::IsMouseDown(ImGuiMouseButton_Left) && ImGui::IsItemActive()) || bDragging))
    {
        if (ImGui::IsMouseDragging(ImGuiMouseButton_Left))
        {
            bDragging = true;
            const auto pos = Window::getCurrentWindowPosition();
            Window::setCurrentWindowPosition({ pos.x + ImGui::GetIO().MouseDelta.x, pos.y + ImGui::GetIO().MouseDelta.y });
        }
        else
            bDragging = false;
    }
}

void UImGui::ClientSideBar::renderMinimiseButton(float& width, const ImGuiStyle& style) noexcept
{
    if (ImGui::SmallButton(" ##uimgui_internal_invisible_minimise_button"))
        Window::iconifyWindow();
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
        bWindowed = !Window::getWindowCurrentlyMaximised();
        bFirst = false;
    }

    if (ImGui::SmallButton(" ##uimgui_internal_invisible_maximise_button"))
    {
        if (bWindowed)
            Window::maximiseWindow();
        else
            Window::restoreWindowState();
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

void UImGui::ClientSideBar::renderCloseButton(float& width, const ImGuiStyle& style, FVector4 destructiveColour, FVector4 destructiveColourActive) noexcept
{
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImGui::ColorConvertFloat4ToU32({ destructiveColour.x, destructiveColour.y, destructiveColour.z, destructiveColour.w }));
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImGui::ColorConvertFloat4ToU32({ destructiveColourActive.x, destructiveColourActive.y, destructiveColourActive.z, destructiveColourActive.w }));

    if (ImGui::SmallButton(" ##uimgui_internal_invisible_close_button"))
        Instance::shutdown();
    UPDATE_PADDING;
    ADD_PADDING_TO_ITEM_RECT(min, max, padding);

    auto* drawList = ImGui::GetWindowDrawList();
    drawList->AddLine(min, max, ImGui::ColorConvertFloat4ToU32(style.Colors[ImGuiCol_Text]));
    drawList->AddLine({ min.x, max.y }, { max.x, min.y }, ImGui::ColorConvertFloat4ToU32(style.Colors[ImGuiCol_Text]));

    ImGui::PopStyleColor(2);
}
