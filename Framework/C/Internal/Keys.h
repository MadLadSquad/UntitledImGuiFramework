#pragma once
#ifdef __cplusplus
extern "C"
{
#endif
    typedef enum [[maybe_unused]] CKeys
    {
        Keys_UnknownKey = 349,
        Keys_Space = 32,
        Keys_Apostrophe = 39,
        Keys_Comma = 44,
        Keys_Minus = 45,
        Keys_Period = 46,
        Keys_Slash = 47,
        Keys_Zero = 48,
        Keys_One = 49,
        Keys_Two = 50,
        Keys_Three= 51,
        Keys_Four = 52,
        Keys_Five = 53,
        Keys_Six = 54,
        Keys_Seven = 55,
        Keys_Eight = 56,
        Keys_Nine = 57,
        Keys_Semicolon = 59,
        Keys_Equal = 61,
        Keys_A = 65,
        Keys_B = 66,
        Keys_C = 67,
        Keys_D = 68,
        Keys_E = 69,
        Keys_F = 70,
        Keys_G = 71,
        Keys_H = 72,
        Keys_I = 73,
        Keys_J = 74,
        Keys_K = 75,
        Keys_L = 76,
        Keys_M = 77,
        Keys_N = 78,
        Keys_O = 79,
        Keys_P = 80,
        Keys_Q = 81,
        Keys_R = 82,
        Keys_S = 83,
        Keys_T = 84,
        Keys_U = 85,
        Keys_V = 86,
        Keys_W = 87,
        Keys_X = 88,
        Keys_Y = 89,
        Keys_Z = 90,
        Keys_LeftBracket = 91,
        Keys_Backslash = 92,
        Keys_RightBracket = 93,
        Keys_GraveAccent = 96,
        Keys_WorldOne = 161,
        Keys_WorldTwo = 162,
        Keys_Escape = 256,
        Keys_Enter = 257,
        Keys_Tab = 258,
        Keys_Backspace = 259,
        Keys_Insert = 260,
        Keys_Delete = 261,
        Keys_RightArrow = 262,
        Keys_LeftArrow = 263,
        Keys_DownArrow = 264,
        Keys_UpArrow = 265,
        Keys_PageUp = 266,
        Keys_PageDown = 267,
        Keys_Home = 268,
        Keys_End = 269,
        Keys_CapsLock = 280,
        Keys_ScrollLock = 281,
        Keys_NumLock = 282,
        Keys_PrintScreen = 283,
        Keys_Pause = 284,
        Keys_F1 = 290,
        Keys_F2 = 291,
        Keys_F3 = 292,
        Keys_F4 = 293,
        Keys_F5 = 294,
        Keys_F6 = 295,
        Keys_F7 = 296,
        Keys_F8 = 297,
        Keys_F9 = 298,
        Keys_F10 = 299,
        Keys_F11 = 300,
        Keys_F12 = 301,
        Keys_F13 = 302,
        Keys_F14 = 303,
        Keys_F15 = 304,
        Keys_F16 = 305,
        Keys_F17 = 306,
        Keys_F18 = 307,
        Keys_F19 = 308,
        Keys_F20 = 309,
        Keys_F21 = 310,
        Keys_F22 = 311,
        Keys_F23 = 312,
        Keys_F24 = 313,
        Keys_F25 = 314,
        Keys_NumPadZero = 320,
        Keys_NumPadOne = 321,
        Keys_NumPadTwo = 322,
        Keys_NumPadThree = 323,
        Keys_NumPadFour = 324,
        Keys_NumPadFive = 325,
        Keys_NumPadSix = 326,
        Keys_NumPadSeven = 327,
        Keys_NumPadEight = 328,
        Keys_NumPadNine = 329,
        Keys_NumPadDecimal = 330,
        Keys_NumPadDivide = 331,
        Keys_NumPadMultiply = 332,
        Keys_NumPadSubtract = 333,
        Keys_NumPadAdd = 334,
        Keys_NumPadEnter = 335,
        Keys_NumPadEqual = 336,
        Keys_LeftShift = 340,
        Keys_LeftControl = 341,
        Keys_LeftAlt = 342,
        Keys_LeftSuper = 343,
        Keys_RightShift = 344,
        Keys_RightControl = 345,
        Keys_RightAlt = 346,
        Keys_RightSuper = 347,
        Keys_Menu = 348,
        Keys_MouseButton1 = 0,
        Keys_MouseButton2 = 1,
        Keys_MouseButton3 = 2,
        Keys_MouseButton4 = 3,
        Keys_MouseButton5 = 4,
        Keys_MouseButton6 = 5,
        Keys_MouseButton7 = 6,
        Keys_MouseButton8 = 7,
        Keys_MouseButtonLast = 7,
        Keys_MouseButtonLeft = 0,
        Keys_MouseButtonRight = 1,
        Keys_MouseButtonMiddle = 2,
        Keys_ScrollUp = 8,
        Keys_ScrollDown = 9,
        Keys_ScrollRight = 10,
        Keys_ScrollLeft = 11,
        Keys_None = 12,
        Keys_KeyReleased = 0,
        Keys_KeyPressed = 1,
        Keys_KeyRepeat = 2,
    } CKeys;
#ifdef __cplusplus
}
#endif