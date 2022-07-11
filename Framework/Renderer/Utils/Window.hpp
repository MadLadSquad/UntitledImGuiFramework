#pragma once
#include <Core/Events/Input.hpp>
#include <array>

class GLFWwindow;
namespace UImGui
{
    struct UIMGUI_PUBLIC_API WindowData
    {
        FString name = "UntitledImGuiFramework Application";
        FString iconLocation = "example-icon.png";
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
    private:
        friend class Window;
        friend class Input;
        friend class RendererInternal;

        FVector2 windowSize = { 800.0f, 600.0f };
        std::array<uint16_t, 350> keys{};
        std::vector<InputAction> inputActionList{};

        void saveConfig(bool bSaveKeybindings) noexcept;
        void openConfig();
        void setTitle(String title) noexcept;
        void setCursorVisibility(bool bVisible) noexcept;
        [[nodiscard]] FVector2 getLastMousePosition() const noexcept;
        [[nodiscard]] FVector2 getCurrentMousePosition() const noexcept;
        FVector2 getMousePositionChange() noexcept;
        FVector2 getScroll() noexcept;
        const std::array<uint16_t, 350>& getKeys() noexcept;
        std::vector<InputAction>& getActions() noexcept;


        void createWindow() noexcept;
        void destroyWindow() noexcept;

        void configureCallbacks() noexcept;
        static void framebufferSizeCallback(GLFWwindow* window, int width, int height) noexcept;
        static void keyboardInputCallback(GLFWwindow* window, int key, int scanCode, int action, int mods) noexcept;
        static void mouseKeyInputCallback(GLFWwindow* window, int button, int action, int mods) noexcept;
        static void mouseCursorPositionCallback(GLFWwindow* window, double xpos, double ypos) noexcept;
        static void scrollInputCallback(GLFWwindow* window, double xoffset, double yoffset) noexcept;

        [[nodiscard]] float getXMousePositionChange() noexcept;
        [[nodiscard]] float getYMousePositionChange() noexcept;

        GLFWwindow* windowMain = nullptr;
        //InternalRendererComponents* renderer = nullptr;
        WindowData windowData;

        bool bFirstMove = true;
        bool bResized = false;

        float posX = 0;
        float posY = 0;
        float lastPosX = 0;
        float lastPosY = 0;
        float offsetX = 0;
        float offsetY = 0;
        FVector2 scroll;
    };
}