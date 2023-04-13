#define STB_IMAGE_IMPLEMENTATION
#include "Window.hpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <ThirdParty/source-libraries/stb_image.h>
#include <yaml.h>
#include <Interfaces/RendererInterface.hpp>

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

void UImGui::WindowInternal::saveConfig(bool bSaveKeybindings) noexcept
{
    YAML::Emitter out;
    out << YAML::BeginMap;

    out << YAML::Key << "icon" << YAML::Value << windowData.iconLocation;
    out << YAML::Key << "width" << YAML::Value << windowSize.x;
    out << YAML::Key << "height" << YAML::Value << windowSize.y;
    out << YAML::Key << "fullscreen" << YAML::Value << windowData.fullscreen;
    out << YAML::Key << "window-name" << YAML::Value << windowData.name;

    std::ofstream fout("../Config/Core/Window.yaml");
    fout << out.c_str();
    fout.close();

    if (bSaveKeybindings)
    {
        YAML::Emitter o;
        o << YAML::BeginMap << YAML::Key << "bindings" << YAML::BeginSeq;
        for (auto& a : inputActionList)
        {
            out << YAML::BeginMap << YAML::Key << "key" << YAML::Value << a.name;
            out << YAML::Key << "val" << YAML::Value << a.keyCode << YAML::EndMap;
        }
        out << YAML::EndSeq << YAML::EndMap;

        fout = std::ofstream("../Config/Core/Keybindings.yaml");
        fout << o.c_str();
        fout.close();
    }
}

void UImGui::WindowInternal::setTitle(UImGui::String title) noexcept
{
    glfwSetWindowTitle(windowMain, title);
    windowData.name = title;
}

void UImGui::WindowInternal::setCursorVisibility(bool bVisible) noexcept
{
    bVisible ? glfwSetInputMode(windowMain, GLFW_CURSOR, GLFW_CURSOR_NORMAL) : glfwSetInputMode(windowMain, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

UImGui::FVector2 UImGui::WindowInternal::getMousePositionChange() noexcept
{
    FVector2 ret = mouseOffset;
    mouseOffset = { 0.0f, 0.0f };

    return ret;
}

UImGui::FVector2 UImGui::WindowInternal::getScroll() noexcept
{
    FVector2 ret = scroll;
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
        Logger::log("GLFW initialisation failed!", UVK_LOG_TYPE_ERROR);
        glfwTerminate();
        return;
    }
    Logger::log("Setting up the window", UVK_LOG_TYPE_NOTE);

    // Add GLFW window flags and enable OpenGL
    // TODO: Support Vulkan here
    glewExperimental = GL_TRUE;
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_SAMPLES, 16);

    Logger::log("Window settings configured", UVK_LOG_TYPE_NOTE);
    GLFWmonitor* monitor = nullptr;
    if (windowData.fullscreen)
        monitor = glfwGetPrimaryMonitor();

    windowMain = glfwCreateWindow((int)windowSize.x, (int)windowSize.y, windowData.name.c_str(), monitor, nullptr);
    if (!windowMain)
    {
        Logger::log("GLFW window creation failed!", UVK_LOG_TYPE_ERROR);
        glfwTerminate();
        return;
    }
    Logger::log("Created window", UVK_LOG_TYPE_NOTE);

    // Load window icon
    GLFWimage images[1];
    images[0].pixels = stbi_load(windowData.iconLocation.c_str(), &images[0].width, &images[0].height, nullptr, 4);
    glfwSetWindowIcon(windowMain, 1, images);
    stbi_image_free(images[0].pixels);

    Logger::log("Window was created successfully", UVK_LOG_TYPE_SUCCESS);

    // Set framebuffer size
    // TODO: Support Vulkan here
    int tempx = static_cast<int>(windowSize.x);
    int tempy = static_cast<int>(windowSize.y);

    glfwGetFramebufferSize(windowMain, &tempx, &tempy);

    windowSize.x = static_cast<float>(tempx);
    windowSize.y = static_cast<float>(tempy);

    // Set the context
    glfwMakeContextCurrent(windowMain);

    // Set swap interval
    if (Renderer::data().bUsingVSync)
        glfwSwapInterval(1);

    // Set callbacks
    configureCallbacks();

    // Init glew
    // TODO: Support Vulkan here
    if (glewInit() != GLEW_OK)
    {
        glfwDestroyWindow(windowMain);
        glfwTerminate();
        Logger::log("GLEW initialisation failed!", UVK_LOG_TYPE_ERROR);
        return;
    }
    // Set viewport and global pointer to use in callbacks
    glViewport(0, 0, tempx, tempy);
    glfwSetWindowUserPointer(windowMain, this);
}

void UImGui::WindowInternal::destroyWindow() noexcept
{
    glfwDestroyWindow(windowMain);
    glfwTerminate();
}

void UImGui::WindowInternal::configureCallbacks() noexcept
{
    glfwSetFramebufferSizeCallback(windowMain, framebufferSizeCallback);
    glfwSetKeyCallback(windowMain, keyboardInputCallback);
    glfwSetCursorPosCallback(windowMain, mouseCursorPositionCallback);
    glfwSetMouseButtonCallback(windowMain, mouseKeyInputCallback);
    glfwSetScrollCallback(windowMain, scrollInputCallback);
    glfwSetWindowPosCallback(windowMain, windowPositionCallback);
}

void UImGui::WindowInternal::framebufferSizeCallback(GLFWwindow* window, int width, int height) noexcept
{
    auto* windowInst = static_cast<WindowInternal*>(glfwGetWindowUserPointer(window));

    windowInst->windowSize.x = static_cast<float>(width);
    windowInst->windowSize.y = static_cast<float>(height);
    glViewport(0, 0, width, height);
}

void UImGui::WindowInternal::keyboardInputCallback(GLFWwindow* window, int key, int scanCode, int action, int mods) noexcept
{
    auto* wind = (WindowInternal*)glfwGetWindowUserPointer(window);
    for (auto& a : wind->inputActionList)
    {
        if (a.keyCode == key)
        {
            a.state = action;
        }
    }

    wind->keys[key] = action;
}

void UImGui::WindowInternal::mouseKeyInputCallback(GLFWwindow* window, int button, int action, int mods) noexcept
{
    auto* wind = (WindowInternal*)glfwGetWindowUserPointer(window);
    for (auto& a : wind->inputActionList)
    {
        if (a.keyCode == button)
        {
            a.state = action;
        }
    }
    wind->keys[button] = action;
}

void UImGui::WindowInternal::mouseCursorPositionCallback(GLFWwindow* window, double xpos, double ypos) noexcept
{
    auto* windowInst = static_cast<WindowInternal*>(glfwGetWindowUserPointer(window));

    if (windowInst->bFirstMove)
    {
        windowInst->mouseLastPos.x = static_cast<float>(xpos);
        windowInst->mouseLastPos.y = static_cast<float>(ypos);
        windowInst->bFirstMove = false;
    }

    windowInst->mouseOffset.x = static_cast<float>(xpos) - windowInst->mouseLastPos.x;
    windowInst->mouseOffset.y = windowInst->mouseLastPos.y - static_cast<float>(ypos);

    windowInst->mouseLastPos.x = static_cast<float>(xpos);
    windowInst->mouseLastPos.y = static_cast<float>(ypos);
}

void UImGui::WindowInternal::scrollInputCallback(GLFWwindow* window, double xoffset, double yoffset) noexcept
{
    auto* windowInst = static_cast<WindowInternal*>(glfwGetWindowUserPointer(window));

    windowInst->scroll = { static_cast<float>(xoffset), static_cast<float>(yoffset) };
}

void UImGui::WindowInternal::windowPositionCallback(GLFWwindow* window, int xpos, int ypos) noexcept
{
    auto* windowInst = static_cast<WindowInternal*>(glfwGetWindowUserPointer(window));

    windowInst->windowLastPos.x = windowInst->windowCurrentPos.x;
    windowInst->windowLastPos.y = windowInst->windowCurrentPos.y;

    windowInst->windowCurrentPos.x = static_cast<float>(xpos);
    windowInst->windowCurrentPos.y = static_cast<float>(ypos);
}

void UImGui::WindowInternal::openConfig()
{
    YAML::Node out;

    try
    {
        out = YAML::LoadFile("../Config/Core/Window.yaml");
    }
    catch (YAML::BadFile&)
    {
        Logger::log("Couldn't open the Window.yaml config file, please fix this error before shipping for production! Starting with default settings!", UVK_LOG_TYPE_ERROR);
        goto skip_window_config;
    }

    if (out["icon"])
        windowData.iconLocation = "../Content/" + out["icon"].as<FString>();
    if (out["width"] && out["height"])
    {
        windowSize.x = out["width"].as<float>();
        windowSize.y = out["height"].as<float>();
    }
    if (out["fullscreen"])
        windowData.fullscreen = out["fullscreen"].as<bool>();
    if (out["window-name"])
        windowData.name = out["window-name"].as<FString>();
skip_window_config:

    try
    {
        out = YAML::LoadFile("../Config/Core/Keybindings.yaml");
    }
    catch (YAML::BadFile&)
    {
        Logger::log("Couldn't open the Keybindings.yaml config file, please fix this error before shipping for production! Starting with default settings!", UVK_LOG_TYPE_ERROR);
        return;
    }

    auto binds = out["bindings"];
    if (binds)
    {
        for (const YAML::Node& a : binds)
        {
            InputAction action;
            action.name = a["key"].as<std::string>();
            action.keyCode = a["val"].as<uint16_t>();
            inputActionList.push_back(action);
        }
    }
}

void UImGui::WindowInternal::close() noexcept
{
    glfwSetWindowShouldClose(windowMain, true);
}