#include "OpenGLTexture.hpp"
#ifndef __APPLE__
    #include <GL/glew.h>
#else
    #include <OpenGL/GL.h>
#endif

UImGui::OpenGLTexture::OpenGLTexture(const String location) noexcept
{
    init(location);
}

void UImGui::OpenGLTexture::init(const String location) noexcept
{
    defaultInit(location);
}

void* UImGui::OpenGLTexture::get() noexcept
{
    return reinterpret_cast<void*>(static_cast<intptr_t>(id));
}

void UImGui::OpenGLTexture::clear() noexcept
{
    glDeleteTextures(1, &id);
    id = 0;
    defaultClear();
}

UImGui::OpenGLTexture::~OpenGLTexture() noexcept
{
    clear();
}

void UImGui::OpenGLTexture::load(void* data, FVector2 size, const uint32_t depth, const bool bFreeImageData, const TFunction<void(void*)>& freeFunc) noexcept
{
    beginLoad(&data, size);

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

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, static_cast<int>(size.x), static_cast<int>(size.y), 0, GL_RGBA, dataType, data);

    endLoad(data, size, bFreeImageData, freeFunc);
}
