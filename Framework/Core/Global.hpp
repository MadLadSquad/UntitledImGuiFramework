#pragma once
#include <Components/Instance.hpp>
#include <Renderer/Utils/Window.hpp>

namespace UImGui
{
    class RendererInternal;
    class Global
    {
    public:
        Global() noexcept;
        ~Global() noexcept;
        Instance* instance = nullptr;
        RendererInternal* renderer = nullptr;
    private:
        friend class Instance;
        friend class Input;
        friend class GUIRenderer;
        friend class Window;
        friend class Renderer;
        friend class RendererInternal;

        WindowInternal window{};
    };

    inline Global internalGlobal;
}