#define STB_IMAGE_WRITE_IMPLEMENTATION

#include "GenericTexture.hpp"
#include <Utilities.hpp>
#include <Global.hpp>
#include <stb_image.h>

void UImGui::GenericTexture::setCustomSaveFunction(const CustomSaveFunction f) noexcept
{
    dt.customSaveFunction = f;
}

const UImGui::FVector2& UImGui::GenericTexture::size() const noexcept
{
    return dt.size;
}

void UImGui::GenericTexture::beginLoad(void** data, FVector2& size) noexcept
{
    if (*data == nullptr || (size.x == 0 && size.y == 0))
    {
        int x = static_cast<int>(size.x);
        int y = static_cast<int>(size.y);

        *data = stbi_load(dt.filename, &x, &y, &dt.channels, 4);
        if (*data == nullptr)
        {
            Logger::log("Failed to load a texture with the following location: ", UVK_LOG_TYPE_ERROR, dt.filename);
            return;
        }
        size.x = static_cast<float>(x);
        size.y = static_cast<float>(y);
    }
}

void UImGui::GenericTexture::endLoad(void* data, const FVector2 size, const bool bFreeImageData, const std::function<void(void*)>& freeFunc) noexcept
{
    dt.size = size;
    if (bFreeImageData)
        freeFunc(data);
    else
        dt.data = data;
}

void UImGui::GenericTexture::defaultInit(const String location) noexcept
{
    auto& strings = Global::get().deallocationStruct.keyStrings;

    strings.emplace_back(location);
    dt.filename = strings.back().c_str();
    dt.storageIndex = strings.size() - 1;

    dt.size = { 0.0f, 0.0f };
    dt.channels = 0;

    dt.data = nullptr;
    dt.customSaveFunction = [](TextureData*, String) -> bool { return false; };
}

void UImGui::GenericTexture::defaultClear() noexcept
{
    dt.size = { 0.0f, 0.0f };

    auto& strings = Global::get().deallocationStruct.keyStrings;
    if (!strings.empty() && dt.storageIndex < strings.size())
        strings.erase(strings.begin() + static_cast<std::string::difference_type>(dt.storageIndex));
}
