#include "Texture.hpp"
#include <GL/glew.h>
#include <stb_image.h>

UImGui::Texture::Texture(UImGui::String file) noexcept
{
    init(file);
}

void UImGui::Texture::init(UImGui::String file) noexcept
{
    filename = file;
}

void UImGui::Texture::load(void* data, uint32_t x, uint32_t y, uint32_t depth, bool bFreeImageData, const std::function<void(void*)>& freeFunc) noexcept
{
    if (data == nullptr || (x == 0 && y == 0))
    {
        data = stbi_load(filename.c_str(), (int*)&x, (int*)&y, nullptr, 0);
        if (data == nullptr)
        {
            Logger::log("Failed to load a texture with the following location: ", UVK_LOG_TYPE_ERROR, filename);
            return;
        }
    }

    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);

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
    sz = { static_cast<float>(x), static_cast<float>(y) };
    if (bFreeImageData)
        freeFunc(data);
}

void UImGui::Texture::loadImGui(void* data, uint32_t x, uint32_t y, uint32_t depth, bool bFreeImageData, const std::function<void(void*)>& freeFunc) noexcept
{
    if (data == nullptr || (x == 0 && y == 0))
    {
        data = stbi_load(filename.c_str(), (int*)&x, (int*)&y, nullptr, 4);
        if (data == nullptr)
        {
            Logger::log("Failed to load a texture with the following location: ", UVK_LOG_TYPE_ERROR, filename);
            return;
        }
    }

    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);

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
    sz = { static_cast<float>(x), static_cast<float>(y) };
    if (bFreeImageData)
        freeFunc(data);
}

void UImGui::Texture::use() const noexcept
{
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, id);
}

void UImGui::Texture::clear() noexcept
{
    glDeleteTextures(1, &id);
    id = 0;
    sz = { 0.0f, 0.0f };
    filename.clear();
}

UImGui::Texture::~Texture() noexcept
{
    clear();
}

const UImGui::FVector2& UImGui::Texture::size() const noexcept
{
    return sz;
}

const uint32_t& UImGui::Texture::get() const noexcept
{
    return id;
}

void UImGui::Texture::defaultFreeFunc(void* data) noexcept
{
    stbi_image_free(data);
}
