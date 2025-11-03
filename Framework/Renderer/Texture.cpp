#include "Texture.hpp"
#include <Core/Components/Instance.hpp>

UImGui::Texture::Texture(const String location, const bool bFiltered) noexcept
{
    init(location, bFiltered);
}

bool UImGui::Texture::init(const String location, const bool bFiltered) noexcept
{
    auto& type = Renderer::data().textureRendererType;
#ifdef __EMSCRIPTEN__
    type = (type == UIMGUI_RENDERER_TYPE_VULKAN_WEBGPU) ? UIMGUI_RENDERER_TYPE_OPENGL : type;
#endif
    if (type == UIMGUI_RENDERER_TYPE_CUSTOM)
    {
        auto& initInfo = Instance::get()->initInfo;
        if (initInfo.customTexture != nullptr)
            textures[UIMGUI_RENDERER_TYPE_CUSTOM] = initInfo.customTexture;
        else if (initInfo.cInitInfo != nullptr && initInfo.cInitInfo->customTexture != nullptr)
            textures[UIMGUI_RENDERER_TYPE_CUSTOM] = static_cast<GenericTexture*>(initInfo.cInitInfo->customTexture);
        else
        {
            Logger::log("Invalid custom renderer backend!", ULOG_LOG_TYPE_ERROR);
            return false;
        }
    }
    bCleared = false;
    textures[type]->init(dt, location, bFiltered);
    return true;
}

void UImGui::Texture::load(void* data, const FVector2 size, const uint32_t depth, const bool bFreeImageData,
    const TFunction<void(void*)>& freeFunc) noexcept
{
    TEX_RUN(load(dt, data, size, depth, bFreeImageData, freeFunc));
}

uintptr_t UImGui::Texture::get() noexcept
{
    TEX_RUN(get(dt));
}

void UImGui::Texture::setCustomSaveFunction(const CustomSaveFunction f) noexcept
{
    dt.customSaveFunction = f;
}

UImGui::FVector2 UImGui::Texture::size() const noexcept
{
    return dt.size;
}

void UImGui::Texture::clear() noexcept
{
    if (!bCleared)
    {
        bCleared = true;
        RendererUtils::getRenderer()->waitOnGPU();
        // CAUTION: if you get a crash here you probably forgot to clear your texture
        // in a function marked as event safe during "end"(*::end methods of components/instance for example)
        TEX_RUN(clear(dt));
    }
}

UImGui::Texture::~Texture() noexcept
{
    clear();
}

UImGui::TextureData& UImGui::Texture::getData() noexcept
{
    return dt;
}
