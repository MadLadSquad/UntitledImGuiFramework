#pragma once
#include <Core/Defines.hpp>
#include <Core/Types.hpp>

namespace UImGui
{

    /**
     * @brief A struct to hold the data for an input action
     * @var name - The name ID for the action
     * @var keyCode - The keyCode at which the action gets activated
     * @var state - The current state of the action
     * @note Event Safety - Any time
     */
    struct UIMGUI_PUBLIC_API InputAction
    {
        InputAction() = default;

        bool operator==(const uint8_t& st) const noexcept;
        bool operator!=(const uint8_t& st) const noexcept;

        // The ID for the action
        FString name{};
        uint16_t keyCode{};

        // Set by the input system, do not set this manually
        uint8_t state{};
    };

    /**
     * @brief Implements a public interface to the Input system
     * @implements getKey - Given a keycode, returns the state of the key
     * @implements getAction - Given the name of an action, returns the action
     * @implements getActions - Returns the list of actions
     * @implements getMousePositionChange, getCurrentMousePosition, getLastMousePosition, getScroll
     * @note Event Safety - Any time
     */
    class UIMGUI_PUBLIC_API Input
    {
    public:
        Input() = delete;
        Input(const Input&) = delete;
        void operator=(Input const&) = delete;

        // Event Safety - Any time
        static uint8_t getKey(uint16_t key) noexcept;
        // Event Safety - Any time
        static const InputAction& getAction(const UImGui::FString& name) noexcept;

        // Event Safety - Any time
        static std::vector<InputAction>& getActions() noexcept;

        // Event Safety - Any time
        static FVector2 getMousePositionChange() noexcept;
        // Event Safety - Any time
        static FVector2 getCurrentMousePosition() noexcept;
        // Event Safety - Any time
        static FVector2 getLastMousePosition() noexcept;

        // Event Safety - Any time
        static FVector2 getScroll() noexcept;
    };
}