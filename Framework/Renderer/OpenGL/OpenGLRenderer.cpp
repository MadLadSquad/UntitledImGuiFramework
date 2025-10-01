#include "OpenGLRenderer.hpp"
#include <Renderer.hpp>
#include <ImGui/ImGui.hpp>
#include <Interfaces/WindowInterface.hpp>
#ifdef __APPLE__
    #include <OpenGL/GL.h>
#else
    #include <glad/include/glad/gl.h>
#endif
#include <imgui_impl_opengl3.h>

#ifdef __EMSCRIPTEN__
    #include <emscripten/html5.h>
#endif

#include <Defines.hpp>
#include <Renderer/RendererUtils.hpp>
#include <Interfaces/RendererInterface.hpp>

void UImGui::OpenGLRenderer::parseCustomConfig(YAML::Node&) noexcept{}

void UImGui::OpenGLRenderer::setupWindowIntegration() noexcept
{
    RendererUtils::OpenGL::setHints
    (
        UIMGUI_LATEST_OPENGL_VERSION,

#ifdef __EMSCRIPTEN__
        UIMGUI_RENDERER_CLIENT_API_OPENGL_ES,
        UIMGUI_OPENGL_PROFILE_ANY,
        false,
#else
        UIMGUI_RENDERER_CLIENT_API_OPENGL,
        UIMGUI_OPENGL_PROFILE_CORE,
        true,
#endif

        Renderer::data().msaaSamples
    );
}

void UImGui::OpenGLRenderer::setupPostWindowCreation() noexcept
{
    RendererUtils::OpenGL::setCurrentContext(RendererUtils::OpenGL::createContext());
    RendererUtils::OpenGL::setSwapInterval(Renderer::data().bUsingVSync);
#if !__APPLE__
    const int version = gladLoadGL(RendererUtils::OpenGL::getProcAddressFunction());
    Logger::log
    (
#ifdef __EMSCRIPTEN__
        "Successfully loaded WebGL ",
#else
        "Successfully loaded OpenGL ",
#endif
        ULOG_LOG_TYPE_SUCCESS, GLAD_VERSION_MAJOR(version), ".", GLAD_VERSION_MINOR(version)
    );
#endif

    glEnable(GL_MULTISAMPLE);
    glEnable(GL_DEPTH_TEST);

    const auto size = Window::getWindowSize();

    // Set viewport and global pointer to use in callbacks
    glViewport(0, 0, CAST(int, size.x), CAST(int, size.y));
}

void UImGui::OpenGLRenderer::init(RendererInternalMetadata& metadata) noexcept
{
    metadata.vendorString = FCAST(const char*, glGetString(GL_VENDOR));
    if (metadata.vendorString.starts_with("NVIDIA"))
    {
        metadata.driverVersion = FCAST(const char*, glGetString(GL_VERSION));
        metadata.apiVersion = metadata.driverVersion;

        metadata.driverVersion.erase(0, metadata.driverVersion.find("NVIDIA ") + strlen("NVIDIA "));
        metadata.apiVersion.erase(metadata.apiVersion.find(" NVIDIA"));
    }
    metadata.gpuName = FCAST(const char*, glGetString(GL_RENDERER));

    Logger::log("Running on device - ", ULOG_LOG_TYPE_NOTE, metadata.gpuName);

    Window::pushWindowResizeCallback([](const int width, const int height) -> void
    {
        glViewport(0, 0, width, height);
    });
}

void UImGui::OpenGLRenderer::renderStart(double deltaTime) noexcept
{
    const auto& colours = ImGui::GetStyle().Colors[ImGuiCol_WindowBg];
    glClearColor(colours.x, colours.y, colours.z, colours.w);
    glClear(GL_COLOR_BUFFER_BIT);
}

void UImGui::OpenGLRenderer::renderEnd(double deltaTime) noexcept
{
    RendererUtils::OpenGL::swapFramebuffers();
}

void UImGui::OpenGLRenderer::destroy() noexcept
{

}

void UImGui::OpenGLRenderer::ImGuiNewFrame() noexcept
{
    ImGui_ImplOpenGL3_NewFrame();
    RendererUtils::beginImGuiFrame();
    glUseProgram(0);
}

void UImGui::OpenGLRenderer::ImGuiShutdown() noexcept
{
    ImGui_ImplOpenGL3_Shutdown();
}

void UImGui::OpenGLRenderer::ImGuiInit() noexcept
{
    RendererUtils::OpenGL::ImGuiInit(UIMGUI_LATEST_GLSL_VERSION);
}

void UImGui::OpenGLRenderer::ImGuiRenderData() noexcept
{
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void UImGui::OpenGLRenderer::waitOnGPU() noexcept
{
}
