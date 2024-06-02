#include "Utilities.hpp"
#include <Global.hpp>
#include <Instance.hpp>
#include <C/Internal/Keys.h>
#include <thread>
#ifdef _WIN32
    #include <windows.h>
#else
    #include <signal.h>
#endif

void UImGui::Utility::sanitiseFilepath(FString& str) noexcept
{
    for (auto& a : str)
        if (a == '\\')
            a = '/';
}

void UImGui::Utility::keyToText(UImGui::FString& text, const uint16_t& key, bool bLong) noexcept
{
    static bool bFirst = true;
    static std::array<std::pair<FString, FString>, Keys::UnknownKey + 1> keyStrings{};
    if (bFirst)
    {
        initializeKeyStrings(keyStrings);
        bFirst = false;
    }
    text = bLong ? keyStrings[key].first : keyStrings[key].second;
}

UImGui::FString UImGui::Utility::keyToText(const uint16_t& key, bool bLong) noexcept
{
    FString txt;
    keyToText(txt, key, bLong);
    return txt;
}

UImGui::Global& UImGui::Utility::getGlobal() noexcept
{
    return internalGlobal;
}

void UImGui::Utility::removeConsole() noexcept
{
#ifdef _WIN32
    HWND cnsl = GetConsoleWindow();
    ShowWindow(cnsl, 0);
    FreeConsole();
#endif
}

UImGui::FString UImGui::Utility::toLower(UImGui::String str) noexcept
{
    FString ret = str;
    for (auto& a : ret)
        a = static_cast<char>(tolower(a));
    return ret;
}

void UImGui::Utility::toLower(UImGui::FString& str) noexcept
{
    for (auto& a : str)
        a = static_cast<char>(tolower(a));
}

UImGui::FString UImGui::Utility::toUpper(UImGui::String str) noexcept
{
    FString ret = str;
    for (auto& a : ret)
        a = static_cast<char>(toupper(a));
    return ret;
}

void UImGui::Utility::toUpper(UImGui::FString& str) noexcept
{
    for (auto& a : str)
        a = static_cast<char>(toupper(a));
}

void UImGui::Utility::initializeKeyStrings(KeyStringsArrType& keyStrings) noexcept
{
    keyStrings.fill({ "Unknown Key", "Unknown" });

    keyStrings[Keys::Space] = { "Space", "Space" };
    keyStrings[Keys::Apostrophe] = { "Apostrophe", "\'" };
    keyStrings[Keys::Comma] = { "Comma", "," };
    keyStrings[Keys::Minus] = { "Minus", "-" };
    keyStrings[Keys::Period] = { "Period", "." };
    keyStrings[Keys::Slash] = { "Slash", "/" };
    keyStrings[Keys::Zero] = { "Zero", "0" };
    keyStrings[Keys::One] = { "One", "1" };
    keyStrings[Keys::Two] = { "Two", "2" };
    keyStrings[Keys::Three] = { "Three", "3" };
    keyStrings[Keys::Four] = { "Four", "4" };
    keyStrings[Keys::Five] = { "Five", "5" };
    keyStrings[Keys::Six] = { "Six", "6" };
    keyStrings[Keys::Seven] = { "Seven", "7" };
    keyStrings[Keys::Eight] = { "Eight", "8" };
    keyStrings[Keys::Nine] = { "Nine", "9" };
    keyStrings[Keys::Semicolon] = { "Semicolon", ";" };
    keyStrings[Keys::Equal] = { "Equal", "=" };

    keyStrings[Keys::A] = { "A", "A" };
    keyStrings[Keys::B] = { "B", "B" };
    keyStrings[Keys::C] = { "C", "C" };
    keyStrings[Keys::D] = { "D", "D" };
    keyStrings[Keys::E] = { "E", "E" };
    keyStrings[Keys::F] = { "F", "F" };
    keyStrings[Keys::G] = { "G", "G" };
    keyStrings[Keys::H] = { "H", "H" };
    keyStrings[Keys::I] = { "I", "I" };
    keyStrings[Keys::J] = { "J", "J" };
    keyStrings[Keys::K] = { "K", "K" };
    keyStrings[Keys::L] = { "L", "L" };
    keyStrings[Keys::M] = { "M", "M" };
    keyStrings[Keys::N] = { "N", "N" };
    keyStrings[Keys::O] = { "O", "O" };
    keyStrings[Keys::P] = { "P", "P" };
    keyStrings[Keys::Q] = { "Q", "Q" };
    keyStrings[Keys::R] = { "R", "R" };
    keyStrings[Keys::S] = { "S", "S" };
    keyStrings[Keys::T] = { "T", "T" };
    keyStrings[Keys::U] = { "U", "U" };
    keyStrings[Keys::V] = { "V", "V" };
    keyStrings[Keys::W] = { "W", "W" };
    keyStrings[Keys::X] = { "X", "X" };
    keyStrings[Keys::Y] = { "Y", "Y" };
    keyStrings[Keys::Z] = { "Z", "Z" };

    keyStrings[Keys::LeftBracket] = { "Left Bracket", "]" };
    keyStrings[Keys::Backslash] = { "Backslash", "\\" };
    keyStrings[Keys::RightBracket] = { "Left Bracket", "[" };
    keyStrings[Keys::GraveAccent] = { "Grave Accent", "`" };
    keyStrings[Keys::WorldOne] = { "World One", "Wld1" };
    keyStrings[Keys::WorldTwo] = { "World Two", "Wld2" };

    keyStrings[Keys::Escape] = { "Escape", "Esc" };
    keyStrings[Keys::Enter] = { "Enter", "Enter" };
    keyStrings[Keys::Tab] = { "Tab", "Tab" };
    keyStrings[Keys::Backspace] = { "Backspace", "Backspace" };
    keyStrings[Keys::Insert] = { "Insert", "Ins" };
    keyStrings[Keys::Delete] = { "Delete", "Del" };

    keyStrings[Keys::RightArrow] = { "Right Arrow", "RArr" };
    keyStrings[Keys::LeftArrow] = { "Left Arrow", "LArr" };
    keyStrings[Keys::DownArrow] = { "Down Arrow", "DwnArr" };
    keyStrings[Keys::UpArrow] = { "Up Arrow", "UpArr" };

    keyStrings[Keys::PageUp] = { "Page Up", "PgUp" };
    keyStrings[Keys::PageDown] = { "Page Down", "PgDn" };
    keyStrings[Keys::Home] = { "Home", "Home" };
    keyStrings[Keys::End] = { "End", "End" };
    keyStrings[Keys::CapsLock] = { "Caps Lock", "CapsL" };
    keyStrings[Keys::ScrollLock] = { "Scroll Lock", "ScrL" };
    keyStrings[Keys::NumLock] = { "Num Lock", "NumL" };
    keyStrings[Keys::PrintScreen] = { "Print Screen", "Prtsc" };
    keyStrings[Keys::Pause] = { "Pause", "Pause" };

    keyStrings[Keys::F1] = { "F1", "F1" };
    keyStrings[Keys::F2] = { "F2", "F2" };
    keyStrings[Keys::F3] = { "F3", "F3" };
    keyStrings[Keys::F4] = { "F4", "F4" };
    keyStrings[Keys::F5] = { "F5", "F5" };
    keyStrings[Keys::F6] = { "F6", "F6" };
    keyStrings[Keys::F7] = { "F7", "F7" };
    keyStrings[Keys::F8] = { "F8", "F8" };
    keyStrings[Keys::F9] = { "F9", "F9" };
    keyStrings[Keys::F10] = { "F10", "F10" };
    keyStrings[Keys::F11] = { "F11", "F11" };
    keyStrings[Keys::F12] = { "F12", "F12" };
    keyStrings[Keys::F13] = { "F13", "F13" };
    keyStrings[Keys::F14] = { "F14", "F14" };
    keyStrings[Keys::F15] = { "F15", "F15" };
    keyStrings[Keys::F16] = { "F16", "F16" };
    keyStrings[Keys::F17] = { "F17", "F17" };
    keyStrings[Keys::F18] = { "F18", "F18" };
    keyStrings[Keys::F19] = { "F19", "F19" };
    keyStrings[Keys::F20] = { "F20", "F20" };
    keyStrings[Keys::F21] = { "F21", "F21" };
    keyStrings[Keys::F22] = { "F22", "F22" };
    keyStrings[Keys::F23] = { "F23", "F23" };
    keyStrings[Keys::F24] = { "F24", "F24" };
    keyStrings[Keys::F25] = { "F25", "F25" };

    keyStrings[Keys::NumPadZero] = { "Numpad Zero", "Num 0" };
    keyStrings[Keys::NumPadOne] = { "Numpad One", "Num 1" };
    keyStrings[Keys::NumPadTwo] = { "Numpad Two", "Num 2" };
    keyStrings[Keys::NumPadThree] = { "Numpad Three", "Num 3" };
    keyStrings[Keys::NumPadFour] = { "Numpad Four", "Num 4" };
    keyStrings[Keys::NumPadFive] = { "Numpad Five", "Num 5" };
    keyStrings[Keys::NumPadSix] = { "Numpad Six", "Num 6" };
    keyStrings[Keys::NumPadSeven] = { "Numpad Seven", "Num 7" };
    keyStrings[Keys::NumPadEight] = { "Numpad Eight", "Num 8" };
    keyStrings[Keys::NumPadNine] = { "Numpad Nine", "Num 9" };
    keyStrings[Keys::NumPadDecimal] = { "Numpad Decimal", "Num ." };
    keyStrings[Keys::NumPadDivide] = { "Numpad Divide", "Num /" };
    keyStrings[Keys::NumPadMultiply] = { "Numpad Multiply", "Num *" };
    keyStrings[Keys::NumPadSubtract] = { "Numpad Subtract", "Num -" };
    keyStrings[Keys::NumPadAdd] = { "Numpad Add", "Num +" };
    keyStrings[Keys::NumPadEnter] = { "Numpad Enter", "Num Enter" };
    keyStrings[Keys::NumPadEqual] = { "Numpad Equal", "Num =" };

    keyStrings[Keys::LeftShift] = { "Left Shift", "LShift" };
    keyStrings[Keys::LeftAlt] = { "Left Alt", "LAlt" };
    keyStrings[Keys::LeftControl] = { "Left Control", "LCTRL" };
    keyStrings[Keys::LeftSuper] = { "Left Super/CMD/Windows", "LSuper" };

    keyStrings[Keys::RightShift] = { "Right Shift", "RShift" };
    keyStrings[Keys::RightControl] = { "Right Control", "RCTRL" };
    keyStrings[Keys::RightAlt] = { "Right Alt", "RAlt" };
    keyStrings[Keys::RightSuper] = { "Right Super/CMD/Windows", "RSuper" };
    keyStrings[Keys::Menu] = { "Menu", "Menu" };

    keyStrings[Keys::MouseButtonLeft] = { "Mouse Button 1/Left", "LMB" };
    keyStrings[Keys::MouseButtonRight] = { "Mouse Button 2/Right", "RMB" };
    keyStrings[Keys::MouseButtonMiddle] = { "Mouse Button 3/Middle", "MMB" };
    keyStrings[Keys::MouseButton4] = { "Mouse Button 4", "MB4" };
    keyStrings[Keys::MouseButton5] = { "Mouse Button 5", "MB5" };
    keyStrings[Keys::MouseButton6] = { "Mouse Button 6", "MB6" };
    keyStrings[Keys::MouseButton7] = { "Mouse Button 7", "MB7" };
    keyStrings[Keys::MouseButton8] = { "Mouse Button 8/Last", "MB8" };

    keyStrings[Keys::None] = { "None", "None" };
}

void UImGui::Utility::keyToText(UImGui::FString& text, const UImGui::InputAction& action, bool bLong) noexcept
{
    for (auto& a : action.keyCodes)
        text += keyToText(a, bLong) + "+";
    text.pop_back();
}

UImGui::FString UImGui::Utility::keyToText(const UImGui::InputAction& action, bool bLong) noexcept
{
    FString ret;
    keyToText(ret, action, bLong);
    return ret;
}

void UImGui::Utility::sleep(uint64_t milliseconds) noexcept
{
    std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
}

#ifdef _WIN32
    #define SIGTERM 15
#endif

void UImGui::Utility::interruptSignalHandler() noexcept
{
#ifdef _WIN32
    if (!SetConsoleCtrlHandler([](DWORD signal) -> BOOL WINAPI {
        if (signal == CTRL_C_EVENT)
        {
#else
    struct sigaction data{ .sa_flags = SA_SIGINFO };
    data.sa_sigaction = [](int signal, siginfo_t* info, void* next) -> void {
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
#endif
}
