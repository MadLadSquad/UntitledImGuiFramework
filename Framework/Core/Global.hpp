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
        friend class Instance;
        friend class Input;
        friend class GUIRenderer;
        friend class Window;
        friend class Renderer;
        friend class RendererInternal;
        friend class Locale;
        friend class StateTracker;
        friend class Modules;
        friend class ModulesManager;

        WindowInternal window{};
        ModulesManager modulesManager{};
    };

    inline Global internalGlobal;
}