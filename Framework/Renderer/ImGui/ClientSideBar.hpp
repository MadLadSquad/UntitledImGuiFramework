#pragma once
#include <C/Rendering/CClientSideBar.h>

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
        static void End(float deltaTime, ClientSideBarFlags flags = UIMGUI_CLIENT_SIDE_BAR_FLAG_ALL) noexcept;
    private:
        static void renderMinimiseButton(float& width, const ImGuiStyle& style) noexcept;
        static void renderMaximiseButton(float& width, const ImGuiStyle& style) noexcept;
        static void renderCloseButton(float& width, const ImGuiStyle& style) noexcept;
    };
}