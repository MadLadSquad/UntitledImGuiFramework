#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "GenericTexture.hpp"
#include <Utilities.hpp>
#include <C/CAllocator.h>
#include <cstring>
#include <stb_image.h>

void UImGui::GenericTexture::beginLoad(TextureData& dt, void** data, FVector2& size) noexcept
{
    if (*data == nullptr || (size.x == 0 && size.y == 0))
    {
        int x = static_cast<int>(size.x);
        int y = static_cast<int>(size.y);

        // stbi_load writes the file's own channel count here, which is overwritten below
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

// The filename is owned by the TextureData and copied through the framework allocator, so that it stays valid for exactly
// as long as the texture does.
//
// It used to be a c_str() pointer into Global::deallocationStruct.keyStrings, which was unsafe twice over. That vector is
// shared with the C API's key-name registry, so any push_back from either side could reallocate it and dangle the filename
// of every texture created so far. And defaultClear erased by storageIndex, which shifts every later element down one -
// invalidating the storageIndex and filename of every texture created after the one being cleared, and silently deleting
// an unrelated key name once the two systems interleaved. Owning the string removes both failure modes and the index
// bookkeeping along with them; storageIndex is left at 0 and is no longer read for textures.
void UImGui::GenericTexture::defaultInit(TextureData& dt, const String location, const bool bFiltered) noexcept
{
    // Guards against a re-init that skipped clear(). Textures always reach this with a zero-initialised TextureData, so a
    // non-null filename here can only be one we allocated ourselves
    if (dt.filename != nullptr)
        UImGui_Allocator_deallocate(const_cast<char*>(dt.filename));
    dt.filename = nullptr;

    if (location != nullptr)
    {
        const size_t length = strlen(location) + 1;
        auto* buffer = static_cast<char*>(UImGui_Allocator_allocate(length));
        if (buffer != nullptr)
            memcpy(buffer, location, length);
        else
            Logger::log("Failed to allocate storage for a texture filename: ", ULOG_LOG_TYPE_ERROR, location);
        dt.filename = buffer;
    }
    dt.storageIndex = 0;

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

    UImGui_Allocator_deallocate(const_cast<char*>(dt.filename));
    dt.filename = nullptr;
}
