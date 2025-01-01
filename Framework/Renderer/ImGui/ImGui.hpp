#pragma once
#include <GenericRenderer/GenericRenderer.hpp>

struct ImVec4;
struct GLFWwindow;

namespace UImGui
{
    class Window;
    class GUIRenderer
    {
    public:
        GUIRenderer() = default;

        static void init(GenericInternalRenderer* renderer) noexcept;
        static void beginUI(float deltaTime, GenericInternalRenderer* renderer) noexcept;
        static void beginFrame() noexcept;
        static void shutdown(GenericInternalRenderer* renderer) noexcept;
    };
}