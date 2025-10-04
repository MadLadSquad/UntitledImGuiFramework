#include "WindowGLFW.hpp"
#include <Core/Components/Instance.hpp>
#include <Renderer/RendererUtils.hpp>
#include <Renderer/GenericRenderer/GenericRenderer.hpp>

#include <GLFW/glfw3.h>

#define STB_IMAGE_IMPLEMENTATION
#include <ThirdParty/source-libraries/stb_image.h>

UImGui::WindowGLFW::WindowGLFW() noexcept
{
    monitor = dynamic_cast<GenericMonitor*>(&monitorGLFW);
    keys.fill(KeyStateReleased);
}

void UImGui::WindowGLFW::createWindow() noexcept
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

    window = glfwCreateWindow(static_cast<int>(windowSizeS.x), static_cast<int>(windowSizeS.y), windowData.name.c_str(), monitor, nullptr);
    if (!window)
    {
        Logger::log("GLFW window creation failed!", ULOG_LOG_TYPE_ERROR);
        glfwTerminate();
        return;
    }
    Logger::log("Created window", ULOG_LOG_TYPE_NOTE);

    // Load window icon
    setIcon((Instance::get()->initInfo.contentDir + windowData.iconLocation).c_str());
    setSizeLimits({ windowData.sizeLimits.x, windowData.sizeLimits.y }, { windowData.sizeLimits.z, windowData.sizeLimits.w });
    setSizeLimitByAspectRatio(windowData.aspectRatioSizeLimit);

    Logger::log("Window was created successfully", ULOG_LOG_TYPE_SUCCESS);

    // Set framebuffer size
    int tempx = CAST(int, windowSizeS.x);
    int tempy = CAST(int, windowSizeS.y);

    glfwGetFramebufferSize(window, &tempx, &tempy);

    windowSizeS.x = CAST(float, tempx);
    windowSizeS.y = CAST(float, tempy);

    RendererUtils::getRenderer()->setupPostWindowCreation();

    // Set callbacks
    configureCallbacks();
    glfwSetWindowUserPointer(window, this);
}

void UImGui::WindowGLFW::destroyWindow() noexcept
{
    // This is a strange workaround for a Wayland-only crash. Check https://github.com/GLFW/glfw/issues/2744
    glfwPollEvents();

    glfwDestroyWindow(window);
    glfwTerminate();
}

void UImGui::WindowGLFW::configureDefaultHints() const noexcept
{
    glfwWindowHint(GLFW_RESIZABLE, windowData.bResizeable);
#ifndef __EMSCRIPTEN__
    glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, windowData.bSurfaceTransparent);
    glfwWindowHint(GLFW_VISIBLE, !windowData.bHidden);
    glfwWindowHint(GLFW_FOCUSED, windowData.bFocused);
    glfwWindowHint(GLFW_DECORATED, windowData.bDecorated);
    glfwWindowHint(GLFW_MAXIMIZED, windowData.bMaximised);

#ifdef GLFW_PLATFORM_X11
    glfwWindowHintString(GLFW_X11_CLASS_NAME, Instance::get()->applicationName.c_str());
    glfwWindowHintString(GLFW_X11_INSTANCE_NAME, Instance::get()->applicationName.c_str());
#endif
#ifdef GLFW_PLATFORM_WAYLAND
    glfwWindowHintString(GLFW_WAYLAND_APP_ID, Instance::get()->applicationName.c_str());
#endif
#endif

    Logger::log("Window settings configured", ULOG_LOG_TYPE_NOTE);
}

void UImGui::WindowGLFW::setTitle(const String name) noexcept
{
    glfwSetWindowTitle(window, name);
}

UImGui::String UImGui::WindowGLFW::getTitle() noexcept
{
#ifndef __EMSCRIPTEN__
    return glfwGetWindowTitle(window);
#else
    return "";
#endif
}

void UImGui::WindowGLFW::setTitleSetting(const String name) noexcept
{
    windowData.name = name;
}

UImGui::String UImGui::WindowGLFW::getTitleSetting() noexcept
{
    return windowData.name.c_str();
}

void UImGui::WindowGLFW::setIcon(const String name) noexcept
{
#ifndef __EMSCRIPTEN__
    GLFWimage images[1];
    images[0].pixels = stbi_load(name, &images[0].width, &images[0].height, nullptr, 4);
    if (images[0].pixels != nullptr)
    {
        currentIconLocation = name;
        glfwSetWindowIcon(window, 1, images);
        stbi_image_free(images[0].pixels);
    }
    else
        Logger::log("Couldn't load the window icon at location: ", ULOG_LOG_TYPE_WARNING, name);
#endif
}

UImGui::String UImGui::WindowGLFW::getIconLocation() noexcept
{
    return currentIconLocation.c_str();
}

UImGui::String UImGui::WindowGLFW::getIconLocationSetting() noexcept
{
    return windowData.iconLocation.c_str();
}

void UImGui::WindowGLFW::setIconLocationSetting(const String location) noexcept
{
    windowData.iconLocation = location;
}


void* UImGui::WindowGLFW::getInternal() noexcept
{
    return window;
}

UImGui::GenericWindow* UImGui::WindowGLFW::get() noexcept
{
    return this;
}
