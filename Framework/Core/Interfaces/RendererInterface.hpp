#pragma once
#include <Core/Defines.hpp>
#include <Core/Types.hpp>
#include "Renderer.hpp"

namespace UImGui
{
    class RendererData;

    class UIMGUI_PUBLIC_API Renderer
    {
    public:
        static RendererData& data() noexcept;
        static void saveSettings() noexcept;
    private:
        friend class RendererInternal;

        static RendererInternal& get() noexcept;
    };
}