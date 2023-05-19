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
        std::vector<uint16_t> keyCodes;

        // Set by the input system, do not set this manually
        uint8_t state{};
    };

    /**
     * @brief Defines the 3 visibility states of a mouse cursor
     * @enum UIMGUI_CURSOR_VISIBILITY_STATE_NORMAL - Cursor is visible and can leave the window at any point.
     * For normal GUI applications
     * @enum UIMGUI_CURSOR_VISIBILITY_STATE_HIDDEN - Hides the cursor when it's over the window, but allows the user to
     * leave the window area.
     * @enum UIMGUI_CURSOR_VISIBILITY_STATE_DISABLED - Hides the cursor and locks it to the window. This is useful for
     * 3D cameras like in games.
     */
    enum CursorVisibilityState
    {
        UIMGUI_CURSOR_VISIBILITY_STATE_NORMAL = 0x00034001,
        UIMGUI_CURSOR_VISIBILITY_STATE_HIDDEN = 0x00034002,
        UIMGUI_CURSOR_VISIBILITY_STATE_DISABLED = 0x00034003
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

        // Event Safety - begin, style, post-begin
        static void setCursorVisibility(CursorVisibilityState visibility) noexcept;
        // Event Safety - begin, style, post-begin
        static CursorVisibilityState getCurrentCursorVisibility() noexcept;

        // Event Safety - begin, style, post-begin
        static void setStickyKeys(bool bEnable) noexcept;
        // Event Safety - begin, style, post-begin
        static bool getStickyKeys() noexcept;

        // Event Safety - begin, style, post-begin
        // This may not be set if the system doesn't support raw mouse motion or if the mouse cursor is not in the
        // UIMGUI_CURSOR_VISIBILITY_STATE_DISABLED state
        static void setRawMouseMotion(bool bEnable) noexcept;
        // Event Safety - begin, style, post-begin
        static bool getRawMouseMotion() noexcept;

        // Event Safety - begin, style, post-begin
        static void setLockKeyMods(bool bEnable) noexcept;
        // Event Safety - begin, style, post-begin
        static bool getLockKeyMods() noexcept;

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