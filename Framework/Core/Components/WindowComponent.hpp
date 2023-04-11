#pragma once
#include <Defines.hpp>
#include <Types.hpp>

namespace UImGui
{
    /**
     * @brief A component that draws to a movable and dockable window
     * @implements WindowComponent - The constructor for the component
     * @implements begin - The default begin event as detailed in the docs
     * @implements tick - The default tick event as detailed in the docs
     * @implements end - The default end event as detailed in the docs
     * @static make - Creates a WindowComponent of a given subclass type
     * @implements beginAutohandle - Used to automatically handle downstream begin events
     * @implements tickAutohandle - Used to automatically handle downstream tick events
     * @implements endAutohandle - Used to automatically handle downstream end events
     * @var state - The default initial state of the component
     * @var componentType - The constexpr type of the component
     * @var name - The name identifier of the component
     * @var id - The numeric identifier of the component
     */
    class UIMGUI_PUBLIC_API WindowComponent
    {
    public:
        WindowComponent() = default;
        // Event Safety - All instantiated
        virtual void begin() = 0;
        // Event Safety - All instantiated
        virtual void tick(float deltaTime) = 0;
        // Event Safety - Pre-destruct
        virtual void end() = 0;

        /**
         * @brief Instantiates the component of type T and using polymorphism converts it to the base class of WindowComponent
         * @tparam T The type of the WindowComponent subclass
         * @return The new instance pointer
         * @note Event Safety - Any time
         */
        template<typename T>
        static WindowComponent* make() noexcept
        {
            T* n = new T();
            return n;
        }

        /**
         * @brief Used to automatically handle downstream begin events
         * @note Event Safety - Any time
         */
        void beginAutohandle() noexcept;
        /**
         * @brief Used to automatically handle downstream tick events
         * @param deltaTime - the delta time calculated in the application's render loop
         * @note Event Safety - Any time
         */
        void tickAutohandle(float deltaTime) noexcept;
        /**
         * @brief Used to automatically handle downstream end events
         * @note Event Safety - Any time
         */
        void endAutohandle() noexcept;

        /**
         * @brief The current state of the component
         */
        ComponentState state = UIMGUI_COMPONENT_STATE_RUNNING;
        /**
         * @brief The type of the component represented by a ComponentType constexpr static variable
         */
        static constexpr ComponentType componentType = UIMGUI_COMPONENT_TYPE_WINDOW;
        /**
         * @brief The name ID of the component as to provide a human readable way to differentiate between components,
         * not guaranteed to be unique
         */
        FString name{};
        /**
         * @brief The numeric ID of the component, it's not a UUID and is provided by the user!
         */
        uint64_t id{};

        virtual ~WindowComponent() = default;
    private:

    };
}