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

        // Event Safety - begin, style, post-begin
        static void setTitle(String name) noexcept;
        // Event Safety - begin, style, post-begin
        static void setCursorVisibility(bool bVisible) noexcept;

        // Event Safety - begin, style, post-begin
        static void setIcon(String name) noexcept;

        // Event Safety - begin, style, post-begin
        static float aspectRatio() noexcept;

        // Event Safety - begin, style, post-begin
        static FVector2 getCurrentWindowPosition() noexcept;
        // Event Safety - begin, style, post-begin
        static FVector2 getLastWindowPosition() noexcept;
        // Event Safety - begin, style, post-begin
        static FVector2 getWindowPositionChange() noexcept;

        // Event Safety - begin, style, post-begin
        static FVector2& windowSize() noexcept;
        // Event Safety - begin, style, post-begin
        static bool& fullscreen() noexcept;

        // Event Safety - begin, style, post-begin
        static FString& name() noexcept;
        // Event Safety - begin, style, post-begin
        static FString& iconLocation() noexcept;
        // Event Safety - begin, style, post-begin
        static FString& layoutLocation() noexcept;

        // Event Safety - begin, style, post-begin
        static void saveSettings(bool bSaveKeybinds) noexcept;

        // Event Safety - begin, style, post-begin
        static void refreshSettings() noexcept;

        // Event Safety - begin, style, post-begin
        static void close() noexcept;
    private:
        friend class Input;
        friend class Instance;
        friend class RendererInternal;

        static WindowInternal& get() noexcept;
    };
}