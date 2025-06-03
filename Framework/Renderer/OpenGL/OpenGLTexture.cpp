#include "OpenGLTexture.hpp"
#ifndef __APPLE__
    #include <glad/include/glad/gl.h>
#elif __EMSCRIPTEN__
    #include <glad/include/glad/gles2.h>
#else
    #include <OpenGL/GL.h>
#endif
#include <Interfaces/RendererInterface.hpp>

void UImGui::OpenGLTexture::init(TextureData& dt, const String location, const bool bFiltered) noexcept
{
    defaultInit(dt, location, bFiltered);
}

uintptr_t UImGui::OpenGLTexture::get(TextureData& dt) noexcept
{
    return dt.id;
}

void UImGui::OpenGLTexture::clear(TextureData& dt) noexcept
{
    const GLuint tmp = dt.id;
    if (Renderer::data().textureRendererType == UIMGUI_RENDERER_TYPE_OPENGL)
        glDeleteTextures(1, &tmp);
    dt.id = 0;
    defaultClear(dt);
}

void UImGui::OpenGLTexture::load(TextureData& dt, void* data, FVector2 size, const uint32_t depth, const bool bFreeImageData, const TFunction<void(void*)>& freeFunc) noexcept
{
    beginLoad(dt, &data, size);

    GLuint tmp = 0;

    glGenTextures(1, &tmp);
    glBindTexture(GL_TEXTURE_2D, tmp);

    dt.id = tmp;

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, dt.bFiltered ? GL_LINEAR : GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, dt.bFiltered ? GL_LINEAR : GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

#if defined(GL_UNPACK_ROW_LENGTH) && !defined(__EMSCRIPTEN__)
    glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
#endif
    uint32_t dataType = GL_UNSIGNED_BYTE;
    if (depth > 8)
        dataType = GL_UNSIGNED_SHORT;

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, static_cast<int>(size.x), static_cast<int>(size.y), 0, GL_RGBA, dataType, data);

    endLoad(dt, data, bFreeImageData, freeFunc);
}
