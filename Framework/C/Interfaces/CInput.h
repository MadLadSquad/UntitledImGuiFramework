#pragma once
#include <C/CTypes.h>

#ifdef __cplusplus
extern "C"
{
#endif
    /**
     * @brief A struct to hold the data for an input action
     * @var name - The name ID for the action
     * @var keyCode - The keyCode at which the action gets activated
     * @var keyCodesSize - The size of the key codes array
     * @var state - The current state of the action
     * @note Event Safety - Any time
     */
    struct UImGui_CInputAction_I
    {
        const char* name;

        uint16_t* keyCodes;
        size_t keyCodesSize;

        uint8_t state;
    };

    typedef struct UImGui_CInputAction_I UImGui_CInputAction;

    /**
     * @brief Defines the 3 visibility states of a mouse cursor
     * @enum UIMGUI_CURSOR_VISIBILITY_STATE_NORMAL - Cursor is visible and can leave the window at any point.
     * For normal GUI applications
     * @enum UIMGUI_CURSOR_VISIBILITY_STATE_HIDDEN - Hides the cursor when it's over the window, but allows the user to
     * leave the window area.
     * @enum UIMGUI_CURSOR_VISIBILITY_STATE_DISABLED - Hides the cursor and locks it to the window. This is useful for
     * 3D cameras like in games.
     */                      
    enum UImGui_CursorVisibilityState
    {
        UIMGUI_CURSOR_VISIBILITY_STATE_NORMAL = 0x00034001,
        UIMGUI_CURSOR_VISIBILITY_STATE_HIDDEN = 0x00034002,
        UIMGUI_CURSOR_VISIBILITY_STATE_DISABLED = 0x00034003
    };
    
    // Event Safety - begin, style, post-begin
    UIMGUI_PUBLIC_API void UImGui_Input_setCursorVisibility(UImGui_CursorVisibilityState visibility);
    // Event Safety - begin, style, post-begin
    UIMGUI_PUBLIC_API UImGui_CursorVisibilityState UImGui_Input_getCurrentCursorVisibility();

    // Event Safety - begin, style, post-begin
    UIMGUI_PUBLIC_API void UImGui_Input_setStickyKeys(bool bEnable);
    // Event Safety - begin, style, post-begin
    UIMGUI_PUBLIC_API bool UImGui_Input_getStickyKeys();

    // Event Safety - begin, style, post-begin
    // This may not be set if the system doesn't support raw mouse motion or if the mouse cursor is not in the
    // UIMGUI_CURSOR_VISIBILITY_STATE_DISABLED state
    UIMGUI_PUBLIC_API void UImGui_Input_setRawMouseMotion(bool bEnable);
    // Event Safety - begin, style, post-begin
    UIMGUI_PUBLIC_API bool UImGui_Input_getRawMouseMotion();

    // Event Safety - begin, style, post-begin
    UIMGUI_PUBLIC_API void UImGui_Input_setLockKeyMods(bool bEnable);
    // Event Safety - begin, style, post-begin
    UIMGUI_PUBLIC_API bool UImGui_Input_getLockKeyMods();

    // Event Safety - Any time
    UIMGUI_PUBLIC_API uint8_t UImGui_Input_getKey(uint16_t key);
    // Event Safety - Any time
    UIMGUI_PUBLIC_API UImGui_CInputAction UImGui_Input_getAction(UImGui_String name);

    // Event Safety - Any time
    UIMGUI_PUBLIC_API UImGui_FVector2 UImGui_Input_getMousePositionChange();
    // Event Safety - Any time
    UIMGUI_PUBLIC_API UImGui_FVector2 UImGui_Input_getCurrentMousePosition();
    // Event Safety - Any time
    UIMGUI_PUBLIC_API UImGui_FVector2 UImGui_Input_getLastMousePosition();

    // Event Safety - Any time
    UIMGUI_PUBLIC_API UImGui_FVector2 UImGui_Input_getScroll();
#ifdef __cplusplus
}
#endif