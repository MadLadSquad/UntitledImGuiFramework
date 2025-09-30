#include "UImGuiExtensions.hpp"

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