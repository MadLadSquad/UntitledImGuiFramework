#include "WindowGLFW.hpp"
#include <GLFW/glfw3.h>
#include "imgui_impl_glfw.h"
#include <Interfaces/RendererInterface.hpp>

#ifndef __EMSCRIPTEN__
void UImGui::WindowGLFW::ImGuiInitFor_Vulkan() noexcept
{
    ImGui_ImplGlfw_InitForVulkan(window, true);
}
#endif

void UImGui::WindowGLFW::ImGuiInitFor_OpenGL() noexcept
{
    ImGui_ImplGlfw_InitForOpenGL(window, true);
}

void UImGui::WindowGLFW::ImGuiInitFor_Other() noexcept
{
    ImGui_ImplGlfw_InitForOther(window, true);
}

void UImGui::WindowGLFW::ImGuiInstallCallbacks() noexcept
{
#ifdef __EMSCRIPTEN__
    ImGui_ImplGlfw_InstallEmscriptenCallbacks(window, Renderer::data().emscriptenCanvas);
#endif
}

void UImGui::WindowGLFW::ImGuiNewFrame() noexcept
{
    ImGui_ImplGlfw_NewFrame();
}

void UImGui::WindowGLFW::ImGuiShutdown() noexcept
{
    ImGui_ImplGlfw_Shutdown();
}

bool UImGui::WindowGLFW::shouldRender() noexcept
{
    return glfwWindowShouldClose(window);
}

void UImGui::WindowGLFW::pollEvents(double& now, double& deltaTime, double& lastTime) noexcept
{
    glfwPollEvents();

    now = glfwGetTime();
    deltaTime = now - lastTime;
    lastTime = now;

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

    // Needs to be updated at every frame
    if (windowData.bSurfaceTransparent)
        glfwSetWindowOpacity(window, ImGui::GetStyle().Colors[ImGuiCol_WindowBg].w);
}

void UImGui::WindowGLFW::waitEventsTimeout(const double timeout) noexcept
{
    glfwWaitEventsTimeout(timeout);
}

void UImGui::WindowGLFW::waitEvents() noexcept
{
    glfwWaitEvents();
}

void UImGui::WindowGLFW::OpenGL_swapBuffers() noexcept
{
    glfwSwapBuffers(window);
}

UImGui::RendererUtils::OpenGL::Context* UImGui::WindowGLFW::OpenGL_createContext() noexcept
{
    return nullptr;
}

UImGui::RendererUtils::OpenGL::Context* UImGui::WindowGLFW::OpenGL_getCurrentContext() noexcept
{
    return glfwGetCurrentContext();
}

void UImGui::WindowGLFW::OpenGL_setCurrentContext(RendererUtils::OpenGL::Context* ctx) noexcept
{
    glfwMakeContextCurrent(window); UNUSED(ctx);
}

void UImGui::WindowGLFW::OpenGL_destroyContext(RendererUtils::OpenGL::Context* ctx) noexcept
{
    UNUSED(ctx);
}

void UImGui::WindowGLFW::OpenGL_setSwapInterval(const int interval) noexcept
{
    glfwSwapInterval(interval);
}

void UImGui::WindowGLFW::OpenGL_setHints(const int majorVersion, const int minorVersion, const RendererClientAPI clientApi, const RendererUtils::OpenGL::Profile profile, const bool bForwardCompatible, uint32_t samples) noexcept
{
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, majorVersion);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minorVersion);
    glfwWindowHint(GLFW_CLIENT_API, CAST(int, clientApi));
    glfwWindowHint(GLFW_OPENGL_PROFILE, CAST(int, profile));
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, CAST(int, bForwardCompatible));

    glfwWindowHint(GLFW_SAMPLES, CAST(int, samples));
}

UImGui::RendererUtils::OpenGL::GetProcAddressFun UImGui::WindowGLFW::OpenGL_getProcAddressFunction() noexcept
{
    return glfwGetProcAddress;
}

void UImGui::WindowGLFW::setupManualRenderingHints() noexcept
{
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
}
#ifndef __EMSCRIPTEN__
VkResult UImGui::WindowGLFW::Vulkan_createWindowSurface(const VkInstance instance, const VkAllocationCallbacks* allocator, VkSurfaceKHR* surface) noexcept
{
    return glfwCreateWindowSurface(instance, window, allocator, surface);
}

void UImGui::WindowGLFW::Vulkan_fillInstanceAndLayerExtensions(TVector<const char*>& instanceExtensions, TVector<const char*>& instanceLayers) noexcept
{
    uint32_t glfwExtensionCount = 0;
    const char** glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

    instanceExtensions.resize(glfwExtensionCount);
    for (size_t i = 0; i < glfwExtensionCount; i++)
        instanceExtensions[i] = glfwExtensions[i];
}
#endif
