#pragma once
#include <Core/Types.hpp>
#include <C/Window/Keys.h>

// Imports the C API, contains definitions of the C InputAction struct and other uniform API structs and enum
#include <C/Interfaces/CInput.h>

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

        bool operator==(const CKeyState& st) const noexcept;
        bool operator!=(const CKeyState& st) const noexcept;

        // The ID for the action
        FString name{};
        TVector<uint64_t> keyCodes;

        // Set by the input system, do not set this manually
        CKeyState state{};
    };

    typedef UImGui_CursorVisibilityState CursorVisibilityState;

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

        // Event Safety - begin, style, post-begin
        static void setCursorVisibility(CursorVisibilityState visibility) noexcept;

        // Event Safety - begin, style, post-begin
        // This may not be set if the system doesn't support raw mouse motion or if the mouse cursor is not in the
        // UIMGUI_CURSOR_VISIBILITY_STATE_DISABLED state
        static void setRawMouseMotion(bool bEnable) noexcept;
        // Event Safety - begin, style, post-begin
        static bool getRawMouseMotion() noexcept;

        // Event Safety - Any time
        static CKeyState getKey(CKeys key) noexcept;
        // Event Safety - Any time
        static const InputAction& getAction(const UImGui::FString& name) noexcept;

        // Event Safety - Any time
        static TVector<InputAction>& getActions() noexcept;

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