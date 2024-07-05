#define STB_IMAGE_WRITE_IMPLEMENTATION

#include "Texture.hpp"
#ifndef __APPLE__
    #include <GL/glew.h>
#else
    #include <OpenGL/GL.h>
#endif
#include <stb_image.h>
#include <Utilities.hpp>
#include <Global.hpp>

#include "Interfaces/RendererInterface.hpp"

UImGui::Texture::Texture(String file) noexcept
{
    init(file);
}

void UImGui::Texture::init(String file) noexcept
{
    auto& strings = Utility::getGlobal().deallocationStruct.keyStrings;

    strings.emplace_back(file);
    dt.filename = strings.back().c_str();
    dt.storageIndex = strings.size() - 1;

    dt.id = 0;
    dt.size = { 0.0f, 0.0f };
    dt.channels = 0;

    dt.data = nullptr;
    dt.customSaveFunction = [](TextureData*, String) -> bool { return false; };
}

void UImGui::Texture::load(void* data, uint32_t x, uint32_t y, const uint32_t depth, const bool bFreeImageData, const std::function<void(void*)>& freeFunc) noexcept
{
    if (data == nullptr || (x == 0 && y == 0))
    {
        data = stbi_load(dt.filename, (int*)&x, (int*)&y, &dt.channels, 0);
        if (data == nullptr)
        {
            Logger::log("Failed to load a texture with the following location: ", UVK_LOG_TYPE_ERROR, dt.filename);
            return;
        }
    }
    Renderer::get().renderer->loadTexture(reinterpret_cast<intptr_t>(&dt.id), x, y, depth, data);

    dt.size = { static_cast<float>(x), static_cast<float>(y) };
    if (bFreeImageData)
        freeFunc(data);
}

void UImGui::Texture::loadImGui(void* data, uint32_t x, uint32_t y, const uint32_t depth, const bool bFreeImageData, const std::function<void(void*)>& freeFunc) noexcept
{
    if (data == nullptr || (x == 0 && y == 0))
    {
        data = stbi_load(dt.filename, (int*)&x, (int*)&y, &dt.channels, 4);
        if (data == nullptr)
        {
            Logger::log("Failed to load a texture with the following location: ", UVK_LOG_TYPE_ERROR, dt.filename);
            return;
        }
    }

    Renderer::get().renderer->loadTextureImGui(reinterpret_cast<intptr_t>(&dt.id), x, y, depth, data);
    dt.size = { static_cast<float>(x), static_cast<float>(y) };

    if (bFreeImageData)
        freeFunc(data);
    else
        dt.data = data;
}

void UImGui::Texture::use() const noexcept
{
    Renderer::get().renderer->useTexture(reinterpret_cast<intptr_t>(&dt.id));
}

void UImGui::Texture::clear() noexcept
{
    Renderer::get().renderer->clearTexture(reinterpret_cast<intptr_t>(&dt.id));
    dt.id = 0;
    dt.size = { 0.0f, 0.0f };

    auto& strings = Utility::getGlobal().deallocationStruct.keyStrings;
    strings.erase(strings.begin() + static_cast<std::string::difference_type>(dt.storageIndex));
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

void UImGui::Texture::setCustomSaveFunction(const CustomSaveFunction f) noexcept
{
    dt.customSaveFunction = f;
}
