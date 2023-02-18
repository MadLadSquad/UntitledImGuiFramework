#include <Global.hpp>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <imgui_internal.h>
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

void UImGui::GUIRenderer::shutdown()
{
    for (auto& a : Instance::get()->initInfo.titlebarComponents)
        if (a->state != UIMGUI_COMPONENT_STATE_OFF)
            a->end();
    for (auto& a : Instance::get()->initInfo.windowComponents)
        if (a->state != UIMGUI_COMPONENT_STATE_OFF)
            a->end();
    for (auto& a : Instance::get()->initInfo.inlineComponents)
        if (a->state != UIMGUI_COMPONENT_STATE_OFF)
            a->end();

    ImGui::SaveIniSettingsToMemory();
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
#ifdef UIMGUI_PLOTTING_MODULE_ENABLED
    ImPlot::DestroyContext();
#endif
    ImGui::DestroyContext();
    Instance::get()->end();
}

void UImGui::GUIRenderer::init(GLFWwindow* glfwwindow, const std::string& ini)
{
    ImGui::CreateContext();
#ifdef UIMGUI_PLOTTING_MODULE_ENABLED
    ImPlot::CreateContext();
#endif
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable | ImGuiConfigFlags_ViewportsEnable;
    io.WantSaveIniSettings = false;
    io.ConfigViewportsNoTaskBarIcon = true;

    ImGui::LoadIniSettingsFromMemory(ini.c_str());
    ImGui::StyleColorsDark();
    ImGui::StyleColorsClassic();
    ImGuiStyle& style = ImGui::GetStyle();
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        style.Colors[ImGuiCol_WindowBg].w = 1.0f;

    Instance::get()->onEventConfigureStyle(style, io);

    ImGui_ImplGlfw_InitForOpenGL(glfwwindow, true);
    ImGui_ImplOpenGL3_Init("#version 330");

    Instance::get()->begin();
    for (auto& a : Instance::get()->initInfo.titlebarComponents)
        if (a->state != UIMGUI_COMPONENT_STATE_OFF)
            a->begin();
    for (auto& a : Instance::get()->initInfo.windowComponents)
        if (a->state != UIMGUI_COMPONENT_STATE_OFF)
            a->begin();
    for (auto& a : Instance::get()->initInfo.inlineComponents)
        if (a->state != UIMGUI_COMPONENT_STATE_OFF)
            a->begin();
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

    for (auto& a : Instance::get()->initInfo.titlebarComponents)
        if (a->state == UIMGUI_COMPONENT_STATE_RUNNING)
            a->tick(deltaTime);
    for (auto& a : Instance::get()->initInfo.inlineComponents)
        if (a->state == UIMGUI_COMPONENT_STATE_RUNNING)
            a->tick(deltaTime);

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