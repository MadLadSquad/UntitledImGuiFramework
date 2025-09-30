#pragma once
#include <C/Interfaces/CWindowInterface.h>
#include "GLFW/WindowGLFW.hpp"

namespace UImGui
{
    class UIMGUI_PUBLIC_API WindowInternal
    {
    public:
        WindowInternal() noexcept = default;
    private:
        friend class Window;
        friend class Global;
        friend class RendererInternal;

        WindowGLFW glfw{};
        GenericWindow* window = &glfw;
    };
}
