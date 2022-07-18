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

        template<typename T>
        static WindowComponent* make() noexcept
        {
            T* n = new T();
            return n;
        }

        void beginAutohandle() noexcept;
        void tickAutohandle(float deltaTime) noexcept;
        void endAutohandle() noexcept;

        ComponentState state = UIMGUI_COMPONENT_STATE_RUNNING;

        virtual ~WindowComponent() = default;
    private:

    };
}