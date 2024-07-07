#include <WebGPU/WebGPUTexture.hpp>

UImGui::WebGPUTexture::WebGPUTexture(const String location) noexcept
{
    init(location);
}

void UImGui::WebGPUTexture::init(const String location) noexcept
{
    defaultInit(location);
}

void UImGui::WebGPUTexture::load(void* data, FVector2 size, uint32_t depth, bool bFreeImageData,
    const std::function<void(void*)>& freeFunc) noexcept
{
    beginLoad(&data, size);
    endLoad(data, size, bFreeImageData, freeFunc);
}

void* UImGui::WebGPUTexture::get() noexcept
{
    return reinterpret_cast<void*>(static_cast<intptr_t>(id));
}

void UImGui::WebGPUTexture::clear() noexcept
{
    defaultClear();
}

UImGui::WebGPUTexture::~WebGPUTexture() noexcept
{
    clear();
}
