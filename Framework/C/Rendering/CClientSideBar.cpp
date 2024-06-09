#include "CClientSideBar.h"
#include <ImGui/ClientSideBar.hpp>

void UImGui_ClientSideBar_Begin()
{
    UImGui::ClientSideBar::Begin();
}

void UImGui_ClientSideBar_End(UImGui_ClientSideBarFlags flags, UImGui_FVector4 destructiveColour, UImGui_FVector4 destructiveColourActive) noexcept
{
    UImGui::ClientSideBar::End(flags, destructiveColour, destructiveColourActive);
}