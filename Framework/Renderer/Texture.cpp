#include "Texture.hpp"

UImGui::Texture::Texture(const String location, const bool bFiltered) noexcept
{
    init(location, bFiltered);
}

void UImGui::Texture::init(const String location, const bool bFiltered) noexcept
{
    bCleared = false;
    TEX_RUN(init(location, bFiltered));
}

void UImGui::Texture::load(void* data, const FVector2 size, const uint32_t depth, const bool bFreeImageData,
    const TFunction<void(void*)>& freeFunc) noexcept
{
    TEX_RUN(load(data, size, depth, bFreeImageData, freeFunc));
}

uintptr_t UImGui::Texture::get() noexcept
{
    TEX_RUN(get());
}

void UImGui::Texture::setCustomSaveFunction(const CustomSaveFunction f) noexcept
{
    TEX_RUN(setCustomSaveFunction(f));
}

const UImGui::FVector2& UImGui::Texture::size() const noexcept
{
    TEX_RUN(size());
}

void UImGui::Texture::clear() noexcept
{
    if (!bCleared)
    {
        bCleared = true;
        Renderer::get().renderer->waitOnGPU();
        TEX_RUN(clear());
    }
}

UImGui::Texture::~Texture() noexcept
{
    clear();
}