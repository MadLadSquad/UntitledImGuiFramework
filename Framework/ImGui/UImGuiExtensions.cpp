#include "UImGuiExtensions.hpp"
#include <Renderer/Texture.hpp>

struct InputTextCallbackUserData
{
    UImGui::FString* str = nullptr;
    ImGuiInputTextCallback chainCallback{};
    void* chainCallbackContext = nullptr;
};

static int InputTextCallback(ImGuiInputTextCallbackData* data)
{
    const auto* user_data = static_cast<InputTextCallbackUserData*>(data->UserData);
    if (data->EventFlag == ImGuiInputTextFlags_CallbackResize)
    {
        // Resize string callback
        // If for some reason we refuse the new length (BufTextLen) and/or capacity (BufSize) we need to set them back to what we want.
        auto* str = user_data->str;
        IM_ASSERT(data->Buf == str->c_str());
        str->resize(data->BufTextLen);
        data->Buf = str->data();
    }
    else if (user_data->chainCallback)
    {
        // Forward to user callback, if any
        data->UserData = user_data->chainCallbackContext;
        return user_data->chainCallback(data);
    }
    return 0;
}

bool ImGui::InputText(const char* label, UImGui::FString* str, ImGuiInputTextFlags flags, const ImGuiInputTextCallback callback, void* user_data)
{
    IM_ASSERT((flags & ImGuiInputTextFlags_CallbackResize) == 0);
    flags |= ImGuiInputTextFlags_CallbackResize;

    InputTextCallbackUserData cb_user_data =
    {
        .str = str,
        .chainCallback = callback,
        .chainCallbackContext = user_data,
    };
    return InputText(label, str->data(), str->capacity() + 1, flags, InputTextCallback, &cb_user_data);
}

bool ImGui::InputTextMultiline(const char* label, UImGui::FString* str, const ImVec2& size, ImGuiInputTextFlags flags, const ImGuiInputTextCallback callback, void* user_data)
{
    IM_ASSERT((flags & ImGuiInputTextFlags_CallbackResize) == 0);
    flags |= ImGuiInputTextFlags_CallbackResize;

    InputTextCallbackUserData cb_user_data =
    {
        .str = str,
        .chainCallback = callback,
        .chainCallbackContext = user_data,
    };
    return InputTextMultiline(label, str->data(), str->capacity() + 1, size, flags, InputTextCallback, &cb_user_data);
}

bool ImGui::InputTextWithHint(const char* label, const char* hint, UImGui::FString* str, ImGuiInputTextFlags flags, const ImGuiInputTextCallback callback, void* user_data)
{
    IM_ASSERT((flags & ImGuiInputTextFlags_CallbackResize) == 0);
    flags |= ImGuiInputTextFlags_CallbackResize;

    InputTextCallbackUserData cb_user_data =
    {
        .str = str,
        .chainCallback = callback,
        .chainCallbackContext = user_data,
    };
    return InputTextWithHint(label, hint, str->data(), str->capacity() + 1, flags, InputTextCallback, &cb_user_data);
}

static void samplerNearest() noexcept
{
    const auto& pio = ImGui::GetPlatformIO();
    if (pio.DrawCallback_SetSamplerNearest != nullptr)
        ImGui::GetWindowDrawList()->AddCallback(pio.DrawCallback_SetSamplerNearest, nullptr);
}

static void restoreSamplerLinear() noexcept
{
    const auto& pio = ImGui::GetPlatformIO();
    if (pio.DrawCallback_SetSamplerLinear != nullptr)
        ImGui::GetWindowDrawList()->AddCallback(pio.DrawCallback_SetSamplerLinear, nullptr);
}

static inline ImVec2 getImageSize(const ImVec2 image_size, const UImGui::FVector2 texture_size) noexcept
{
    return image_size.x == 0.0f && image_size.y == 0.0f ? std::move(texture_size) : std::move(image_size);
}

void ImGui::Image(const UImGui::Texture& texture, const ImVec2 image_size, const ImVec2 uv0, const ImVec2 uv1)
{
    const bool bFiltered = texture.getData().bFiltered;
    if (!bFiltered)
        samplerNearest();
    Image(texture.get(), getImageSize(std::move(image_size), std::move(texture.size())), uv0, uv1);
    if (!bFiltered)
        restoreSamplerLinear();
}

void ImGui::ImageWithBg(const UImGui::Texture& texture, const ImVec2 image_size, const ImVec2 uv0, const ImVec2 uv1, const ImVec4 bg_col, const ImVec4 tint_col)
{
    const bool bFiltered = texture.getData().bFiltered;
    if (!bFiltered)
        samplerNearest();
    ImageWithBg(texture.get(), getImageSize(std::move(image_size), std::move(texture.size())), uv0, uv1, bg_col, tint_col);
    if (!bFiltered)
        restoreSamplerLinear();
}

bool ImGui::ImageButton(const char* str_id, const UImGui::Texture& texture, const ImVec2 image_size, const ImVec2 uv0, const ImVec2 uv1, const ImVec4 bg_col, const ImVec4 tint_col)
{
    const bool bFiltered = texture.getData().bFiltered;
    if (!bFiltered)
        samplerNearest();
    const bool result = ImageButton(str_id, texture.get(), getImageSize(std::move(image_size), std::move(texture.size())), uv0, uv1, bg_col, tint_col);
    if (!bFiltered)
        restoreSamplerLinear();
    return result;
}