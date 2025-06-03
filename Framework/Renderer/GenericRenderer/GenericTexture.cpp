#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "GenericTexture.hpp"
#include <Utilities.hpp>
#include <Global.hpp>
#include <stb_image.h>

void UImGui::GenericTexture::beginLoad(TextureData& dt, void** data, FVector2& size) noexcept
{
    if (*data == nullptr || (size.x == 0 && size.y == 0))
    {
        int x = static_cast<int>(size.x);
        int y = static_cast<int>(size.y);

        *data = stbi_load(dt.filename, &x, &y, &dt.channels, 4);
        if (*data == nullptr)
        {
            Logger::log("Failed to load a texture with the following location: ", ULOG_LOG_TYPE_ERROR, dt.filename);
            return;
        }
        size.x = static_cast<float>(x);
        size.y = static_cast<float>(y);
        dt.size = size;
    }
}

void UImGui::GenericTexture::endLoad(TextureData& dt, void* data, const bool bFreeImageData, const TFunction<void(void*)>& freeFunc) noexcept
{
    if (bFreeImageData)
        freeFunc(data);
    else
        dt.data = data;
}

void UImGui::GenericTexture::defaultInit(TextureData& dt, const String location, const bool bFiltered) noexcept
{
    auto& strings = Global::get().deallocationStruct.keyStrings;

    strings.emplace_back(location);
    dt.filename = strings.back().c_str();
    dt.storageIndex = strings.size() - 1;

    dt.size = { 0.0f, 0.0f };
    dt.channels = 0;
    dt.bFiltered = bFiltered;

    dt.data = nullptr;
    dt.customSaveFunction = [](TextureData*, String) -> bool { return false; };
    dt.id = 0;
}

void UImGui::GenericTexture::defaultClear(TextureData& dt) noexcept
{
    dt.size = { 0.0f, 0.0f };

    auto& strings = Global::get().deallocationStruct.keyStrings;
    if (!strings.empty() && dt.storageIndex < strings.size())
        strings.erase(strings.begin() + static_cast<FString::difference_type>(dt.storageIndex));
}
