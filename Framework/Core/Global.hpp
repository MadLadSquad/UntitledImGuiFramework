#pragma once
//#include <Components/Instance.hpp>
#include <Renderer/Utils/Window.hpp>
#include "Modules/Manager/ModulesManager.hpp"

namespace UImGui
{
    class RendererInternal;
    class Instance;
    class UIMGUI_PUBLIC_API Global
    {
    public:
        Global() noexcept;
        ~Global() noexcept;

        void init() noexcept;

        Instance* instance = nullptr;
        RendererInternal* renderer = nullptr;
    private:
        friend class Window;
        friend class Renderer;
        friend class Modules;

        WindowInternal window{};
        ModulesManager modulesManagerr{};
    };

    inline Global internalGlobal;
}