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

        static void init(const FString& ini, GenericInternalRenderer* renderer) noexcept;
        static void beginUI(float deltaTime, GenericInternalRenderer* renderer);
        static void beginFrame();
        static void shutdown(const FString& ini, GenericInternalRenderer* renderer) noexcept;
    };
}