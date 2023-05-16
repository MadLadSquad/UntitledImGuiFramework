#pragma once
#include <Core/Events/Input.hpp>
#include <array>

struct GLFWwindow;
namespace UImGui
{
    struct UIMGUI_PUBLIC_API WindowData
    {
        FString name = "UntitledImGuiFramework Application";
        FString iconLocation = "example-icon.png";
        FString layoutLocation = "DefaultLayout";

        bool fullscreen = false;
        bool bResizeable = true;
        bool bSurfaceTransparent = false;
        bool bHidden = false;
        bool bFocused = true;

        FVector2 aspectRatioSizeLimit = { -1, -1 };
        FVector4 sizeLimits = { -1, -1, -1, -1 };

        bool bDecorated = true;
        bool bMaximised = false;
    };

    class WindowInternal
    {
    public:
        WindowInternal() noexcept;
        WindowInternal(const WindowInternal&) = delete;
        void operator=(WindowInternal const&) = delete;

        [[nodiscard]] GLFWwindow* data() const noexcept;
        bool& resized() noexcept;

        void close() noexcept;
    private:
        friend class Window;
        friend class Input;
        friend class RendererInternal;
        friend class Global;

        void updateKeyState() noexcept;

        FVector2 windowSize = { 800.0f, 600.0f };
        FVector2 windowSizeInScreenCoords;

        std::array<uint16_t, 350> keys{};
        std::vector<InputAction> inputActionList{};

        void saveConfig(bool bSaveKeybindings) noexcept;
        void openConfig();
        void setTitle(String title) noexcept;
        void setIcon(String name) noexcept;
        void setCursorVisibility(bool bVisible) noexcept;

        FVector2 getMousePositionChange() noexcept;
        FVector2 getScroll() noexcept;

        void createWindow() noexcept;
        void destroyWindow() noexcept;

        void configureCallbacks() noexcept;
        static void framebufferSizeCallback(GLFWwindow* window, int width, int height) noexcept;
        static void keyboardInputCallback(GLFWwindow* window, int key, int scanCode, int action, int mods) noexcept;
        static void mouseKeyInputCallback(GLFWwindow* window, int button, int action, int mods) noexcept;
        static void mouseCursorPositionCallback(GLFWwindow* window, double xpos, double ypos) noexcept;
        static void scrollInputCallback(GLFWwindow* window, double xoffset, double yoffset) noexcept;
        static void windowPositionCallback(GLFWwindow* window, int xpos, int ypos) noexcept;

        static void windowSizeCallback(GLFWwindow* window, int width, int height) noexcept;
        static void windowCloseCallback(GLFWwindow* window) noexcept;
        static void windowFocusCallback(GLFWwindow* window, int focused) noexcept;
        static void windowIconifyCallback(GLFWwindow* window, int iconified) noexcept;
        static void windowContentScaleCallback(GLFWwindow* window, float x, float y) noexcept;
        static void windowRefreshCallback(GLFWwindow* window) noexcept;
        static void windowMaximisedCallback(GLFWwindow* window, int maximised) noexcept;

        // As of now, only supported in X11
        // TODO: Port to Win32
        // TODO: Port to Wayland
        void setWindowAlwaysOnTop() noexcept;

        // As of now, only supported in X11
        // TODO: Port to Win32
        // TODO: Port to Wayland
        void setWindowAlwaysBelow() noexcept;

        std::vector<std::function<void(int, int)>> windowResizeCallbackList;
        std::vector<std::function<void(int, int)>> windowResizeInScreenCoordCallbackList;
        std::vector<std::function<void(void)>> windowCloseCallbackList;
        std::vector<std::function<void(bool)>> windowFocusCallbackList;
        std::vector<std::function<void(bool)>> windowIconifiedCallbackList;
        std::vector<std::function<void(FVector2)>> windowPositionChangeCallbackList;
        std::vector<std::function<void(FVector2)>> windowContentScaleChangeCallbackList;
        std::vector<std::function<void(void)>> windowRefreshCallbackList;
        std::vector<std::function<void(bool)>> windowMaximisedCallbackList;

        GLFWwindow* windowMain = nullptr;
        WindowData windowData;

        bool bFirstMove = true;
        bool bResized = false;

        FVector2 mousePos = { 0.0f, 0.0f };
        FVector2 mouseLastPos = { 0.0f, 0.0f };
        FVector2 mouseOffset = { 0.0f, 0.0f };

        FVector2 scroll;

        FVector2 windowLastPos = { 0.0f, 0.0f };
        FVector2 windowCurrentPos = { 0.0f, 0.0f };
    };
}
