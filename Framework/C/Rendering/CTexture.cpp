#include "CTexture.h"
#include <Renderer/Texture.hpp>
#include <stb_image.h>

#define cast(x) ((UImGui::Texture*)(x))

void UImGui_Texture_defaultFreeFunc(void* data)
{
    stbi_image_free(data);
}

UImGui_CTexture* UImGui_Texture_init(const UImGui_String file)
{
    auto* texture = new UImGui::Texture(file);
    return texture;
}

void UImGui_Texture_load(UImGui_CTexture* texture, void* data, const UImGui_FVector2 size, const uint32_t depth,
                         const bool bFreeImageData, const UImGui_Texture_FreeFunctionT defaultFreeFunc)
{
    cast(texture)->load(data, size, depth, bFreeImageData, defaultFreeFunc);
}

void* UImGui_Texture_get(UImGui_CTexture* texture)
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
    return cast(texture)->saveToFile<UIMGUI_TEXTURE_FORMAT_OTHER>(location, fmt, jpegQuality);
}

void UImGui_Texture_setCustomSaveFunction(UImGui_CTexture* texture, const UImGui_Texture_CustomSaveFunction f)
{
    cast(texture)->setCustomSaveFunction(f);
}

void UImGui_Texture_free(UImGui_CTexture* texture)
{
    delete static_cast<UImGui::Texture*>(texture);
}