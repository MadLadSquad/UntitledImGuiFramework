#pragma once
#include <Renderer/Window/Window.hpp>
#include "Modules/Manager/ModulesManager.hpp"
#include "CDeallocation.hpp"
#include <Interfaces/PluginInterface.hpp>
#ifdef _WIN32
    #include <windows.h>
#endif

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

        static Global& get(Global* parent = nullptr) noexcept;

        Instance* instance = nullptr;
        RendererInternal* renderer = nullptr;

        CDeallocationStruct deallocationStruct;
    private:
        friend class Window;
        friend class Renderer;
        friend class Modules;
        friend class ModulesManager;
        friend class RendererInternal;
        friend class Plugins;

        WindowInternal window{};
        ModulesManager modulesManagerr{};
        Plugins plugins{};

        static Global* getWithCreate() noexcept;
    };
}
