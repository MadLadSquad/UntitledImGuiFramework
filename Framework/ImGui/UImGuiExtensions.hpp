#pragma once
#include <Types.hpp>
#include <imgui.h>

// Custom InputText that uses FString
namespace ImGui
{
    UIMGUI_PUBLIC_API bool InputText(const char* label, UImGui::FString* str, ImGuiInputTextFlags flags = 0, ImGuiInputTextCallback callback = nullptr, void* user_data = nullptr);
    UIMGUI_PUBLIC_API bool InputTextMultiline(const char* label, UImGui::FString* str, const ImVec2& size = ImVec2(0, 0), ImGuiInputTextFlags flags = 0, ImGuiInputTextCallback callback = nullptr, void* user_data = nullptr);
    UIMGUI_PUBLIC_API bool InputTextWithHint(const char* label, const char* hint, UImGui::FString* str, ImGuiInputTextFlags flags = 0, ImGuiInputTextCallback callback = nullptr, void* user_data = nullptr);
}