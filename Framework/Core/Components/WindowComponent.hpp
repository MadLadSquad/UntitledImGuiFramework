#pragma once
#include <Defines.hpp>

namespace UImGui
{
    class UIMGUI_PUBLIC_API WindowComponent
    {
    public:
        WindowComponent() = default;
        virtual void begin() = 0;
        virtual void tick(float deltaTime) = 0;
        virtual void end() = 0;

        void beginAutohandle() noexcept;
        void tickAutohandle(float deltaTime) noexcept;
        void endAutohandle() noexcept;

        virtual ~WindowComponent() = default;
    private:

    };
}