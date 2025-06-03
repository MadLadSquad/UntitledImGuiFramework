#include "CGenericTexture.h"
#include <Renderer/GenericRenderer/GenericTexture.hpp>

class CGenericTexture final : public UImGui::GenericTexture
{
public:
    CGenericTexture() noexcept = default;
    virtual void init(UImGui::TextureData& dt, const UImGui::String location, const bool bFiltered) noexcept override
    {
        initFun(&dt, location, bFiltered);
        defaultInit(dt, location, bFiltered);
    }

    virtual uintptr_t get(UImGui::TextureData& dt) noexcept override
    {
        return getFun(&dt);
    }

    virtual void load(UImGui::TextureData& dt, void* data, UImGui::FVector2 size, const uint32_t depth, bool const bFreeImageData, const TFunction<void(void*)>& freeFunc) noexcept override
    {
        beginLoad(dt, &data, size);
        loadFun(&dt, data, size, depth, bFreeImageData);
        endLoad(dt, data, bFreeImageData, freeFunc);
    }

    virtual void clear(UImGui::TextureData& dt) noexcept override
    {
        clearFun(&dt);
        defaultClear(dt);
    }

    ~CGenericTexture() noexcept override = default;

    UImGui_CGenericTexture_InitFun initFun;
    UImGui_CGenericTexture_GetFun getFun;
    UImGui_CGenericTexture_LoadFun loadFun;
    UImGui_CGenericTexture_Clear clearFun;
};

UImGui_CGenericTexture* UImGui_CGenericTexture_make(
    const UImGui_CGenericTexture_InitFun init,
    const UImGui_CGenericTexture_GetFun get,
    const UImGui_CGenericTexture_LoadFun load,
    const UImGui_CGenericTexture_Clear clear)
{
    auto* a = new CGenericTexture{};
    a->initFun = init;
    a->getFun = get,
    a->loadFun = load;
    a->clearFun = clear;

    return static_cast<UImGui_CGenericTexture*>(a);
}

void UImGui_CGenericTexture_free(UImGui_CGenericTexture* texture)
{
    delete static_cast<CGenericTexture*>(texture);
}