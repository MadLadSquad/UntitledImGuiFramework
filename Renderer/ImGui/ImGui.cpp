#include <Core.hpp>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <imgui_internal.h>
#include <GLFW/glfw3.h>
#include <Utils/Window.hpp>
#include "ImGui.hpp"

void Renderer::ImGuiUtil::beginFrame()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void Renderer::ImGuiUtil::shutdown()
{
    ImGui::SaveIniSettingsToMemory();
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void Renderer::ImGuiUtil::init(GLFWwindow* glfwwindow, const std::string& ini)
{
    ImGui::CreateContext();
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
    setupTheme(style.Colors);

    ImGui_ImplGlfw_InitForOpenGL(glfwwindow, true);
    ImGui_ImplOpenGL3_Init("#version 330");
}

void Renderer::ImGuiUtil::setupTheme(ImVec4* colours)
{
    colours[ImGuiCol_Text] = { 1.0f, 1.0f, 1.0f, 1.0f };
    colours[ImGuiCol_WindowBg] = { 0.1f, 0.1f, 0.1f, 1.0f };

    colours[ImGuiCol_Header] = { 0.2f, 0.2f, 0.2f, 1.0f };
    colours[ImGuiCol_HeaderHovered] = { 0.3f, 0.3f, 0.3f, 1.0f };
    colours[ImGuiCol_HeaderActive] = { 0.15f, 0.15f, 0.15f, 1.0f };

    colours[ImGuiCol_Button] = { 0.2f, 0.2f, 0.2f, 1.0f };
    colours[ImGuiCol_ButtonHovered] = { 0.3f, 0.3f, 0.3f, 1.0f };
    colours[ImGuiCol_ButtonActive] = { 0.15f, 0.15f, 0.15f, 1.0f };

    colours[ImGuiCol_FrameBg] = { 0.2f, 0.2f, 0.2f, 1.0f };
    colours[ImGuiCol_FrameBgHovered] = { 0.3f, 0.3f, 0.3f, 1.0f };
    colours[ImGuiCol_FrameBgActive] = { 0.15f, 0.15f, 0.15f, 1.0f };

    colours[ImGuiCol_Tab] = { 0.15, 0.15, 0.15, 1.0 };
    colours[ImGuiCol_TabHovered] = { 0.4, 0.4, 0.4, 1.0 };
    colours[ImGuiCol_TabActive] = { 0.3, 0.3, 0.3, 1.0 };
    colours[ImGuiCol_TabUnfocused] = { 0.15, 0.15, 0.15, 1.0 };
    colours[ImGuiCol_TabUnfocusedActive] = { 0.2, 0.2, 0.2, 1.0 };

    colours[ImGuiCol_TitleBg] = { 0.15, 0.15, 0.15, 1.0 };
    colours[ImGuiCol_TitleBgActive] = { 0.15, 0.15, 0.15, 1.0 };
    colours[ImGuiCol_TitleBgCollapsed] = { 0.95, 0.15, 0.95, 1.0 };

    colours[ImGuiCol_MenuBarBg] = { 0.01, 0.01, 0.01, 1.0 };
    colours[ImGuiCol_PopupBg] = { 0.1, 0.1, 0.1, 1.0 };
}

void Renderer::ImGuiUtil::beginUI(const std::function<void(Window&)>& renderFunc, const std::function<void(Window&)>& renderWindowFunc, Window& mainWindow)
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
        dockspace_flags |= ImGuiDockNodeFlags_PassthruCentralNode | ImGuiDockNodeFlags_AutoHideTabBar | ImGuiDockNodeFlags_NoTabBar;
    }
    else
        dockspace_flags &= ~ImGuiDockNodeFlags_PassthruCentralNode;


    if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
        window_flags |= ImGuiWindowFlags_NoBackground;

    static bool bIsOpen = true;

    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
    ImGui::Begin("DockSpace Demo", &bIsOpen, window_flags | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar);
    ImGui::PopStyleVar();
    renderFunc(mainWindow);

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
    renderWindowFunc(mainWindow);
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