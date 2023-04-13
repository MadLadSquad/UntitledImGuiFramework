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
        std::array<uint16_t, 350> keys{};
        std::vector<InputAction> inputActionList{};

        void saveConfig(bool bSaveKeybindings) noexcept;
        void openConfig();
        void setTitle(String title) noexcept;
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
