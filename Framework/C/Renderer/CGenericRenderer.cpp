#include "CGenericRenderer.h"
#include "Renderer/GenericRenderer/GenericRenderer.hpp"

class CGenericRenderer final : public UImGui::GenericRenderer
{
public:
    CGenericRenderer() noexcept = default;

    virtual void parseCustomConfig(YAML::Node&) noexcept override
    {
    }

    virtual void setupWindowIntegration() noexcept override
    {
        setupWindowIntegrationFun();
    }

    virtual void setupPostWindowCreation() noexcept override
    {
        setupPostWindowIntegrationFun();
    }

    virtual void init(UImGui::RendererInternalMetadata&) noexcept override
    {
        initFun();
    }

    virtual void renderStart(const double deltaTime) noexcept override
    {
        renderStartFun(deltaTime);
    }

    virtual void renderEnd(const double deltaTime) noexcept override
    {
        renderEndFun(deltaTime);
    }

    virtual void destroy() noexcept override
    {
        destroyFun();
    }

    virtual void ImGuiNewFrame() noexcept override
    {
        ImGuiNewFrameFun();
    }

    virtual void ImGuiShutdown() noexcept override
    {
        ImGuiShutdownFun();
    }

    virtual void ImGuiInit() noexcept override
    {
        ImGuiInitFun();
    }

    virtual void ImGuiRenderData() noexcept override
    {
        ImGuiRenderDataFun();
    }

    // Only called on Vulkan, because there we need to wait for resources to be used before freeing resources,
    // like textures
    virtual void waitOnGPU() noexcept override
    {
        waitOnGPUFun();
    }

    ~CGenericRenderer() noexcept override
    {
        destructFun();
    }

    UImGui_CGenericRenderer_VoidVoidFun setupWindowIntegrationFun;
    UImGui_CGenericRenderer_VoidVoidFun setupPostWindowIntegrationFun;

    UImGui_CGenericRenderer_VoidVoidFun initFun;
    UImGui_CGenericRenderer_TickEvent renderStartFun;
    UImGui_CGenericRenderer_TickEvent renderEndFun;
    UImGui_CGenericRenderer_VoidVoidFun destroyFun;

    UImGui_CGenericRenderer_VoidVoidFun ImGuiNewFrameFun;
    UImGui_CGenericRenderer_VoidVoidFun ImGuiShutdownFun;
    UImGui_CGenericRenderer_VoidVoidFun ImGuiInitFun;
    UImGui_CGenericRenderer_VoidVoidFun ImGuiRenderDataFun;

    UImGui_CGenericRenderer_VoidVoidFun waitOnGPUFun;
    UImGui_CGenericRenderer_VoidVoidFun destructFun;
};

UImGui_CGenericRenderer* UImGui_CGenericRenderer_init(
    const UImGui_CGenericRenderer_VoidVoidFun setupWindowIntegration,
    const UImGui_CGenericRenderer_VoidVoidFun setupPostWindowIntegration,

    const UImGui_CGenericRenderer_VoidVoidFun init,
    const UImGui_CGenericRenderer_TickEvent renderStart,
    const UImGui_CGenericRenderer_TickEvent renderEnd,
    const UImGui_CGenericRenderer_VoidVoidFun destroy,

    const UImGui_CGenericRenderer_VoidVoidFun ImGuiNewFrame,
    const UImGui_CGenericRenderer_VoidVoidFun ImGuiShutdown,
    const UImGui_CGenericRenderer_VoidVoidFun ImGuiInit,
    const UImGui_CGenericRenderer_VoidVoidFun ImGuiRenderData,

    const UImGui_CGenericRenderer_VoidVoidFun waitOnGPU,
    const UImGui_CGenericRenderer_VoidVoidFun destruct)
{
    auto* a = new CGenericRenderer{};
    a->setupWindowIntegrationFun = setupWindowIntegration;
    a->setupPostWindowIntegrationFun = setupPostWindowIntegration;

    a->initFun = init;
    a->renderStartFun = renderStart;
    a->renderEndFun = renderEnd;
    a->destroyFun = destroy;

    a->ImGuiNewFrameFun = ImGuiNewFrame;
    a->ImGuiShutdownFun = ImGuiShutdown;
    a->ImGuiInitFun = ImGuiInit;
    a->ImGuiRenderDataFun = ImGuiRenderData;

    a->waitOnGPUFun = waitOnGPU;
    a->destructFun = destruct;

    return static_cast<UImGui_CGenericRenderer*>(a);
}

void UImGui_CGenericRenderer_free(UImGui_CGenericRenderer* data)
{
    delete static_cast<CGenericRenderer*>(data);
}