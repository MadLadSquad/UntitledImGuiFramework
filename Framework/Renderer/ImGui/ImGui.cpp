#include <Global.hpp>
#include <Defines.hpp>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <GLFW/glfw3.h>
#include "ImGui.hpp"
#include <Core/Components/Instance.hpp>
#include <Core/Platform/WASM.hpp>

void UImGui::GUIRenderer::beginFrame() noexcept
{
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void UImGui::GUIRenderer::shutdown(const FString& ini, GenericInternalRenderer* renderer) noexcept
{
    const auto& initInfo = Instance::get()->initInfo;

    for (const auto& a : initInfo.titlebarComponents)
        if (a->state != UIMGUI_COMPONENT_STATE_OFF)
            a->end();
    if (initInfo.cInitInfo != nullptr && initInfo.cInitInfo->titlebarComponents != nullptr)
    {
        for (size_t i = 0; i < initInfo.cInitInfo->titlebarComponentsSize; i++)
        {
            auto* component = static_cast<TitlebarComponent*>(initInfo.cInitInfo->titlebarComponents[i]);
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
            auto* component = static_cast<WindowComponent*>(initInfo.cInitInfo->windowComponents[i]);
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
            auto* component = static_cast<InlineComponent*>(initInfo.cInitInfo->inlineComponents[i]);
            if (component->state != UIMGUI_COMPONENT_STATE_OFF)
                component->end();
        }
    }

    ImGui::SaveIniSettingsToDisk((Instance::get()->initInfo.configDir + "Core/" + ini + ".ini").c_str());
    renderer->ImGuiShutdown();
    ImGui_ImplGlfw_Shutdown();
#ifdef UIMGUI_PLOTTING_MODULE_ENABLED
    if (Modules::data().plotting)
        ImPlot::DestroyContext();
#endif
    ImGui::DestroyContext();
    Instance::get()->end();
}

void UImGui::GUIRenderer::init(const FString& ini, GenericInternalRenderer* renderer) noexcept
{
    ImGui::CreateContext();
#ifdef UIMGUI_PLOTTING_MODULE_ENABLED
    if (Modules::data().plotting)
        ImPlot::CreateContext();
#endif
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable | ImGuiConfigFlags_ViewportsEnable;
    io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
    io.IniFilename = nullptr;
    io.WantSaveIniSettings = false;
    io.ConfigViewportsNoTaskBarIcon = true;
    io.ConfigMacOSXBehaviors = em_is_on_macOS();

    ImGui::LoadIniSettingsFromDisk((Instance::get()->initInfo.configDir + "Core/" + ini + ".ini").c_str());
    ImGui::StyleColorsDark();

    ImGuiStyle& style = ImGui::GetStyle();
#ifdef UIMGUI_THEME_MODULE_ENABLED
    if (Modules::data().theming)
        Theme::load((Instance::get()->initInfo.configDir + "Theme/default.theme.yaml").c_str());
#endif
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
            auto* component = static_cast<TitlebarComponent*>(initInfo.cInitInfo->titlebarComponents[i]);
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
            auto* component = static_cast<WindowComponent*>(initInfo.cInitInfo->windowComponents[i]);
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
            auto* component = static_cast<InlineComponent*>(initInfo.cInitInfo->inlineComponents[i]);
            if (component->state != UIMGUI_COMPONENT_STATE_OFF)
                component->begin();
        }
    }
}

void UImGui::GUIRenderer::beginUI(const float deltaTime, GenericInternalRenderer* renderer) noexcept
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

    if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
        window_flags |= ImGuiWindowFlags_NoBackground;

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
            auto* component = static_cast<TitlebarComponent*>(initInfo.cInitInfo->titlebarComponents[i]);
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
            auto* component = static_cast<InlineComponent*>(initInfo.cInitInfo->inlineComponents[i]);
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
            auto* component = static_cast<WindowComponent*>(initInfo.cInitInfo->windowComponents[i]);
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
