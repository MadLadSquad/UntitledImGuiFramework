#pragma once
//#include <Components/Instance.hpp>
#include <Renderer/Utils/Window.hpp>
#ifdef UIMGUI_LOCALE_MODULE_ENABLED
#include "Modules/Locale/src/localemod.hpp"
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

        WindowInternal window{};
#ifdef UIMGUI_LOCALE_MODULE_ENABLED
        LocaleManager localeManager{};
#endif
    };

    inline Global internalGlobal;
}