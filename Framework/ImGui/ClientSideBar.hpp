#pragma once
#include <C/ImGui/CClientSideBar.h>
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

        // Set the client-side bar's flags. Note that we already default to UIMGUI_CLIENT_SIDE_BAR_FLAG_ALL so for most
        // cases calling this function will not be necessary
        // Event Safety - Any time
        static void SetFlags(ClientSideBarFlags flags) noexcept;

        // Starts rendering the automatic main client-side bar. For more control consider using the *Manual* functions
        // Event Safety - Tick
        static bool Begin() noexcept;

        // Finishes rendering the automatic main client-side bar. For more control consider using the *Manual* functions
        // The function needs to be called with the result of the previous call for it to terminate successfully
        // Event Safety - Tick
        static void End(bool bRendered, FVector4 destructiveColour = { 1.0, 0.482, 0.388f, 1.0f }, FVector4 destructiveColourActive = { 0.753f, 0.110f, 0.157f, 1.0f }) noexcept;

        // Sets up the style for the bar before starting to render it.
        // Event Safety - Tick
        static void BeginManualStyle() noexcept;

        // Pops the style for the bar after rendering.
        // Event Safety - Tick
        static void EndManualStyle() noexcept;

        // Starts rendering the client-side bar. Make sure to call BeginManualStyle before it.
        // Event Safety - Tick
        static void BeginManualRender() noexcept;

        // Finishes rendering the bar and commits the result. Make sure to call EndManualStyle after it.
        // Event Safety - Tick
        static void EndManualRender(FVector4 destructiveColour = { 1.0, 0.482, 0.388f, 1.0f }, FVector4 destructiveColourActive = { 0.753f, 0.110f, 0.157f, 1.0f }) noexcept;
    private:
        static ClientSideBarFlags& getFlags();

        static void renderMinimiseButton(float& width, const ImGuiStyle& style) noexcept;
        static void renderMaximiseButton(float& width, const ImGuiStyle& style) noexcept;
        static void renderCloseButton(float& width, const ImGuiStyle& style, FVector4 destructiveColour, FVector4 destructiveColourActive) noexcept;
    };
}