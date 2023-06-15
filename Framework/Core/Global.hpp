#pragma once
//#include <Components/Instance.hpp>
#include <Renderer/Utils/Window.hpp>
#include "Modules/Manager/ModulesManager.hpp"
#include "Threads/LogicThreads.hpp"
#include "CDeallocation.hpp"

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

        CDeallocationStruct deallocationStruct;
    private:
        friend class Window;
        friend class Renderer;
        friend class Modules;
        friend class RendererInternal;

        WindowInternal window{};
        ModulesManager modulesManagerr{};
        LogicThreadsManager threadsManager{};
    };

    inline Global internalGlobal;
}