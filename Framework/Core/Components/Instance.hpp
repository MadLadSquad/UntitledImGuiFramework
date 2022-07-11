#pragma once
#include <Defines.hpp>
#include <vector>
#include <Components/InlineComponent.hpp>
#include <Components/TitlebarComponent.hpp>
#include <Components/WindowComponent.hpp>
#include <imgui.h>
#include <imgui_internal.h>

namespace UImGui
{
    struct UIMGUI_PUBLIC_API InitInfo
    {
        std::vector<InlineComponent*> inlineComponents;
        std::vector<TitlebarComponent*> titlebarComponents;
        std::vector<WindowComponent*> windowComponents;
    };

    class UIMGUI_PUBLIC_API Instance
    {
    public:
        Instance() noexcept;
        virtual void begin() = 0;
        virtual void tick(float deltaTime) = 0;
        virtual void end() = 0;
        virtual ~Instance() noexcept;

        virtual void onEventConfigureStyle(ImGuiStyle& style, ImGuiIO& io) = 0;

        InitInfo initInfo;

        void beginAutohandle() noexcept;
        void tickAutohandle(float deltaTime) noexcept;
        void endAutohandle() noexcept;
    private:

    };
}