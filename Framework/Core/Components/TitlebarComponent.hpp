#pragma once
#include <Defines.hpp>
#include <Types.hpp>

namespace UImGui
{
    /**
     * @brief A UI component that implements the standard top title bar
     * @implements TitlebarComponent - The constructor for the component
     * @implements begin - The default begin event as detailed in the docs
     * @implements tick - The default tick event as detailed in the docs
     * @implements end - The default end event as detailed in the docs
     * @implements ~TitlebarComponent - The destructor for the component
     * @static make - Creates a titlebar component of a given subclass type
     * @var componentType - The type of the component as a constexpr
     * @var state - The default initial state of the component
     * @var name - The name identifier of the component
     * @var id  - The numeric identifier of the component
     * @implements beginAutohandle - Used to automatically handle downstream begin events
     * @implements tickAutohandle - Used to automatically handle downstream tick events
     * @implements endAutohandle - Used to automatically handle downstream end events
     */
    class UIMGUI_PUBLIC_API TitlebarComponent
    {
    public:
        TitlebarComponent() = default;
        // Event Safety - All instantiated
        virtual void begin() = 0;
        // Event Safety - All instantiated
        virtual void tick(float deltaTime) = 0;
        // Event Safety - Pre-destruct
        virtual void end() = 0;

        /**
         * @brief Easily initializes a component of a certain subclass provided as a template argument
         * @tparam T - The subclass type
         * @return A pointer to the newly created component
         * @note Event Safety - Any time
         */
        template<typename T>
        static TitlebarComponent* make() noexcept
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
        static constexpr ComponentType componentType = UIMGUI_COMPONENT_TYPE_TITLEBAR;
        /**
         * @brief The name ID of the component as to provide a human readable way to differentiate between components,
         * not guaranteed to be unique
         */
        FString name{};
        /**
         * @brief The numeric ID of the component, it's not a UUID and is provided by the user!
         */
        uint64_t id{};

        virtual ~TitlebarComponent() = default;
    private:
    };
}