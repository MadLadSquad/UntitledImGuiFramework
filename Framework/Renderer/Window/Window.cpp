#define STB_IMAGE_IMPLEMENTATION
#include "Window.hpp"
#ifdef __APPLE__
    #include <OpenGL/GL.h>
#else
    #include <glad/include/glad/gl.h>
#endif
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

#define SAVE_CONFIG_YAML_BASIC(x, y) out << YAML::Key << #x << YAML::Value << windowData.y

void UImGui::WindowInternal::saveConfig(bool bSaveKeybindings) const noexcept
{
    auto* instance = Instance::get();
    std::ofstream fout((instance->initInfo.configDir + "Core/Window.yaml").c_str());
    {
        YAML::Emitter out;
        out << YAML::BeginMap;

        SAVE_CONFIG_YAML_BASIC(layout-location, layoutLocation);
        SAVE_CONFIG_YAML_BASIC(icon, iconLocation);

        out << YAML::Key << "width" << YAML::Value << windowSize.x;
        out << YAML::Key << "height" << YAML::Value << windowSize.y;

        SAVE_CONFIG_YAML_BASIC(fullscreen, fullscreen);
        SAVE_CONFIG_YAML_BASIC(window-name, name);
        SAVE_CONFIG_YAML_BASIC(resizeable, bResizeable);
        SAVE_CONFIG_YAML_BASIC(transparent-surface, bSurfaceTransparent);
        SAVE_CONFIG_YAML_BASIC(hidden, bHidden);
        SAVE_CONFIG_YAML_BASIC(focusedisplay, bFocused);
        SAVE_CONFIG_YAML_BASIC(size-limits, sizeLimits);
        SAVE_CONFIG_YAML_BASIC(aspect-ratio-size-limit, aspectRatioSizeLimit);
        SAVE_CONFIG_YAML_BASIC(decoratedisplay, bDecorated);
        SAVE_CONFIG_YAML_BASIC(maximisedisplay, bMaximised);

        out << YAML::EndMap;

        fout << out.c_str();
        fout.close();
    }

    if (bSaveKeybindings)
    {
        YAML::Emitter out;
        out << YAML::BeginMap << YAML::Key << "bindings" << YAML::BeginSeq;

        for (auto& a : inputActionList)
        {
            out << YAML::BeginMap << YAML::Key << "key" << YAML::Value << a.name;
            out << YAML::Key << "val" << YAML::Value << YAML::Flow << YAML::BeginSeq;
            for (auto& f : a.keyCodes)
                out << static_cast<int>(f);
            out << YAML::EndSeq;
            out << YAML::EndMap;
        }
        out << YAML::EndSeq << YAML::EndMap;

        fout = std::ofstream((instance->initInfo.configDir + "Core/Keybindings.yaml").c_str());
        fout << out.c_str();
        fout.close();
    }
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

    if (Renderer::data().bVulkan)
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API); // Have to set this to NO_API because that's how Vulkan is done in it
    else
    {
#ifdef __EMSCRIPTEN__
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
        glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
#else
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        #ifdef __APPLE__
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
        #else
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
        #endif
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, true);
#endif
        glfwWindowHint(GLFW_SAMPLES, static_cast<int>(Renderer::data().msaaSamples));
    }

#ifndef __EMSCRIPTEN__
    glfwWindowHint(GLFW_RESIZABLE, windowData.bResizeable);
    glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, windowData.bSurfaceTransparent);
    glfwWindowHint(GLFW_VISIBLE, !windowData.bHidden);
    glfwWindowHint(GLFW_FOCUSED, windowData.bFocused);
    glfwWindowHint(GLFW_DECORATED, windowData.bDecorated);
    glfwWindowHint(GLFW_MAXIMIZED, windowData.bMaximised);
#endif

    Logger::log("Window settings configured", ULOG_LOG_TYPE_NOTE);
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

    if (!Renderer::data().bVulkan)
    {
#if !__APPLE__
        const int version = gladLoadGL(glfwGetProcAddress);
        Logger::log(
    #ifdef EMSCRIPTEN
            "Successfully loaded WebGL ",
    #else
            "Successfully loaded OpenGL ",
    #endif
            ULOG_LOG_TYPE_SUCCESS, GLAD_VERSION_MAJOR(version), ".", GLAD_VERSION_MINOR(version));
#endif
        glEnable(GL_MULTISAMPLE);
        glEnable(GL_DEPTH_TEST);
        // Set viewport and global pointer to use in callbacks
        glViewport(0, 0, tempx, tempy);
    }
    glfwSetWindowUserPointer(windowMain, this);
}

void UImGui::WindowInternal::destroyWindow() const noexcept
{
    glfwDestroyWindow(windowMain);
    glfwTerminate();
}

#define OPEN_CONFIG_GET_YAML_BASIC(x, y, z) if (out[#x]) windowData.y = out[#x].as<z>()

void UImGui::WindowInternal::openConfig()
{
    YAML::Node out;

    const auto* instance = Instance::get();
    try
    {
        out = YAML::LoadFile((instance->initInfo.configDir + "Core/Window.yaml").c_str());
    }
    catch (YAML::BadFile&)
    {
        Logger::log("Couldn't open the Window.yaml config file, please fix this error before shipping for production! Starting with default settings!", ULOG_LOG_TYPE_ERROR);
        goto skip_window_config;
    }

    if (out["width"] && out["height"])
    {
        windowSize.x = out["width"].as<float>();
        windowSize.y = out["height"].as<float>();
    }

    OPEN_CONFIG_GET_YAML_BASIC(icon, iconLocation, FString);
    OPEN_CONFIG_GET_YAML_BASIC(layout-location, layoutLocation, FString);
    OPEN_CONFIG_GET_YAML_BASIC(fullscreen, fullscreen, bool);
    OPEN_CONFIG_GET_YAML_BASIC(window-name, name, FString);
    OPEN_CONFIG_GET_YAML_BASIC(resizeable, bResizeable, bool);
    OPEN_CONFIG_GET_YAML_BASIC(transparent-surface, bSurfaceTransparent, bool);
    OPEN_CONFIG_GET_YAML_BASIC(visible, bHidden, bool);
    OPEN_CONFIG_GET_YAML_BASIC(focusedisplay, bFocused, bool);
    OPEN_CONFIG_GET_YAML_BASIC(size-limits, sizeLimits, FVector4);
    OPEN_CONFIG_GET_YAML_BASIC(aspect-ratio-size-limit, aspectRatioSizeLimit, FVector2);
    OPEN_CONFIG_GET_YAML_BASIC(decoratedisplay, bDecorated, bool);
    OPEN_CONFIG_GET_YAML_BASIC(maximisedisplay, bMaximised, bool);
skip_window_config:

    try
    {
        out = YAML::LoadFile((instance->initInfo.configDir + "Core/Keybindings.yaml").c_str());
    }
    catch (YAML::BadFile&)
    {
        Logger::log("Couldn't open the Keybindings.yaml config file, please fix this error before shipping for production! Starting with default settings!", ULOG_LOG_TYPE_ERROR);
        return;
    }

    auto binds = out["bindings"];
    if (binds)
    {
        for (const YAML::Node& a : binds)
        {
            InputAction action;
            action.name = a["key"].as<FString>();
            action.keyCodes = a["val"].as<TVector<uint16_t>>();
            inputActionList.push_back(action);
        }
    }
}

void UImGui::WindowInternal::close() const noexcept
{
    glfwSetWindowShouldClose(windowMain, true);
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