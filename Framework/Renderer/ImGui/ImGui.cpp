#include <Global.hpp>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <GLFW/glfw3.h>
#include <Utils/Window.hpp>
#include "ImGui.hpp"
#include <Core/Components/Instance.hpp>

void UImGui::GUIRenderer::beginFrame()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void UImGui::GUIRenderer::shutdown(const FString& ini)
{
    auto& initInfo = Instance::get()->initInfo;

    for (auto& a : initInfo.titlebarComponents)
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

    for (auto& a : initInfo.windowComponents)
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

    for (auto& a : initInfo.inlineComponents)
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

    ImGui::SaveIniSettingsToDisk((UImGui::internalGlobal.instance->initInfo.configDir + "Core/" + ini + ".ini").c_str());
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
#ifdef UIMGUI_PLOTTING_MODULE_ENABLED
    if (Modules::data().plotting)
        ImPlot::DestroyContext();
#endif
    ImGui::DestroyContext();
    Instance::get()->end();
}

void UImGui::GUIRenderer::init(GLFWwindow* glfwwindow, const FString& ini)
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

    ImGui::LoadIniSettingsFromDisk((UImGui::internalGlobal.instance->initInfo.configDir + "Core/" + ini + ".ini").c_str());
    ImGui::StyleColorsDark();

    ImGuiStyle& style = ImGui::GetStyle();
#ifdef UIMGUI_THEME_MODULE_ENABLED
    if (Modules::data().theming)
        UImGui::Theme::load((UImGui::internalGlobal.instance->initInfo.configDir + "Theme/default.theme.yaml").c_str());
#endif
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        style.Colors[ImGuiCol_WindowBg].w = 1.0f;

    Instance::get()->onEventConfigureStyle(style, io);

    ImGui_ImplGlfw_InitForOpenGL(glfwwindow, true);
    ImGui_ImplOpenGL3_Init("#version 330");

    Instance::get()->begin();
    auto& initInfo = Instance::get()->initInfo;

    for (auto& a : Instance::get()->initInfo.titlebarComponents)
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

    for (auto& a : Instance::get()->initInfo.windowComponents)
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

    for (auto& a : Instance::get()->initInfo.inlineComponents)
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

void UImGui::GUIRenderer::beginUI(float deltaTime)
{
    static bool opt_fullscreen = true;
    static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

    ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoCollapse;
    window_flags |= ImGuiTreeNodeFlags_SpanAvailWidth;
    if (opt_fullscreen)
    {
        ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowBgAlpha(1.0f);

        ImGui::SetNextWindowPos(viewport->WorkPos);
        ImGui::SetNextWindowSize(viewport->WorkSize);
        ImGui::SetNextWindowViewport(viewport->ID);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 12.0f);
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

    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
    ImGui::Begin("DockSpace Demo", &bIsOpen, window_flags | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar);
    ImGui::PopStyleVar();

    Instance::get()->tick(deltaTime);
    auto& initInfo = Instance::get()->initInfo;

    for (auto& a : Instance::get()->initInfo.titlebarComponents)
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

    for (auto& a : Instance::get()->initInfo.inlineComponents)
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
    //ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, { 0.0f, 0.0f });
    //ImGui::PushStyleVar(ImGuiStyleVar_CellPadding, { 0.0f, 0.0f });
    // DockSpace
    ImGuiIO& io = ImGui::GetIO();
    if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
    {
        ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
        ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
    }

    for (auto& a : Instance::get()->initInfo.windowComponents)
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

    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        GLFWwindow* backup_current_context = glfwGetCurrentContext();
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
        glfwMakeContextCurrent(backup_current_context);
    }
}
