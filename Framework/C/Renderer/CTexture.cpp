#include "CTexture.h"
#include <Core/Global.hpp>
#include <Renderer/Texture.hpp>
#include <stb_image.h>
#include <ImGui/UImGuiExtensions.hpp>

#define cast(x) ((UImGui::Texture*)(x))

void UImGui_Texture_defaultFreeFunc(void* data)
{
    stbi_image_free(data);
}

UImGui_CTexture* UImGui_Texture_init(const UImGui_String file, const bool bFiltered)
{
    // Constructed in place. This used to build a local Texture(which already initialised it), call init() on it a second
    // time, copy it into the list, and then let the local's destructor clear() the GPU texture that the stored copy was
    // still pointing at - so every handle returned from here referred to an already-destroyed texture
    auto& textures = UImGui::Global::get().deallocationStruct.textures;
    auto& tex = textures.emplace_back();

    if (!tex.init(file, bFiltered))
    {
        textures.pop_back();
        return nullptr;
    }
    return &tex;
}

void UImGui_Texture_load(UImGui_CTexture* texture, void* data, const UImGui_FVector2 size, const uint32_t depth,
                         const bool bFreeImageData, const UImGui_Texture_FreeFunctionT defaultFreeFunc)
{
    cast(texture)->load(data, size, depth, bFreeImageData, defaultFreeFunc);
}

uintptr_t UImGui_Texture_get(UImGui_CTexture* texture)
{
    return cast(texture)->get();
}

UImGui_FVector2 UImGui_Texture_size(UImGui_CTexture* texture)
{
    return cast(texture)->size();
}

void UImGui_Texture_clear(UImGui_CTexture* texture)
{
    cast(texture)->clear();
}

bool UImGui_Texture_saveToFile(UImGui_CTexture* texture, const UImGui_String location, const UImGui_TextureFormat fmt, const uint8_t jpegQuality)
{
    return UImGui::GenericTexture::saveToFile<UIMGUI_TEXTURE_FORMAT_OTHER>(cast(texture)->getData(), location, fmt, jpegQuality);
}

void UImGui_Texture_setCustomSaveFunction(UImGui_CTexture* texture, const UImGui_Texture_CustomSaveFunction f)
{
    cast(texture)->setCustomSaveFunction(f);
}

void UImGui_Texture_release(const UImGui_CTexture* texture)
{
    // Could use pointer arithmetic but that would be really unsafe
    auto& textures = UImGui::Global::get().deallocationStruct.textures;
    for (auto it = textures.begin(); it != textures.end(); ++it)
    {
        if (texture == &*it)
        {
            textures.erase(it);
            return;
        }
    }
}

void UImGui_Image(const UImGui_CTexture* texture)
{
    ImGui::Image(*cast(texture));
}

void UImGui_ImageEx(const UImGui_CTexture* texture, UImGui_FVector2 image_size, UImGui_FVector2 uv0, UImGui_FVector2 uv1)
{
    ImGui::Image(*cast(texture), { image_size.x, image_size.y }, { uv0.x, uv0.y }, { uv1.x, uv1.y });
}

void UImGui_ImageWithBg(const UImGui_CTexture* texture)
{
    ImGui::ImageWithBg(*cast(texture));
}

void UImGui_ImageWithBgEx(const UImGui_CTexture* texture, UImGui_FVector2 image_size, UImGui_FVector2 uv0, UImGui_FVector2 uv1, UImGui_FVector4 bg_col, UImGui_FVector4 tint_col)
{
    ImGui::ImageWithBg(
        *cast(texture),
        {
            image_size.x,
            image_size.y
        },
        {
            uv0.x,
            uv0.y
        },
        {
            uv1.x,
            uv1.y
        },
        {
            bg_col.x,
            bg_col.y,
            bg_col.z,
            bg_col.w
        },
        {
            tint_col.x,
            tint_col.y,
            tint_col.z,
            tint_col.w
        }
    );
}


bool UImGui_ImageButton(const char* str_id, const UImGui_CTexture* texture)
{
    return ImGui::ImageButton(str_id, *cast(texture));
}

bool UImGui_ImageButtonEx(const char* str_id, const UImGui_CTexture* texture, UImGui_FVector2 image_size, UImGui_FVector2 uv0, UImGui_FVector2 uv1, UImGui_FVector4 bg_col, UImGui_FVector4 tint_col)
{
    return ImGui::ImageButton(
        str_id,
        *cast(texture),
        {
            image_size.x,
            image_size.y
        },
        {
            uv0.x,
            uv0.y
        },
        {
            uv1.x,
            uv1.y
        },
        {
            bg_col.x,
            bg_col.y,
            bg_col.z,
            bg_col.w
        },
        {
            tint_col.x,
            tint_col.y,
            tint_col.z,
            tint_col.w
        }
    );
}
