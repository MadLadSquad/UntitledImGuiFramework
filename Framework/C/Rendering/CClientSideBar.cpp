#include "CClientSideBar.h"
#include <ImGui/ClientSideBar.hpp>

void UImGui_ClientSideBar_Begin()
{
    UImGui::ClientSideBar::Begin();
}

void UImGui_ClientSideBar_End(float deltaTime, UImGui_ClientSideBarFlags flags, UImGui_FVector4 destructiveColor, UImGui_FVector4 destructiveColorActive) noexcept
{
    UImGui::ClientSideBar::End(deltaTime, flags, destructiveColor, destructiveColorActive);
}