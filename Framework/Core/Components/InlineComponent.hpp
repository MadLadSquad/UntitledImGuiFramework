#pragma once
#include <Defines.hpp>
#include <Types.hpp>

namespace UImGui
{
    /**
     * @brief A component that directly draws to the window's framebuffer(the opposite of the WindowComponent)
     */
    class UIMGUI_PUBLIC_API InlineComponent
    {
    public:
        InlineComponent() = default;
        virtual void begin() = 0;
        virtual void tick(float deltaTime) = 0;
        virtual void end() = 0;

        /**
         * @brief Instantiates the component of type T and using polymorphism converts it to the base class of InlineComponent
         * @tparam T The type of the InlineComponent subclass
         * @return The new instance pointer
         */
        template<typename T>
        static InlineComponent* make() noexcept
        {
            T* n = new T();
            return n;
        }

        void beginAutohandle() noexcept;
        void tickAutohandle(float deltaTime) noexcept;
        void endAutohandle() noexcept;

        ComponentState state = UIMGUI_COMPONENT_STATE_RUNNING;
        FString name{};
        uint64_t id{};

        virtual ~InlineComponent() = default;
    private:

    };
}