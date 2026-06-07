#pragma once
#include <Types.hpp>
#include <imgui.h>

#include "Texture.hpp"

// Custom InputText that uses FString and custom Image functions that honour the dear imgui sampler callback system
namespace ImGui
{
    UIMGUI_PUBLIC_API bool InputText(const char* label, UImGui::FString* str, ImGuiInputTextFlags flags = 0, ImGuiInputTextCallback callback = nullptr, void* user_data = nullptr);
    UIMGUI_PUBLIC_API bool InputTextMultiline(const char* label, UImGui::FString* str, const ImVec2& size = ImVec2(0, 0), ImGuiInputTextFlags flags = 0, ImGuiInputTextCallback callback = nullptr, void* user_data = nullptr);
    UIMGUI_PUBLIC_API bool InputTextWithHint(const char* label, const char* hint, UImGui::FString* str, ImGuiInputTextFlags flags = 0, ImGuiInputTextCallback callback = nullptr, void* user_data = nullptr);

    UIMGUI_PUBLIC_API void Image(const UImGui::Texture& texture, ImVec2 image_size = { 0.0f, 0.0f }, ImVec2 uv0 = ImVec2(0, 0), ImVec2 uv1 = ImVec2(1, 1));
    UIMGUI_PUBLIC_API void ImageWithBg(const UImGui::Texture& texture, ImVec2 image_size = { 0.0f, 0.0f }, ImVec2 uv0 = ImVec2(0, 0), ImVec2 uv1 = ImVec2(1, 1), ImVec4 bg_col = ImVec4(0, 0, 0, 0), ImVec4 tint_col = ImVec4(1, 1, 1, 1));
    UIMGUI_PUBLIC_API bool ImageButton(const char* str_id, const UImGui::Texture& texture, ImVec2 image_size = { 0.0f, 0.0f }, ImVec2 uv0 = ImVec2(0, 0), ImVec2 uv1 = ImVec2(1, 1), ImVec4 bg_col = ImVec4(0, 0, 0, 0), ImVec4 tint_col = ImVec4(1, 1, 1, 1));
}