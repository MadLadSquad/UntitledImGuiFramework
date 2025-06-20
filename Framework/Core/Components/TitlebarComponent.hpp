#pragma once
#include <Defines.hpp>
#include <Types.hpp>
#include <C/Components/CTitlebarComponent.h>

namespace UImGui
{
    typedef UImGui_TitlebarMenuItemType TitlebarMenuItemType;

    struct UIMGUI_PUBLIC_API TitlebarMenuItem
    {
        FString label;
        FString hint;
        TFunction<void(void*)> f;

        TitlebarMenuItemType type;
        size_t membersLen;

        bool* bEnabled = nullptr;
        bool* bSelected = nullptr;
    };

    class UIMGUI_PUBLIC_API TitlebarBuilder
    {
    public:
        TitlebarBuilder() noexcept = default;

        /**
         * @brief Enables/disables integrating with the global menu on macOS instead of drawing the menu ourselves using dear imgui
         * @param bBuildNativeOnMacOS - Whether to build a native menu on macOS. Doesn't have to be set when not on macOS.
         * Setting this value on macOS changes the behaviour of the finish and render methods.
         * @note Event safety - Any time
         */
        TitlebarBuilder& setBuildNativeOnMacOS(bool bBuildNativeOnMacOS) noexcept;

        /**
         * @brief Sets the user-defined context variable for the menu that can be consumed by callbacks
         * @param data - A void* to your data context for use in menu callback functions
         * @note Event safety - Any time
         */
        TitlebarBuilder& setContext(void* data) noexcept;

        /**
         * @brief Adds a menu item aka a button to the menu
         * @param label - The text label of the menu item
         * @param hint - Hint text, if it's a key binding from the Input interface try converting it to macOS format on macOS
         * @param f - A callback function that is called when pressed. Gets the user-defined void* context pointer
         * @param bEnabled - Whether the menu item is enabled. A nullptr is interpreted as true. On false values the button is greyed out and cannot be clicked
         * @note Event safety - Begin, Post-begin
         */
        TitlebarBuilder& addMenuItem(const FString& label, const FString& hint = "", const TFunction<void(void*)>& f = [](void*) -> void {}, bool* bEnabled = nullptr) noexcept;

        /**
         * @brief Adds a separator to the menu
         * @note Event safety - Begin, Post-begin
         */
        TitlebarBuilder& addSeparator() noexcept;

        /**
         * @brief Adds a submenu to the menu
         * @param label - The text label of the menu item
         * @param submenu - A pointer to another menu builder instance that will be added as a submenu
         * @param bEnabled - Whether the menu item is enabled. NULL is interpreted as true. On false values the button is greyed out and cannot be clicked
         * @note Event safety - Begin, Post-begin
         */
        TitlebarBuilder& addSubmenu(const FString& label, const TitlebarBuilder& submenu, bool* bEnabled = nullptr) noexcept;

        /**
         * @brief Adds a checkbox element to the menu
         * @param label - The text label of the menu item
         * @param bSelected - A pointer to a boolean. The pointer will be mutated by us when the checkbox is pressed
         * @param bEnabled - Whether the menu item is enabled. NULL is interpreted as true. On false values the button is greyed out and cannot be clicked
         * @note Event safety - Begin, Post-begin
         */
        TitlebarBuilder& addCheckbox(const FString& label, bool& bSelected, bool* bEnabled = nullptr) noexcept;

        /**
         * Finishes building the menu. When drawing a macOS menu this function submits it to the OS for rendering. When
         * drawing an imgui-native menu it does nothing.
         * @note Event safety - Begin, Post-begin
         */
        void finish() noexcept;

        /**
         * Renders the menu. Should be called every frame. When drawing a macOS menu it does nothing. When drawing an
         * imgui-native menu it renders the UI for the menu. Should only be called in Titlebar components
         * @note Event safety - Tick
         */
        void render() noexcept;
    private:
        bool bPreferNative = true;
        void* data = nullptr;
#ifdef __APPLE__
        void macOSFinish() noexcept;
#endif

        TVector<TitlebarMenuItem> events{};
    };

    /**
     * @brief A UI component that implements the standard top title bar
     * @implements TitlebarComponent - The constructor for the component
     * @implements begin - The default begin event as detailed in the docs
     * @implements tick - The default tick event as detailed in the docs
     * @implements end - The default end event as detailed in the docs
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
        // Event Safety - All ready
        virtual void begin() = 0;
        // Event Safety - All ready
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
         * @brief The name ID of the component as to provide a human-readable way to differentiate between components,
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