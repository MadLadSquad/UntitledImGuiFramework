#include "CTexture.h"
#include "Utils/Texture.hpp"
#include <stb_image.h>

#define cast(x) ((UImGui::Texture*)(x))

void UImGui_Texture_defaultFreeFunc(void* data)
{
    stbi_image_free(data);
}

void UImGui_Texture_init(UImGui_TextureData* texture, UImGui_String file)
{
    cast(texture)->init(file);
}

void UImGui_Texture_load(UImGui_TextureData* texture, void* data, uint32_t x, uint32_t y, uint32_t depth,
                         bool bFreeImageData, UImGui_Texture_FreeFunctionT defaultFreeFunc)
{
    cast(texture)->load(data, x, y, depth, bFreeImageData, defaultFreeFunc);
}

void UImGui_Texture_loadImGui(UImGui_TextureData* texture, void* data, uint32_t x, uint32_t y, uint32_t depth,
                              bool bFreeImageData, UImGui_Texture_FreeFunctionT defaultFreeFunc)
{
    cast(texture)->loadImGui(data, x, y, depth, bFreeImageData, defaultFreeFunc);
}

uint32_t UImGui_Texture_get(UImGui_TextureData* texture)
{
    return cast(texture)->get();
}

void UImGui_Texture_use(UImGui_TextureData* texture)
{
    cast(texture)->use();
}

UImGui_FVector2 UImGui_Texture_size(UImGui_TextureData* texture)
{
    return cast(texture)->size();
}

void UImGui_Texture_clear(UImGui_TextureData* texture)
{
    cast(texture)->clear();
}

void UImGui_Texture_saveToFile(UImGui_TextureData* texture, UImGui_String location, UImGui_TextureFormat fmt, uint8_t jpegQuality)
{
    cast(texture)->saveToFile<UIMGUI_TEXTURE_FORMAT_OTHER>(location, fmt, jpegQuality);
}

void UImGui_Texture_setCustomSaveFunction(UImGui_TextureData* texture, UImGui_Texture_CustomSaveFunction f)
{
    cast(texture)->setCustomSaveFunction(f);
}