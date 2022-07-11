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

void UImGui::Texture::load() noexcept
{
    int x, y;
    unsigned char* texData = stbi_load(filename.c_str(), &x, &y, nullptr, 0);
    if (texData == nullptr)
    {
        logger.consoleLog("Failed to load a texture with the following location: ", UVK_LOG_TYPE_ERROR, filename);
        return;
    }

    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, x, y, 0, GL_RGBA, GL_UNSIGNED_BYTE, texData);
    glGenerateMipmap(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, 0);
    sz = { static_cast<float>(x), static_cast<float>(y) };
    stbi_image_free(texData);
}

void UImGui::Texture::loadImGui() noexcept
{
    int x, y;
    unsigned char* image_data = stbi_load(filename.c_str(), &x, &y, nullptr, 4);
    if (image_data == nullptr)
    {
        logger.consoleLog("Failed to load a texture with the following location: ", UVK_LOG_TYPE_ERROR, filename);
        return;
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
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, x, y, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data);
    sz = { static_cast<float>(x), static_cast<float>(y) };
    stbi_image_free(image_data);
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
