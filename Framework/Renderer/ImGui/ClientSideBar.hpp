#pragma once
#include <C/Rendering/CClientSideBar.h>
#include <Types.hpp>

struct ImGuiStyle;

namespace UImGui
{
    typedef UImGui_ClientSideBarFlags ClientSideBarFlags;

    class UIMGUI_PUBLIC_API ClientSideBar
    {
    public:
        ClientSideBar() = delete;
        ClientSideBar(const ClientSideBar&) = delete;
        void operator=(ClientSideBar const&) = delete;

        // Initialises the client-side bar
        // Event Safety - Post-begin
        static void Begin() noexcept;

        // Renders the bar
        // Event Safety - Post-begin
        static void End(float deltaTime, ClientSideBarFlags flags = UIMGUI_CLIENT_SIDE_BAR_FLAG_ALL, FVector4 destructiveColor = { 0.753f, 0.110f, 0.157f, 1.0f }, FVector4 destructiveColorActive = { 0.972f, 0.894f, 0.360f, 1.0f }) noexcept;
    private:
        static void renderMinimiseButton(float& width, const ImGuiStyle& style) noexcept;
        static void renderMaximiseButton(float& width, const ImGuiStyle& style) noexcept;
        static void renderCloseButton(float& width, const ImGuiStyle& style, FVector4 destructiveColor, FVector4 destructiveColorActive) noexcept;
    };
}