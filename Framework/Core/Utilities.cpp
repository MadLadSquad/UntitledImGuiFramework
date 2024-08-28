#include "Utilities.hpp"
#include <Global.hpp>
#include <Components/Instance.hpp>
#include <thread>
#ifdef _WIN32
    #include <windows.h>
#elif !__EMSCRIPTEN__
    #include <signal.h>
#endif

#ifdef UIMGUI_PLOTTING_MODULE_ENABLED
    #include <Plotting/ThirdParty/implot/implot_internal.h>
#endif

void UImGui::Utility::sanitiseFilepath(FString& str) noexcept
{
    for (auto& a : str)
        if (a == '\\')
            a = '/';
}

void UImGui::Utility::keyToText(FString& text, const uint16_t& key, const bool bLong) noexcept
{
    static bool bFirst = true;
    static std::array<std::pair<FString, FString>, Keys_UnknownKey + 1> keyStrings{};
    if (bFirst)
    {
        initializeKeyStrings(keyStrings);
        bFirst = false;
    }
    text = bLong ? keyStrings[key].first : keyStrings[key].second;
}

UImGui::FString UImGui::Utility::keyToText(const uint16_t& key, const bool bLong) noexcept
{
    FString txt;
    keyToText(txt, key, bLong);
    return txt;
}

void UImGui::Utility::removeConsole() noexcept
{
#ifdef _WIN32
    HWND cnsl = GetConsoleWindow();
    ShowWindow(cnsl, 0);
    FreeConsole();
#endif
}

UImGui::FString UImGui::Utility::toLower(const String str) noexcept
{
    FString ret = str;
    for (auto& a : ret)
        a = static_cast<char>(tolower(a));
    return ret;
}

void UImGui::Utility::toLower(FString& str) noexcept
{
    for (auto& a : str)
        a = static_cast<char>(tolower(a));
}

UImGui::FString UImGui::Utility::toUpper(const String str) noexcept
{
    FString ret = str;
    for (auto& a : ret)
        a = static_cast<char>(toupper(a));
    return ret;
}

void UImGui::Utility::toUpper(FString& str) noexcept
{
    for (auto& a : str)
        a = static_cast<char>(toupper(a));
}

void UImGui::Utility::loadContext(Global* global, ImGuiContext* imguiContext, const ImGuiMemAllocFunc* imguiAllocFunc,
                                                                              const ImGuiMemFreeFunc* imguiFreeFunc,
                                                                              void** imguiMemoryUserData,
                                                                              void* implotContext) noexcept
{
    Global::get(global);
    ImGui::SetCurrentContext(imguiContext);
    ImGui::SetAllocatorFunctions(*imguiAllocFunc, *imguiFreeFunc, *imguiMemoryUserData);

    if (implotContext != nullptr && Modules::data().plotting)
    {
#ifdef UIMGUI_PLOTTING_MODULE_ENABLED
        ImPlot::SetCurrentContext((ImPlotContext*)implotContext);
#endif
    }
}

void UImGui::Utility::initializeKeyStrings(KeyStringsArrType& keyStrings) noexcept
{
    keyStrings.fill({ "Unknown Key", "Unknown" });

    keyStrings[Keys_Space] = { "Space", "Space" };
    keyStrings[Keys_Apostrophe] = { "Apostrophe", "\'" };
    keyStrings[Keys_Comma] = { "Comma", "," };
    keyStrings[Keys_Minus] = { "Minus", "-" };
    keyStrings[Keys_Period] = { "Period", "." };
    keyStrings[Keys_Slash] = { "Slash", "/" };
    keyStrings[Keys_Zero] = { "Zero", "0" };
    keyStrings[Keys_One] = { "One", "1" };
    keyStrings[Keys_Two] = { "Two", "2" };
    keyStrings[Keys_Three] = { "Three", "3" };
    keyStrings[Keys_Four] = { "Four", "4" };
    keyStrings[Keys_Five] = { "Five", "5" };
    keyStrings[Keys_Six] = { "Six", "6" };
    keyStrings[Keys_Seven] = { "Seven", "7" };
    keyStrings[Keys_Eight] = { "Eight", "8" };
    keyStrings[Keys_Nine] = { "Nine", "9" };
    keyStrings[Keys_Semicolon] = { "Semicolon", ";" };
    keyStrings[Keys_Equal] = { "Equal", "=" };

    keyStrings[Keys_A] = { "A", "A" };
    keyStrings[Keys_B] = { "B", "B" };
    keyStrings[Keys_C] = { "C", "C" };
    keyStrings[Keys_D] = { "D", "D" };
    keyStrings[Keys_E] = { "E", "E" };
    keyStrings[Keys_F] = { "F", "F" };
    keyStrings[Keys_G] = { "G", "G" };
    keyStrings[Keys_H] = { "H", "H" };
    keyStrings[Keys_I] = { "I", "I" };
    keyStrings[Keys_J] = { "J", "J" };
    keyStrings[Keys_K] = { "K", "K" };
    keyStrings[Keys_L] = { "L", "L" };
    keyStrings[Keys_M] = { "M", "M" };
    keyStrings[Keys_N] = { "N", "N" };
    keyStrings[Keys_O] = { "O", "O" };
    keyStrings[Keys_P] = { "P", "P" };
    keyStrings[Keys_Q] = { "Q", "Q" };
    keyStrings[Keys_R] = { "R", "R" };
    keyStrings[Keys_S] = { "S", "S" };
    keyStrings[Keys_T] = { "T", "T" };
    keyStrings[Keys_U] = { "U", "U" };
    keyStrings[Keys_V] = { "V", "V" };
    keyStrings[Keys_W] = { "W", "W" };
    keyStrings[Keys_X] = { "X", "X" };
    keyStrings[Keys_Y] = { "Y", "Y" };
    keyStrings[Keys_Z] = { "Z", "Z" };

    keyStrings[Keys_LeftBracket] = { "Left Bracket", "]" };
    keyStrings[Keys_Backslash] = { "Backslash", "\\" };
    keyStrings[Keys_RightBracket] = { "Left Bracket", "[" };
    keyStrings[Keys_GraveAccent] = { "Grave Accent", "`" };
    keyStrings[Keys_WorldOne] = { "World One", "Wld1" };
    keyStrings[Keys_WorldTwo] = { "World Two", "Wld2" };

    keyStrings[Keys_Escape] = { "Escape", "Esc" };
    keyStrings[Keys_Enter] = { "Enter", "Enter" };
    keyStrings[Keys_Tab] = { "Tab", "Tab" };
    keyStrings[Keys_Backspace] = { "Backspace", "Backspace" };
    keyStrings[Keys_Insert] = { "Insert", "Ins" };
    keyStrings[Keys_Delete] = { "Delete", "Del" };

    keyStrings[Keys_RightArrow] = { "Right Arrow", "RArr" };
    keyStrings[Keys_LeftArrow] = { "Left Arrow", "LArr" };
    keyStrings[Keys_DownArrow] = { "Down Arrow", "DwnArr" };
    keyStrings[Keys_UpArrow] = { "Up Arrow", "UpArr" };

    keyStrings[Keys_PageUp] = { "Page Up", "PgUp" };
    keyStrings[Keys_PageDown] = { "Page Down", "PgDn" };
    keyStrings[Keys_Home] = { "Home", "Home" };
    keyStrings[Keys_End] = { "End", "End" };
    keyStrings[Keys_CapsLock] = { "Caps Lock", "CapsL" };
    keyStrings[Keys_ScrollLock] = { "Scroll Lock", "ScrL" };
    keyStrings[Keys_NumLock] = { "Num Lock", "NumL" };
    keyStrings[Keys_PrintScreen] = { "Print Screen", "Prtsc" };
    keyStrings[Keys_Pause] = { "Pause", "Pause" };

    keyStrings[Keys_F1] = { "F1", "F1" };
    keyStrings[Keys_F2] = { "F2", "F2" };
    keyStrings[Keys_F3] = { "F3", "F3" };
    keyStrings[Keys_F4] = { "F4", "F4" };
    keyStrings[Keys_F5] = { "F5", "F5" };
    keyStrings[Keys_F6] = { "F6", "F6" };
    keyStrings[Keys_F7] = { "F7", "F7" };
    keyStrings[Keys_F8] = { "F8", "F8" };
    keyStrings[Keys_F9] = { "F9", "F9" };
    keyStrings[Keys_F10] = { "F10", "F10" };
    keyStrings[Keys_F11] = { "F11", "F11" };
    keyStrings[Keys_F12] = { "F12", "F12" };
    keyStrings[Keys_F13] = { "F13", "F13" };
    keyStrings[Keys_F14] = { "F14", "F14" };
    keyStrings[Keys_F15] = { "F15", "F15" };
    keyStrings[Keys_F16] = { "F16", "F16" };
    keyStrings[Keys_F17] = { "F17", "F17" };
    keyStrings[Keys_F18] = { "F18", "F18" };
    keyStrings[Keys_F19] = { "F19", "F19" };
    keyStrings[Keys_F20] = { "F20", "F20" };
    keyStrings[Keys_F21] = { "F21", "F21" };
    keyStrings[Keys_F22] = { "F22", "F22" };
    keyStrings[Keys_F23] = { "F23", "F23" };
    keyStrings[Keys_F24] = { "F24", "F24" };
    keyStrings[Keys_F25] = { "F25", "F25" };

    keyStrings[Keys_NumPadZero] = { "Numpad Zero", "Num 0" };
    keyStrings[Keys_NumPadOne] = { "Numpad One", "Num 1" };
    keyStrings[Keys_NumPadTwo] = { "Numpad Two", "Num 2" };
    keyStrings[Keys_NumPadThree] = { "Numpad Three", "Num 3" };
    keyStrings[Keys_NumPadFour] = { "Numpad Four", "Num 4" };
    keyStrings[Keys_NumPadFive] = { "Numpad Five", "Num 5" };
    keyStrings[Keys_NumPadSix] = { "Numpad Six", "Num 6" };
    keyStrings[Keys_NumPadSeven] = { "Numpad Seven", "Num 7" };
    keyStrings[Keys_NumPadEight] = { "Numpad Eight", "Num 8" };
    keyStrings[Keys_NumPadNine] = { "Numpad Nine", "Num 9" };
    keyStrings[Keys_NumPadDecimal] = { "Numpad Decimal", "Num ." };
    keyStrings[Keys_NumPadDivide] = { "Numpad Divide", "Num /" };
    keyStrings[Keys_NumPadMultiply] = { "Numpad Multiply", "Num *" };
    keyStrings[Keys_NumPadSubtract] = { "Numpad Subtract", "Num -" };
    keyStrings[Keys_NumPadAdd] = { "Numpad Add", "Num +" };
    keyStrings[Keys_NumPadEnter] = { "Numpad Enter", "Num Enter" };
    keyStrings[Keys_NumPadEqual] = { "Numpad Equal", "Num =" };

    keyStrings[Keys_LeftShift] = { "Left Shift", "LShift" };
    keyStrings[Keys_LeftAlt] = { "Left Alt", "LAlt" };
    keyStrings[Keys_LeftControl] = { "Left Control", "LCTRL" };
    keyStrings[Keys_LeftSuper] = { "Left Super/CMD/Windows", "LSuper" };

    keyStrings[Keys_RightShift] = { "Right Shift", "RShift" };
    keyStrings[Keys_RightControl] = { "Right Control", "RCTRL" };
    keyStrings[Keys_RightAlt] = { "Right Alt", "RAlt" };
    keyStrings[Keys_RightSuper] = { "Right Super/CMD/Windows", "RSuper" };
    keyStrings[Keys_Menu] = { "Menu", "Menu" };

    keyStrings[Keys_MouseButtonLeft] = { "Mouse Button 1/Left", "LMB" };
    keyStrings[Keys_MouseButtonRight] = { "Mouse Button 2/Right", "RMB" };
    keyStrings[Keys_MouseButtonMiddle] = { "Mouse Button 3/Middle", "MMB" };
    keyStrings[Keys_MouseButton4] = { "Mouse Button 4", "MB4" };
    keyStrings[Keys_MouseButton5] = { "Mouse Button 5", "MB5" };
    keyStrings[Keys_MouseButton6] = { "Mouse Button 6", "MB6" };
    keyStrings[Keys_MouseButton7] = { "Mouse Button 7", "MB7" };
    keyStrings[Keys_MouseButton8] = { "Mouse Button 8/Last", "MB8" };

    keyStrings[Keys_None] = { "None", "None" };
}

void UImGui::Utility::keyToText(FString& text, const InputAction& action, const bool bLong) noexcept
{
    for (auto& a : action.keyCodes)
        text += keyToText(a, bLong) + "+";
    text.pop_back();
}

UImGui::FString UImGui::Utility::keyToText(const InputAction& action, const bool bLong) noexcept
{
    FString ret;
    keyToText(ret, action, bLong);
    return ret;
}

void UImGui::Utility::sleep(const uint64_t milliseconds) noexcept
{
    std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
}

#ifdef _WIN32
    #define SIGTERM 15
#endif

void UImGui::Utility::interruptSignalHandler() noexcept
{
#ifndef __EMSCRIPTEN__
#ifdef _WIN32
    if (!SetConsoleCtrlHandler([](DWORD signal) -> BOOL WINAPI {
        if (signal == CTRL_C_EVENT)
        {
#else
    struct sigaction data{ .sa_flags = SA_SIGINFO };
    data.sa_sigaction = [](int, siginfo_t*, void*) -> void {
#endif
            static bool bFirst = true;
            if (bFirst)
            {
                Logger::log("SIGINT interrupted. Press CTRL+C again to forcefully terminate it!", UVK_LOG_TYPE_WARNING);
                Instance::shutdown();
                bFirst = false;
#ifdef _WIN32
                return TRUE;
#else
                return;
#endif
            }
            exit(SIGTERM);
#ifdef _WIN32
            return TRUE;
        }
        return FALSE;
    }, TRUE))
    {
        Logger::log("Couldn't setup the Windows interrupt handler!", UVK_LOG_TYPE_WARNING);
    }
#else
    },

    sigaction(SIGINT, &data, nullptr);
    sigaction(SIGTERM, &data, nullptr);
#endif
#endif
}
