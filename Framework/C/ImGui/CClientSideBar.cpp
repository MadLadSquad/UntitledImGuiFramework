#include "CClientSideBar.h"
#include <ImGui/ClientSideBar.hpp>

void UImGui_ClientSideBar_SetFlags(const UImGui_ClientSideBarFlags flags)
{
    UImGui::ClientSideBar::SetFlags(flags);
}

bool UImGui_ClientSideBar_Begin()
{
    return UImGui::ClientSideBar::Begin();
}

void UImGui_ClientSideBar_End(const bool bRendered, const UImGui_FVector4 destructiveColour, const UImGui_FVector4 destructiveColourActive)
{
    UImGui::ClientSideBar::End(bRendered, destructiveColour, destructiveColourActive);
}

void UImGui_ClientSideBar_BeginManualStyle()
{
    UImGui::ClientSideBar::BeginManualStyle();
}

void UImGui_ClientSideBar_EndManualStyle()
{
    UImGui::ClientSideBar::EndManualStyle();
}

void UImGui_ClientSideBar_BeginManualRender()
{
    UImGui::ClientSideBar::BeginManualRender();
}

void UImGui_ClientSideBar_EndManualRender(const UImGui_FVector4 destructiveColour, const UImGui_FVector4 destructiveColourActive)
{
    UImGui::ClientSideBar::EndManualRender(destructiveColour, destructiveColourActive);
}
