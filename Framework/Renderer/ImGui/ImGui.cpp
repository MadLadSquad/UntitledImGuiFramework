#include <Global.hpp>
#include <Defines.hpp>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <GLFW/glfw3.h>
#include "ImGui.hpp"
#include <Core/Components/Instance.hpp>
#include <Core/Platform/WASM.hpp>

#include "Interfaces/LayoutsInterface.hpp"

void UImGui::GUIRenderer::init(GenericRenderer* renderer) noexcept
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    Modules::get().initialiseWithImGuiContext();

    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable | ImGuiConfigFlags_ViewportsEnable;
    io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
    io.IniFilename = nullptr;
    io.WantSaveIniSettings = false;
    io.ConfigViewportsNoTaskBarIcon = true;
    io.ConfigMacOSXBehaviors = em_is_on_macOS();

    if (Layouts::getLoadLayout() && !Layouts::layoutLocation().empty())
        ImGui::LoadIniSettingsFromDisk((Instance::get()->initInfo.configDir + "Core/" + Layouts::layoutLocation() + ".ini").c_str());
    ImGui::StyleColorsDark();

    ImGuiStyle& style = ImGui::GetStyle();
    Modules::get().applyCustomisations();
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        style.Colors[ImGuiCol_WindowBg].w = 1.0f;

    auto* inst = Instance::get();
    inst->onEventConfigureStyle(style, io);

    renderer->ImGuiInit();

    inst->begin();
    const auto& initInfo = inst->initInfo;

    for (const auto& a : inst->initInfo.titlebarComponents)
        if (a->state != UIMGUI_COMPONENT_STATE_OFF)
            a->begin();
    if (initInfo.cInitInfo != nullptr && initInfo.cInitInfo->titlebarComponents != nullptr)
    {
        for (size_t i = 0; i < initInfo.cInitInfo->titlebarComponentsSize; i++)
        {
            auto* component = CAST(TitlebarComponent*, initInfo.cInitInfo->titlebarComponents[i]);
            if (component->state != UIMGUI_COMPONENT_STATE_OFF)
                component->begin();
        }
    }

    for (const auto& a : inst->initInfo.windowComponents)
        if (a->state != UIMGUI_COMPONENT_STATE_OFF)
            a->begin();
    if (initInfo.cInitInfo != nullptr && initInfo.cInitInfo->windowComponents != nullptr)
    {
        for (size_t i = 0; i < initInfo.cInitInfo->windowComponentsSize; i++)
        {
            auto* component = CAST(WindowComponent*, initInfo.cInitInfo->windowComponents[i]);
            if (component->state != UIMGUI_COMPONENT_STATE_OFF)
                component->begin();
        }
    }

    for (const auto& a : inst->initInfo.inlineComponents)
        if (a->state != UIMGUI_COMPONENT_STATE_OFF)
            a->begin();
    if (initInfo.cInitInfo != nullptr && initInfo.cInitInfo->inlineComponents != nullptr)
    {
        for (size_t i = 0; i < initInfo.cInitInfo->inlineComponentsSize; i++)
        {
            auto* component = CAST(InlineComponent*, initInfo.cInitInfo->inlineComponents[i]);
            if (component->state != UIMGUI_COMPONENT_STATE_OFF)
                component->begin();
        }
    }
}

void UImGui::GUIRenderer::beginUI(const float deltaTime, GenericRenderer* renderer) noexcept
{
    renderer->ImGuiNewFrame();

    static bool opt_fullscreen = true;
    static bool opt_padding = false;
    static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

    ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoCollapse;
    window_flags |= ImGuiTreeNodeFlags_SpanAvailWidth;
    if (opt_fullscreen)
    {
        const ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowBgAlpha(1.0f);

        ImGui::SetNextWindowPos(viewport->WorkPos);
        ImGui::SetNextWindowSize(viewport->WorkSize);
        ImGui::SetNextWindowViewport(viewport->ID);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 8.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
        window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
        window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
        dockspace_flags |= ImGuiDockNodeFlags_PassthruCentralNode;
    }
    else
        dockspace_flags &= ~ImGuiDockNodeFlags_PassthruCentralNode;

    static bool bIsOpen = true;

    if (!opt_padding)
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
    ImGui::Begin("DockSpace Demo", &bIsOpen, window_flags | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar);
    if (!opt_padding)
        ImGui::PopStyleVar();

    auto* instance = Instance::get();
    instance->tick(deltaTime);
    const auto& initInfo = instance->initInfo;

    for (const auto& a : instance->initInfo.titlebarComponents)
        if (a->state == UIMGUI_COMPONENT_STATE_RUNNING)
            a->tick(deltaTime);
    if (initInfo.cInitInfo != nullptr && initInfo.cInitInfo->titlebarComponents != nullptr)
    {
        for (size_t i = 0; i < initInfo.cInitInfo->titlebarComponentsSize; i++)
        {
            auto* component = CAST(TitlebarComponent*, initInfo.cInitInfo->titlebarComponents[i]);
            if (component->state != UIMGUI_COMPONENT_STATE_OFF)
                component->tick(deltaTime);
        }
    }

    for (const auto& a : instance->initInfo.inlineComponents)
        if (a->state == UIMGUI_COMPONENT_STATE_RUNNING)
            a->tick(deltaTime);
    if (initInfo.cInitInfo != nullptr && initInfo.cInitInfo->inlineComponents != nullptr)
    {
        for (size_t i = 0; i < initInfo.cInitInfo->inlineComponentsSize; i++)
        {
            auto* component = CAST(InlineComponent*, initInfo.cInitInfo->inlineComponents[i]);
            if (component->state != UIMGUI_COMPONENT_STATE_OFF)
                component->tick(deltaTime);
        }
    }

    if (opt_fullscreen)
        ImGui::PopStyleVar(2);

    // DockSpace
    const ImGuiIO& io = ImGui::GetIO();
    if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
    {
        const ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
        ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
    }

    for (const auto& a : instance->initInfo.windowComponents)
        if (a->state == UIMGUI_COMPONENT_STATE_RUNNING)
            a->tick(deltaTime);
    if (initInfo.cInitInfo != nullptr && initInfo.cInitInfo->windowComponents != nullptr)
    {
        for (size_t i = 0; i < initInfo.cInitInfo->windowComponentsSize; i++)
        {
            auto* component = CAST(WindowComponent*, initInfo.cInitInfo->windowComponents[i]);
            if (component->state != UIMGUI_COMPONENT_STATE_OFF)
                component->tick(deltaTime);
        }
    }

    ImGui::End();
    ImGui::Render();

    renderer->ImGuiRenderData();

    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        GLFWwindow* backup_current_context = glfwGetCurrentContext();
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
        glfwMakeContextCurrent(backup_current_context);
    }
}

void UImGui::GUIRenderer::beginFrame() noexcept
{
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void UImGui::GUIRenderer::shutdown(GenericRenderer* renderer) noexcept
{
    renderer->waitOnGPU();
    const auto& initInfo = Instance::get()->initInfo;

    for (const auto& a : initInfo.titlebarComponents)
        if (a->state != UIMGUI_COMPONENT_STATE_OFF)
            a->end();
    if (initInfo.cInitInfo != nullptr && initInfo.cInitInfo->titlebarComponents != nullptr)
    {
        for (size_t i = 0; i < initInfo.cInitInfo->titlebarComponentsSize; i++)
        {
            auto* component = CAST(TitlebarComponent*, initInfo.cInitInfo->titlebarComponents[i]);
            if (component->state != UIMGUI_COMPONENT_STATE_OFF)
                component->end();
        }
    }

    for (const auto& a : initInfo.windowComponents)
        if (a->state != UIMGUI_COMPONENT_STATE_OFF)
            a->end();
    if (initInfo.cInitInfo != nullptr && initInfo.cInitInfo->windowComponents != nullptr)
    {
        for (size_t i = 0; i < initInfo.cInitInfo->windowComponentsSize; i++)
        {
            auto* component = CAST(WindowComponent*, initInfo.cInitInfo->windowComponents[i]);
            if (component->state != UIMGUI_COMPONENT_STATE_OFF)
                component->end();
        }
    }

    for (const auto& a : initInfo.inlineComponents)
        if (a->state != UIMGUI_COMPONENT_STATE_OFF)
            a->end();
    if (initInfo.cInitInfo != nullptr && initInfo.cInitInfo->inlineComponents != nullptr)
    {
        for (size_t i = 0; i < initInfo.cInitInfo->inlineComponentsSize; i++)
        {
            auto* component = CAST(InlineComponent*, initInfo.cInitInfo->inlineComponents[i]);
            if (component->state != UIMGUI_COMPONENT_STATE_OFF)
                component->end();
        }
    }

    if (Layouts::getLoadLayout() && !Layouts::layoutLocation().empty())
        ImGui::SaveIniSettingsToDisk((Instance::get()->initInfo.configDir + "Core/" + Layouts::layoutLocation() + ".ini").c_str());
    renderer->ImGuiShutdown();
    ImGui_ImplGlfw_Shutdown();
#ifdef UIMGUI_PLOTTING_MODULE_ENABLED
    if (Modules::data().plotting)
        ImPlot::DestroyContext();
#endif
    ImGui::DestroyContext();
    Instance::get()->end();
}