#pragma once
#include <Core/Defines.hpp>
#include <Core/Types.hpp>
#include "Utils/Window.hpp"


namespace UImGui
{
    class UIMGUI_PUBLIC_API Window
    {
    public:
        Window() = delete;
        Window(const Window&) = delete;
        void operator=(Window const&) = delete;

        static void setTitle(String name) noexcept;
        static void setCursorVisibility(bool bVisible) noexcept;

        static float aspectRatio() noexcept;

        static FVector2 getCurrentWindowPosition() noexcept;
        static FVector2 getLastWindowPosition() noexcept;
        static FVector2 getWindowPositionChange() noexcept;

        static FVector2& windowSize() noexcept;
        static bool& fullscreen() noexcept;

        static FString& name() noexcept;
        static FString& iconLocation() noexcept;

        static void saveSettings(bool bSaveKeybinds) noexcept;

        static void close() noexcept;
    };
}