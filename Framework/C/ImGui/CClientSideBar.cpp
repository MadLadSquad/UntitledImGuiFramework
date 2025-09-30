#include "CClientSideBar.h"
#include <ImGui/ClientSideBar.hpp>

void UImGui_ClientSideBar_Begin()
{
    UImGui::ClientSideBar::Begin();
}

void UImGui_ClientSideBar_End(const UImGui_ClientSideBarFlags flags, const UImGui_FVector4 destructiveColour, const UImGui_FVector4 destructiveColourActive)
{
    UImGui::ClientSideBar::End(flags, destructiveColour, destructiveColourActive);
}