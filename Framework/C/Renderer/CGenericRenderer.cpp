#include "CGenericRenderer.h"
#include "Renderer/GenericRenderer/GenericRenderer.hpp"

class CGenericRenderer final : public UImGui::GenericRenderer
{
public:
    CGenericRenderer() noexcept = default;

    virtual void parseCustomConfig(const ryml::ConstNodeRef&) noexcept override
    {
    }

    virtual void saveCustomConfig(ryml::NodeRef& config) noexcept override
    {
    }

    virtual void setupWindowIntegration() noexcept override
    {
        initInfo->setupWindowIntegration(initInfo);
    }

    virtual void setupPostWindowCreation() noexcept override
    {
        initInfo->setupPostWindowIntegration(initInfo);
    }

    virtual void init(UImGui::RendererInternalMetadata&) noexcept override
    {
        initInfo->init(initInfo);
    }

    virtual void renderStart(const double deltaTime) noexcept override
    {
        initInfo->renderStart(initInfo, deltaTime);
    }

    virtual void renderEnd(const double deltaTime) noexcept override
    {
        initInfo->renderEnd(initInfo, deltaTime);
    }

    virtual void destroy() noexcept override
    {
        initInfo->destroy(initInfo);
    }

    virtual void ImGuiNewFrame() noexcept override
    {
        initInfo->ImGuiNewFrame(initInfo);
    }

    virtual void ImGuiShutdown() noexcept override
    {
        initInfo->ImGuiShutdown(initInfo);
    }

    virtual void ImGuiInit() noexcept override
    {
        initInfo->ImGuiInit(initInfo);
    }

    virtual void ImGuiRenderData() noexcept override
    {
        initInfo->ImGuiRenderData(initInfo);
    }

    // Only called on Vulkan, because there we need to wait for resources to be used before freeing resources,
    // like textures
    virtual void waitOnGPU() noexcept override
    {
        initInfo->waitOnGPU(initInfo);
    }

    ~CGenericRenderer() noexcept override
    {
        initInfo->destruct(initInfo);
    }

    UImGui_CGenericRenderer_InitInfo* initInfo = nullptr;
};

void UImGui_CGenericRenderer_init(UImGui_CGenericRenderer_InitInfo* initInfo)
{
    auto* a = new CGenericRenderer{};
    initInfo->instance = a;
    a->initInfo = initInfo;
}

void UImGui_CGenericRenderer_free(const UImGui_CGenericRenderer_InitInfo* instance)
{
    delete static_cast<CGenericRenderer*>(instance->instance);
}