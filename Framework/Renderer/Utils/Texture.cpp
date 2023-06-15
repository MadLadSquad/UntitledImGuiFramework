#include "Texture.hpp"
#include <GL/glew.h>
#include <stb_image.h>
#include <Utilities.hpp>
#include <Global.hpp>

UImGui::Texture::Texture(UImGui::String file) noexcept
{
    init(file);
}

void UImGui::Texture::init(UImGui::String file) noexcept
{
    auto& strings = UImGui::Utility::getGlobal().deallocationStruct.keyStrings;

    strings.emplace_back(file);
    dt.filename = strings.back().c_str();
    dt.storageIndex = strings.size() - 1;

    dt.id = 0;
    dt.size = { 0.0f, 0.0f };
    dt.channels = 0;
}

void UImGui::Texture::load(void* data, uint32_t x, uint32_t y, uint32_t depth, bool bFreeImageData, const std::function<void(void*)>& freeFunc) noexcept
{
    if (data == nullptr || (x == 0 && y == 0))
    {
        data = stbi_load(dt.filename, (int*)&x, (int*)&y, nullptr, 0);
        if (data == nullptr)
        {
            Logger::log("Failed to load a texture with the following location: ", UVK_LOG_TYPE_ERROR, dt.filename);
            return;
        }
    }

    glGenTextures(1, &dt.id);
    glBindTexture(GL_TEXTURE_2D, dt.id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    uint32_t dataType = GL_UNSIGNED_BYTE;
    if (depth > 8)
        dataType = GL_UNSIGNED_SHORT;

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, static_cast<int>(x), static_cast<int>(y), 0, GL_RGBA, dataType, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, 0);
    dt.size = { static_cast<float>(x), static_cast<float>(y) };
    if (bFreeImageData)
        freeFunc(data);
}

void UImGui::Texture::loadImGui(void* data, uint32_t x, uint32_t y, uint32_t depth, bool bFreeImageData, const std::function<void(void*)>& freeFunc) noexcept
{
    if (data == nullptr || (x == 0 && y == 0))
    {
        data = stbi_load(dt.filename, (int*)&x, (int*)&y, nullptr, 4);
        if (data == nullptr)
        {
            Logger::log("Failed to load a texture with the following location: ", UVK_LOG_TYPE_ERROR, dt.filename);
            return;
        }
    }

    glGenTextures(1, &dt.id);
    glBindTexture(GL_TEXTURE_2D, dt.id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

#if defined(GL_UNPACK_ROW_LENGTH) && !defined(__EMSCRIPTEN__)
    glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
#endif
    uint32_t dataType = GL_UNSIGNED_BYTE;
    if (depth > 8)
        dataType = GL_UNSIGNED_SHORT;

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, static_cast<int>(x), static_cast<int>(y), 0, GL_RGBA, dataType, data);
    dt.size = { static_cast<float>(x), static_cast<float>(y) };
    if (bFreeImageData)
        freeFunc(data);
}

void UImGui::Texture::use() const noexcept
{
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, dt.id);
}

void UImGui::Texture::clear() noexcept
{
    glDeleteTextures(1, &dt.id);
    dt.id = 0;
    dt.size = { 0.0f, 0.0f };

    auto& strings = UImGui::Utility::getGlobal().deallocationStruct.keyStrings;
    strings.erase(strings.begin() + dt.storageIndex);
}

UImGui::Texture::~Texture() noexcept
{
    clear();
}

const UImGui::FVector2& UImGui::Texture::size() const noexcept
{
    return dt.size;
}

const uint32_t& UImGui::Texture::get() const noexcept
{
    return dt.id;
}