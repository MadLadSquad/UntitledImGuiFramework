#pragma once
#include <GenericRenderer/GenericRenderer.hpp>

struct ImVec4;
struct GLFWwindow;

namespace UImGui
{
    class Window;
    class UIMGUI_PUBLIC_API GUIRenderer
    {
    public:
        GUIRenderer() = default;

    private:
        friend class RendererUtils;
        friend class RendererInternal;

        static void init(GenericRenderer* renderer) noexcept;
        static void beginUI(float deltaTime, GenericRenderer* renderer) noexcept;
        static void beginFrame() noexcept;
        static void shutdown(GenericRenderer* renderer) noexcept;
    };
}