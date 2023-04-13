#pragma once
#include <functional>
#include <iostream>

struct ImVec4;
struct GLFWwindow;

namespace UImGui
{
    class Window;
    class GUIRenderer
    {
    public:
        GUIRenderer() = default;

        static void init(GLFWwindow* glfwwindow, const FString& ini);
        static void beginUI(float deltaTime);
        static void beginFrame();
        static void shutdown(const FString& ini);
    private:
    };
}