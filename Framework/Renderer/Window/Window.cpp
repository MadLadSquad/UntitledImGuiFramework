#define STB_IMAGE_IMPLEMENTATION
#include "Window.hpp"
#ifdef __APPLE__
    #include <OpenGL/GL.h>
#else
    #include <glad/include/glad/gl.h>
#endif
#include <Global.hpp>
#include <GLFW/glfw3.h>

#include <ThirdParty/source-libraries/stb_image.h>
#include <yaml-cpp/yaml.h>
#include <Interfaces/RendererInterface.hpp>
#include <Interfaces/WindowInterface.hpp>

#include <Components/Instance.hpp>

UImGui::WindowInternal::WindowInternal() noexcept
{
    keys.fill(0);
}

GLFWwindow* UImGui::WindowInternal::data() const noexcept
{
    return windowMain;
}

bool& UImGui::WindowInternal::resized() noexcept
{
    return bResized;
}

void UImGui::WindowInternal::setTitle(const String title) noexcept
{
    glfwSetWindowTitle(windowMain, title);
    windowData.name = title;
}

UImGui::FVector2 UImGui::WindowInternal::getMousePositionChange() noexcept
{
    const FVector2 ret = mouseOffset;
    mouseOffset = { 0.0f, 0.0f };
    return ret;
}

UImGui::FVector2 UImGui::WindowInternal::getScroll() noexcept
{
    const FVector2 ret = scroll;
    scroll = { 0.0f, 0.0f };
    return ret;
}

void UImGui::WindowInternal::createWindow() noexcept
{
    // Load all config we need
    openConfig();

    // Init GLFW
    if (!glfwInit())
    {
        Logger::log("GLFW initialisation failed!", ULOG_LOG_TYPE_ERROR);
        glfwTerminate();
        return;
    }
    Logger::log("Setting up the window", ULOG_LOG_TYPE_NOTE);

    // This is used to set up window hints for the renderer. Read up on creating custom renderers.
    RendererUtils::getRenderer()->setupWindowIntegration();
    configureDefaultHints();

    GLFWmonitor* monitor = nullptr;
#ifndef __EMSCRIPTEN__
    if (windowData.fullscreen)
        monitor = glfwGetPrimaryMonitor();
#endif

    windowMain = glfwCreateWindow(static_cast<int>(windowSize.x), static_cast<int>(windowSize.y), windowData.name.c_str(), monitor, nullptr);
    if (!windowMain)
    {
        Logger::log("GLFW window creation failed!", ULOG_LOG_TYPE_ERROR);
        glfwTerminate();
        return;
    }
    Logger::log("Created window", ULOG_LOG_TYPE_NOTE);

    // Load window icon
    setIcon(windowData.iconLocation.c_str());

    Window::setSizeLimits({ windowData.sizeLimits.x, windowData.sizeLimits.y }, { windowData.sizeLimits.z, windowData.sizeLimits.w });
    Window::setSizeLimitByAspectRatio(windowData.aspectRatioSizeLimit);

    Logger::log("Window was created successfully", ULOG_LOG_TYPE_SUCCESS);

    // Set framebuffer size
    int tempx = CAST(int, windowSize.x);
    int tempy = CAST(int, windowSize.y);

    glfwGetFramebufferSize(windowMain, &tempx, &tempy);

    windowSize.x = CAST(float, tempx);
    windowSize.y = CAST(float, tempy);

    RendererUtils::getRenderer()->setupPostWindowCreation();

    // Set callbacks
    configureCallbacks();
    glfwSetWindowUserPointer(windowMain, this);
}

void UImGui::WindowInternal::destroyWindow() const noexcept
{
    glfwDestroyWindow(windowMain);
    glfwTerminate();
}

void UImGui::WindowInternal::updateKeyState() noexcept
{
    for (auto& a : inputActionList)
    {
        if (!a.keyCodes.empty())
        {
            for (const auto& f : a.keyCodes)
                if (keys[f] != keys[a.keyCodes[0]])
                    goto finish_inner_loop;
            a.state = keys[a.keyCodes[0]];
        }
finish_inner_loop:;
    }
}

void UImGui::WindowInternal::setIcon(const String name) const noexcept
{
#ifndef __EMSCRIPTEN__
    GLFWimage images[1];
    images[0].pixels = stbi_load((Instance::get()->initInfo.contentDir + name).c_str(), &images[0].width, &images[0].height, nullptr, 4);
    glfwSetWindowIcon(windowMain, 1, images);
    stbi_image_free(images[0].pixels);
#endif
}
