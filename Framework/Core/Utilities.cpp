#include "Utilities.hpp"
#include <Global.hpp>
#include <Events/Keys.hpp>
#ifdef _WIN32
    #include <windows.h>
#endif

void UImGui::Utility::sanitiseFilepath(FString& str) noexcept
{
    for (auto& a : str)
        if (a == '\\')
            a = '/';
}

void UImGui::Utility::keyToText(UImGui::FString& text, const uint16_t& key, bool bLong) noexcept
{
    if (bLong)
    {
        switch (key)
        {
        case Keys::UnknownKey:
            text = "Unknown Key";
            break;
        case Keys::Space:
            text = "Space";
            break;
        case Keys::Apostrophe:
            text = "Apostrophe";
            break;
        case Keys::Comma:
            text = "Comma";
            break;
        case Keys::Minus:
            text = "Minus";
            break;
        case Keys::Period:
            text = "Period";
            break;
        case Keys::Slash:
            text = "Slash";
            break;
        case Keys::Zero:
            text = "Zero";
            break;
        case Keys::One:
            text = "One";
            break;
        case Keys::Two:
            text = "Two";
            break;
        case Keys::Three:
            text = "Three";
            break;
        case Keys::Four:
            text = "Four";
            break;
        case Keys::Five:
            text = "Five";
            break;
        case Keys::Six:
            text = "Six";
            break;
        case Keys::Seven:
            text = "Seven";
            break;
        case Keys::Eight:
            text = "Eight";
            break;
        case Keys::Nine:
            text = "Nine";
            break;
        case Keys::Semicolon:
            text = "Semicolon";
            break;
        case Keys::Equal:
            text = "Equal";
            break;
        case Keys::A:
            text = "A";
            break;
        case Keys::B:
            text = "B";
            break;
        case Keys::C:
            text = "C";
            break;
        case Keys::D:
            text = "D";
            break;
        case Keys::E:
            text = "E";
            break;
        case Keys::F:
            text = "F";
            break;
        case Keys::G:
            text = "G";
            break;
        case Keys::H:
            text = "H";
            break;
        case Keys::I:
            text = "I";
            break;
        case Keys::J:
            text = "J";
            break;
        case Keys::K:
            text = "K";
            break;
        case Keys::L:
            text = "L";
            break;
        case Keys::M:
            text = "M";
            break;
        case Keys::N:
            text = "N";
            break;
        case Keys::O:
            text = "O";
            break;
        case Keys::P:
            text = "P";
            break;
        case Keys::Q:
            text = "Q";
            break;
        case Keys::R:
            text = "R";
            break;
        case Keys::S:
            text = "S";
            break;
        case Keys::T:
            text = "T";
            break;
        case Keys::U:
            text = "U";
            break;
        case Keys::V:
            text = "V";
            break;
        case Keys::W:
            text = "W";
            break;
        case Keys::X:
            text = "X";
            break;
        case Keys::Y:
            text = "Y";
            break;
        case Keys::Z:
            text = "Z";
            break;
        case Keys::LeftBracket:
            text = "Left Bracket";
            break;
        case Keys::Backslash:
            text = "Backslash";
            break;
        case Keys::RightBracket:
            text = "Right Bracket";
            break;
        case Keys::GraveAccent:
            text = "GraveAccent";
            break;
        case Keys::WorldOne:
            text = "World One";
            break;
        case Keys::WorldTwo:
            text = "World Two";
            break;
        case Keys::Escape:
            text = "Escape";
            break;
        case Keys::Enter:
            text = "Enter";
            break;
        case Keys::Tab:
            text = "Tab";
            break;
        case Keys::Backspace:
            text = "Backspace";
            break;
        case Keys::Insert:
            text = "Insert";
            break;
        case Keys::Delete:
            text = "Delete";
            break;
        case Keys::RightArrow:
            text = "Right Arrow";
            break;
        case Keys::LeftArrow:
            text = "Left Arrow";
            break;
        case Keys::DownArrow:
            text = "Down Arrow";
            break;
        case Keys::UpArrow:
            text = "Up Arrow";
            break;
        case Keys::PageUp:
            text = "Page Up";
            break;
        case Keys::PageDown:
            text = "Page Down";
            break;
        case Keys::Home:
            text = "World Two";
            break;
        case Keys::End:
            text = "End";
            break;
        case Keys::CapsLock:
            text = "Caps Lock";
            break;
        case Keys::ScrollLock:
            text = "Scroll Lock";
            break;
        case Keys::NumLock:
            text = "Num Lock";
            break;
        case Keys::PrintScreen:
            text = "Print Screen";
            break;
        case Keys::Pause:
            text = "Pause";
            break;
        case Keys::F1:
            text = "F1";
            break;
        case Keys::F2:
            text = "F2";
            break;
        case Keys::F3:
            text = "F3";
            break;
        case Keys::F4:
            text = "F4";
            break;
        case Keys::F5:
            text = "F5";
            break;
        case Keys::F6:
            text = "F6";
            break;
        case Keys::F7:
            text = "F7";
            break;
        case Keys::F8:
            text = "F8";
            break;
        case Keys::F9:
            text = "F9";
            break;
        case Keys::F10:
            text = "F10";
            break;
        case Keys::F11:
            text = "F11";
            break;
        case Keys::F12:
            text = "F12";
            break;
        case Keys::F13:
            text = "F13";
            break;
        case Keys::F14:
            text = "F14";
            break;
        case Keys::F15:
            text = "F15";
            break;
        case Keys::F16:
            text = "F16";
            break;
        case Keys::F17:
            text = "F17";
            break;
        case Keys::F18:
            text = "F18";
            break;
        case Keys::F19:
            text = "F19";
            break;
        case Keys::F20:
            text = "F20";
            break;
        case Keys::F21:
            text = "F21";
            break;
        case Keys::F22:
            text = "F22";
            break;
        case Keys::F23:
            text = "F23";
            break;
        case Keys::F24:
            text = "F24";
            break;
        case Keys::F25:
            text = "F25";
            break;
        case Keys::NumPadZero:
            text = "Numpad Zero";
            break;
        case Keys::NumPadOne:
            text = "Numpad One";
            break;
        case Keys::NumPadTwo:
            text = "Numpad Two";
            break;
        case Keys::NumPadThree:
            text = "Numpad Three";
            break;
        case Keys::NumPadFour:
            text = "Numpad Four";
            break;
        case Keys::NumPadFive:
            text = "Numpad Five";
            break;
        case Keys::NumPadSix:
            text = "Numpad Six";
            break;
        case Keys::NumPadSeven:
            text = "Numpad Seven";
            break;
        case Keys::NumPadEight:
            text = "Numpad Eight";
            break;
        case Keys::NumPadNine:
            text = "Numpad Nine";
            break;
        case Keys::NumPadDecimal:
            text = "Numpad Decimal";
            break;
        case Keys::NumPadDivide:
            text = "Numpad Divide";
            break;
        case Keys::NumPadMultiply:
            text = "Numpad Multiply";
            break;
        case Keys::NumPadSubtract:
            text = "Numpad Subtract";
            break;
        case Keys::NumPadAdd:
            text = "Numpad Add";
            break;
        case Keys::NumPadEnter:
            text = "Numpad Enter";
            break;
        case Keys::NumPadEqual:
            text = "Numpad Equal";
            break;
        case Keys::LeftShift:
            text = "Left Shift";
            break;
        case Keys::LeftAlt:
            text = "Left Alt";
            break;
        case Keys::LeftControl:
            text = "Left Control";
            break;
        case Keys::LeftSuper:
            text = "Left Super/CMD/Windows";
            break;
        case Keys::RightShift:
            text = "Right Shift";
            break;
        case Keys::RightControl:
            text = "Right Control";
            break;
        case Keys::RightAlt:
            text = "Right Alt";
            break;
        case Keys::RightSuper:
            text = "Right Super/CMD/Windows";
            break;
        case Keys::Menu:
            text = "Menu";
            break;
        case Keys::MouseButtonLeft:
            text = "Mouse Button 1/Left";
            break;
        case Keys::MouseButtonRight:
            text = "Mouse Button 2/Right";
            break;
        case Keys::MouseButtonMiddle:
            text = "Mouse Button 3/Middle";
            break;
        case Keys::MouseButton4:
            text = "Mouse Button 4";
            break;
        case Keys::MouseButton5:
            text = "Mouse Button 5";
            break;
        case Keys::MouseButton6:
            text = "Mouse Button 6";
            break;
        case Keys::MouseButton7:
            text = "Mouse Button 7";
            break;
        case Keys::MouseButton8:
            text = "Mouse Button 8/Last";
            break;
        default:
            text = "Unknown Key";
            break;
        }
    }
    else
    {
        switch (key)
        {
        case Keys::UnknownKey:
            text = "Unknown Key";
            break;
        case Keys::Space:
            text = "Space";
            break;
        case Keys::Apostrophe:
            text = "\'";
            break;
        case Keys::Comma:
            text = ",";
            break;
        case Keys::Minus:
            text = "-";
            break;
        case Keys::Period:
            text = ".";
            break;
        case Keys::Slash:
            text = "/";
            break;
        case Keys::Zero:
            text = "0";
            break;
        case Keys::One:
            text = "1";
            break;
        case Keys::Two:
            text = "2";
            break;
        case Keys::Three:
            text = "3";
            break;
        case Keys::Four:
            text = "4";
            break;
        case Keys::Five:
            text = "5";
            break;
        case Keys::Six:
            text = "6";
            break;
        case Keys::Seven:
            text = "7";
            break;
        case Keys::Eight:
            text = "8";
            break;
        case Keys::Nine:
            text = "9";
            break;
        case Keys::Semicolon:
            text = ";";
            break;
        case Keys::Equal:
            text = "=";
            break;
        case Keys::A:
            text = "A";
            break;
        case Keys::B:
            text = "B";
            break;
        case Keys::C:
            text = "C";
            break;
        case Keys::D:
            text = "D";
            break;
        case Keys::E:
            text = "E";
            break;
        case Keys::F:
            text = "F";
            break;
        case Keys::G:
            text = "G";
            break;
        case Keys::H:
            text = "H";
            break;
        case Keys::I:
            text = "I";
            break;
        case Keys::J:
            text = "J";
            break;
        case Keys::K:
            text = "K";
            break;
        case Keys::L:
            text = "L";
            break;
        case Keys::M:
            text = "M";
            break;
        case Keys::N:
            text = "N";
            break;
        case Keys::O:
            text = "O";
            break;
        case Keys::P:
            text = "P";
            break;
        case Keys::Q:
            text = "Q";
            break;
        case Keys::R:
            text = "R";
            break;
        case Keys::S:
            text = "S";
            break;
        case Keys::T:
            text = "T";
            break;
        case Keys::U:
            text = "U";
            break;
        case Keys::V:
            text = "V";
            break;
        case Keys::W:
            text = "W";
            break;
        case Keys::X:
            text = "X";
            break;
        case Keys::Y:
            text = "Y";
            break;
        case Keys::Z:
            text = "Z";
            break;
        case Keys::LeftBracket:
            text = "{";
            break;
        case Keys::Backslash:
            text = "\\";
            break;
        case Keys::RightBracket:
            text = "}";
            break;
        case Keys::GraveAccent:
            text = "`";
            break;
        case Keys::WorldOne:
            text = "Wld1";
            break;
        case Keys::WorldTwo:
            text = "Wld2";
            break;
        case Keys::Escape:
            text = "Esc";
            break;
        case Keys::Enter:
            text = "Enter";
            break;
        case Keys::Tab:
            text = "Tab";
            break;
        case Keys::Backspace:
            text = "Backspace";
            break;
        case Keys::Insert:
            text = "Ins";
            break;
        case Keys::Delete:
            text = "Del";
            break;
        case Keys::RightArrow:
            text = "RightArr";
            break;
        case Keys::LeftArrow:
            text = "LeftArr";
            break;
        case Keys::DownArrow:
            text = "DwArr";
            break;
        case Keys::UpArrow:
            text = "UpArr";
            break;
        case Keys::PageUp:
            text = "PgUp";
            break;
        case Keys::PageDown:
            text = "PgDn";
            break;
        case Keys::Home:
            text = "World1";
            break;
        case Keys::End:
            text = "End";
            break;
        case Keys::CapsLock:
            text = "CapsLk";
            break;
        case Keys::ScrollLock:
            text = "ScrollLk";
            break;
        case Keys::NumLock:
            text = "NumLk";
            break;
        case Keys::PrintScreen:
            text = "PTRSC";
            break;
        case Keys::Pause:
            text = "Pause";
            break;
        case Keys::F1:
            text = "F1";
            break;
        case Keys::F2:
            text = "F2";
            break;
        case Keys::F3:
            text = "F3";
            break;
        case Keys::F4:
            text = "F4";
            break;
        case Keys::F5:
            text = "F5";
            break;
        case Keys::F6:
            text = "F6";
            break;
        case Keys::F7:
            text = "F7";
            break;
        case Keys::F8:
            text = "F8";
            break;
        case Keys::F9:
            text = "F9";
            break;
        case Keys::F10:
            text = "F10";
            break;
        case Keys::F11:
            text = "F11";
            break;
        case Keys::F12:
            text = "F12";
            break;
        case Keys::F13:
            text = "F13";
            break;
        case Keys::F14:
            text = "F14";
            break;
        case Keys::F15:
            text = "F15";
            break;
        case Keys::F16:
            text = "F16";
            break;
        case Keys::F17:
            text = "F17";
            break;
        case Keys::F18:
            text = "F18";
            break;
        case Keys::F19:
            text = "F19";
            break;
        case Keys::F20:
            text = "F20";
            break;
        case Keys::F21:
            text = "F21";
            break;
        case Keys::F22:
            text = "F22";
            break;
        case Keys::F23:
            text = "F23";
            break;
        case Keys::F24:
            text = "F24";
            break;
        case Keys::F25:
            text = "F25";
            break;
        case Keys::NumPadZero:
            text = "Num0";
            break;
        case Keys::NumPadOne:
            text = "Num1";
            break;
        case Keys::NumPadTwo:
            text = "Num2";
            break;
        case Keys::NumPadThree:
            text = "Num3";
            break;
        case Keys::NumPadFour:
            text = "Num4";
            break;
        case Keys::NumPadFive:
            text = "Num5";
            break;
        case Keys::NumPadSix:
            text = "Num6";
            break;
        case Keys::NumPadSeven:
            text = "Num7";
            break;
        case Keys::NumPadEight:
            text = "Num8";
            break;
        case Keys::NumPadNine:
            text = "Num9";
            break;
        case Keys::NumPadDecimal:
            text = "Num.";
            break;
        case Keys::NumPadDivide:
            text = "Num/";
            break;
        case Keys::NumPadMultiply:
            text = "Num*";
            break;
        case Keys::NumPadSubtract:
            text = "Num-";
            break;
        case Keys::NumPadAdd:
            text = "Num+";
            break;
        case Keys::NumPadEnter:
            text = "NumEnter";
            break;
        case Keys::NumPadEqual:
            text = "Num=";
            break;
        case Keys::LeftShift:
            text = "LShift";
            break;
        case Keys::LeftAlt:
            text = "LAlt";
            break;
        case Keys::LeftControl:
            text = "LCTRL";
            break;
        case Keys::LeftSuper:
            text = "LSuper";
            break;
        case Keys::RightShift:
            text = "RShift";
            break;
        case Keys::RightControl:
            text = "RCTRL";
            break;
        case Keys::RightAlt:
            text = "RAlt";
            break;
        case Keys::RightSuper:
            text = "RSuper";
            break;
        case Keys::Menu:
            text = "Menu";
            break;
        case Keys::MouseButtonLeft:
            text = "LMB";
            break;
        case Keys::MouseButtonRight:
            text = "RMB";
            break;
        case Keys::MouseButtonMiddle:
            text = "MMB";
            break;
        case Keys::MouseButton4:
            text = "MB4";
            break;
        case Keys::MouseButton5:
            text = "MB5";
            break;
        case Keys::MouseButton6:
            text = "MB6";
            break;
        case Keys::MouseButton7:
            text = "MB7";
            break;
        case Keys::MouseButton8:
            text = "MB8/Last";
            break;
        default:
            text = "Unknown";
            break;
        }
    }
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
