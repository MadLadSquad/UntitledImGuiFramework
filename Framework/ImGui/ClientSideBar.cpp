#include "ClientSideBar.hpp"
#include <imgui.h>
#include <Interfaces/WindowInterface.hpp>
#include <Components/Instance.hpp>
#include <Window/WindowUtils.hpp>
#ifdef _WIN32
    #include <windows.h>
    #include <windowsx.h>
    #include <dwmapi.h>
#endif

#define UPDATE_PADDING (width += ImGui::GetItemRectSize().x + style.WindowPadding.x)
#define ADD_PADDING_TO_ITEM_RECT(x, y, z) auto (x) = ImGui::GetItemRectMin(); \
auto (y) = ImGui::GetItemRectMax();                                           \
auto (z) = style.FramePadding;                                                \
(x) += (z);                                                                   \
(y) -= (z);

#ifdef __APPLE__
extern "C" float UImGui_Cocoa_setUpClientSideBarMacOS(UImGui_ClientSideBarFlags flags);
#endif

#ifdef _WIN32
static WNDPROC* getProc() noexcept
{
    static WNDPROC proc;
    return &proc;
}

static bool& hoveringOnNonDragArea() noexcept
{
    static bool bHovering = false;
    return bHovering;
}

static void applyStyle(HWND hwnd) noexcept
{
    // Keep DWM composition and dark frame enabled
    LONG_PTR lStyle = GetWindowLongPtr(hwnd, GWL_STYLE);
    lStyle |= WS_THICKFRAME;
    lStyle &= ~WS_CAPTION;
    SetWindowLongPtr(hwnd, GWL_STYLE, lStyle);

    RECT windowRect;
    GetWindowRect(hwnd, &windowRect);
    int width = windowRect.right - windowRect.left;
    int height = windowRect.bottom - windowRect.top;

    SetWindowPos(hwnd, NULL, 0, 0, width, height, SWP_FRAMECHANGED | SWP_NOMOVE);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
    case WM_NCCALCSIZE:
        // Remove the window's standard sizing border
        if (wParam == TRUE && lParam != NULL)
        {
            NCCALCSIZE_PARAMS* pParams = reinterpret_cast<NCCALCSIZE_PARAMS*>(lParam);
            pParams->rgrc[0].top += 1;
            pParams->rgrc[0].right -= 1;
            pParams->rgrc[0].bottom -= 1;
            pParams->rgrc[0].left += 1;
        }
        return 0;
    case WM_NCPAINT:
        return 0;
    case WM_NCHITTEST:
        {
            const int borderWidth = 2;
            POINTS mousePos = MAKEPOINTS(lParam);
            POINT clientMousePos = { mousePos.x, mousePos.y };
            ScreenToClient(hWnd, &clientMousePos);

            RECT windowRect;
            GetClientRect(hWnd, &windowRect);

            if (clientMousePos.y >= windowRect.bottom - borderWidth)
            {
                if (clientMousePos.x <= borderWidth)
                    return HTBOTTOMLEFT;
                else if (clientMousePos.x >= windowRect.right - borderWidth)
                    return HTBOTTOMRIGHT;
                else
                    return HTBOTTOM;
            }
            else if (clientMousePos.y <= borderWidth)
            {
                if (clientMousePos.x <= borderWidth)
                    return HTTOPLEFT;
                else if (clientMousePos.x >= windowRect.right - borderWidth)
                    return HTTOPRIGHT;
                else
                    return HTTOP;
            }
            else if (clientMousePos.x <= borderWidth)
                return HTLEFT;
            else if (clientMousePos.x >= windowRect.right - borderWidth)
                return HTRIGHT;

            const int titleBarHeight = 32;
            if (!hoveringOnNonDragArea() && clientMousePos.y <= titleBarHeight)
                 return HTCAPTION;
            return HTCLIENT;
        }
    case WM_NCACTIVATE:
        return TRUE;
    case WM_NCLBUTTONDBLCLK:
        ShowWindow(hWnd, IsZoomed(hWnd) ? SW_RESTORE : SW_MAXIMIZE);
        return 0;
    case WM_GETMINMAXINFO:
        {
            MINMAXINFO* mmi = reinterpret_cast<MINMAXINFO*>(lParam);

            // Get the monitor work area (not full area)
            HMONITOR monitor = MonitorFromWindow(hWnd, MONITOR_DEFAULTTONEAREST);
            MONITORINFO info = { sizeof(info) };
            GetMonitorInfo(monitor, &info);

            // Constrain to work area
            mmi->ptMaxPosition.x = info.rcWork.left - info.rcMonitor.left - 1;
            mmi->ptMaxPosition.y = info.rcWork.top - info.rcMonitor.top - 1;
            mmi->ptMaxSize.x = info.rcWork.right - info.rcWork.left + 2;
            mmi->ptMaxSize.y = info.rcWork.bottom - info.rcWork.top + 2;

            // Hack to fill small pixel gaps when the window is maximised
            MARGINS margin = { 1, 1, 1, 1 };
            DwmExtendFrameIntoClientArea(hWnd, &margin);
            return 0;
        }
    case WM_SIZE:
        {
            auto result = CallWindowProc(*getProc(), hWnd, msg, wParam, lParam);
            applyStyle(hWnd);
            return result;
        }
        
    }

    return CallWindowProc(*getProc(), hWnd, msg, wParam, lParam);
}
#endif


void UImGui::ClientSideBar::SetFlags(const ClientSideBarFlags flags) noexcept
{
    getFlags() = flags;
}

bool UImGui::ClientSideBar::Begin() noexcept
{
    BeginManualStyle();
    const bool bRendered = ImGui::BeginMainMenuBar();
    if (bRendered)
        BeginManualRender();
    return bRendered;
}

void UImGui::ClientSideBar::End(const bool bRendered, const FVector4 destructiveColour, const FVector4 destructiveColourActive) noexcept
{
    if (bRendered)
    {
        EndManualRender(destructiveColour, destructiveColourActive);
        ImGui::EndMainMenuBar();
    }
    EndManualStyle();
}

void UImGui::ClientSideBar::BeginManualStyle() noexcept
{
#if defined(__APPLE__) || defined(_WIN32)
    #ifdef __APPLE__
        ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(8.0f, 9.0f));
    #endif
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
#endif
}

void UImGui::ClientSideBar::EndManualStyle() noexcept
{
#if defined(__APPLE__) || defined(_WIN32)
    ImGui::PopStyleVar(
#ifdef __APPLE__
        2
#else
        1
#endif
    );
#endif
}

void UImGui::ClientSideBar::BeginManualRender() noexcept
{
#ifdef __APPLE__
    auto result = UImGui_Cocoa_setUpClientSideBarMacOS(getFlags());
    ImGui::InvisibleButton("uimgui_internal_main_bar_macos_spacing", { result, 9.0f });
    ImGui::SameLine();
#elifdef _WIN32
    static bool bFirst = true;
    if (bFirst)
    {
        auto hwnd = static_cast<HWND>(UImGui::Window::Platform::getNativeWindowHandle());
        
        // Replace with our extended WndProc
        *getProc() = (WNDPROC)GetWindowLongPtr(hwnd, GWLP_WNDPROC);
        SetWindowLongPtr(hwnd, GWLP_WNDPROC, (LONG_PTR)WndProc);

        applyStyle(hwnd);
        bFirst = false;
    }
#endif
    ImGui::BeginGroup();
}

void UImGui::ClientSideBar::EndManualRender(const FVector4 destructiveColour, const FVector4 destructiveColourActive) noexcept
{
    // Create an invisible button that fills up all available space but leaves enough for the buttons
    static float width = 0;
    ImGui::InvisibleButton("uimgui_internal_main_bar_spacing", { ImGui::GetContentRegionAvail().x - width, ImGui::GetFrameHeight() });

    // macOS + Freedesktop. Maximise on double-click. Windows handles that automatically in the callback
#ifndef _WIN32
    if (ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
        Window::getWindowCurrentlyMaximised() ? Window::restoreWindowState() : Window::maximiseWindow();
#endif

    const auto flags = getFlags();

    // On Windows, moving is handled by the window callback
#ifdef _WIN32
    if (flags & UIMGUI_CLIENT_SIDE_BAR_FLAG_MOVEABLE)
    {
        auto handle = static_cast<HWND>(UImGui::Window::Platform::getNativeWindowHandle());
        hoveringOnNonDragArea() = !ImGui::IsItemHovered();
    }
#endif

    // Windows + Freedesktop. We do not render buttons on macOS because we use the native ones
#ifndef __APPLE__
    const auto& style = ImGui::GetStyle();
    width = 0;

    ImGui::PushStyleColor(ImGuiCol_Button, style.Colors[ImGuiCol_MenuBarBg]); // Dear imgui does some fuckery when ImGui::BeginMainMenuBar is called
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, style.Colors[ImGuiCol_HeaderActive]);
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, style.Colors[ImGuiCol_HeaderHovered]);

    if (flags & UIMGUI_CLIENT_SIDE_BAR_FLAG_MINIMISE_BUTTON)
        renderMinimiseButton(width, style);
    if (flags & UIMGUI_CLIENT_SIDE_BAR_FLAG_MAXIMISE_BUTTON)
        renderMaximiseButton(width, style);
    if (flags & UIMGUI_CLIENT_SIDE_BAR_FLAG_CLOSE_BUTTON)
        renderCloseButton(width, style, destructiveColour, destructiveColourActive);

    ImGui::PopStyleColor(3);
#endif
    ImGui::EndGroup();

    // Freedesktop-only. On Windows we use the window callback. On macOS, we make the titlebar area invisible and we
    // move it down to the bar, which means that it's handled automatically.
    //
    // Dragging for X11(The entire client-side bar feature does not work on Wayland in any way)
#if !defined(__APPLE__) && !defined(_WIN32)
    // Mouse dragging code courtesy of https://github.com/ashifolfi/lynx-animator/blob/main/src/MainWindow.cpp
    static bool bDragging = false;
    if (flags & UIMGUI_CLIENT_SIDE_BAR_FLAG_MOVEABLE && ((ImGui::IsMouseDown(ImGuiMouseButton_Left) && ImGui::IsItemActive()) || bDragging))
    {
        if (ImGui::IsMouseDragging(ImGuiMouseButton_Left))
        {
            bDragging = true;
            const auto pos = Window::getCurrentWindowPosition();
            Window::setCurrentWindowPosition({ pos.x + ImGui::GetIO().MouseDelta.x, pos.y + ImGui::GetIO().MouseDelta.y });
        }
        else
            bDragging = false;
    }
#endif
}

UImGui::ClientSideBarFlags& UImGui::ClientSideBar::getFlags()
{
    static ClientSideBarFlags flags = UIMGUI_CLIENT_SIDE_BAR_FLAG_ALL;
    return flags;
}

void UImGui::ClientSideBar::renderMinimiseButton(float& width, const ImGuiStyle& style) noexcept
{
    if (ImGui::SmallButton(" ##uimgui_internal_invisible_minimise_button"))
        Window::iconifyWindow();
    UPDATE_PADDING;
    ADD_PADDING_TO_ITEM_RECT(min, max, padding);

    auto* drawList = ImGui::GetWindowDrawList();
    drawList->AddLine({ min.x, max.y }, max, ImGui::ColorConvertFloat4ToU32(style.Colors[ImGuiCol_Text]), 1.24f);
}

void UImGui::ClientSideBar::renderMaximiseButton(float& width, const ImGuiStyle& style) noexcept
{
    static bool bFirst = true;
    static bool bWindowed = false;
    if (bFirst)
    {
        bWindowed = !Window::getWindowCurrentlyMaximised();
        bFirst = false;
    }

    if (ImGui::SmallButton(" ##uimgui_internal_invisible_maximise_button"))
    {
        if (bWindowed)
            Window::maximiseWindow();
        else
            Window::restoreWindowState();
        bWindowed = !bWindowed;
    }
    UPDATE_PADDING;
    ADD_PADDING_TO_ITEM_RECT(min, max, padding);

    auto* drawList = ImGui::GetWindowDrawList();
    drawList->AddLine(min, { min.x, max.y }, ImGui::ColorConvertFloat4ToU32(style.Colors[ImGuiCol_Text]), 1.24);
    drawList->AddLine(min, { max.x, min.y }, ImGui::ColorConvertFloat4ToU32(style.Colors[ImGuiCol_Text]), 1.24);
    drawList->AddLine(max, { min.x, max.y }, ImGui::ColorConvertFloat4ToU32(style.Colors[ImGuiCol_Text]), 1.24);
    drawList->AddLine(max, { max.x, min.y }, ImGui::ColorConvertFloat4ToU32(style.Colors[ImGuiCol_Text]), 1.24);
}

void UImGui::ClientSideBar::renderCloseButton(float& width, const ImGuiStyle& style, FVector4 destructiveColour, FVector4 destructiveColourActive) noexcept
{
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImGui::ColorConvertFloat4ToU32({ destructiveColour.x, destructiveColour.y, destructiveColour.z, destructiveColour.w }));
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImGui::ColorConvertFloat4ToU32({ destructiveColourActive.x, destructiveColourActive.y, destructiveColourActive.z, destructiveColourActive.w }));

    if (ImGui::SmallButton(" ##uimgui_internal_invisible_close_button"))
        Instance::shutdown();
    UPDATE_PADDING;
    ADD_PADDING_TO_ITEM_RECT(min, max, padding);

    auto* drawList = ImGui::GetWindowDrawList();
    drawList->AddLine(min, max, ImGui::ColorConvertFloat4ToU32(style.Colors[ImGuiCol_Text]), 1.24);
    drawList->AddLine({ min.x, max.y }, { max.x, min.y }, ImGui::ColorConvertFloat4ToU32(style.Colors[ImGuiCol_Text]), 1.24);

    ImGui::PopStyleColor(2);
}
