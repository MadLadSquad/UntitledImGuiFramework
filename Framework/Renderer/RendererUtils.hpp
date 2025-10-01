#pragma once
#include <C/Renderer/CRendererUtils.h>
#include <Core/Types.hpp>
#ifndef __EMSCRIPTEN__
    #include <vulkan/vulkan.h>
#endif

struct ImGui_ImplVulkan_InitInfo;
namespace UImGui
{
    typedef UImGui_RendererClientAPI RendererClientAPI;
    class GenericRenderer;

    class UIMGUI_PUBLIC_API RendererUtils
    {
    public:
        RendererUtils() = delete;
        RendererUtils(const RendererUtils&) = delete;
        void operator=(RendererUtils const&) = delete;

        // Call this inside the window hints interface function of the GenericRenderer class
        // Event safety - startup, post-startup
        static void setupManually() noexcept;

        // Returns a pointer to the current renderer
        // Event safety - any-time
        static GenericRenderer* getRenderer() noexcept;

        // Render a new dear imgui frame
        // Event safety - post-begin
        static void beginImGuiFrame() noexcept;

        // Initialise dear imgui for rendering with a renderer that is not OpenGL or Vulkan
        // CAUTION: For OpenGL or Vulkan, use the specialisations under their respective namespaces
        // Event safety - style, begin
        static void ImGuiInitOther() noexcept;

        // Install window callbacks for dear imgui(only needed for some renderers, such as WebGPU or OpenGL)
        // Event safety - style, begin
        static void ImGuiInstallCallbacks() noexcept;

        class UIMGUI_PUBLIC_API OpenGL
        {
        public:
            OpenGL() = delete;
            OpenGL(const OpenGL&) = delete;
            void operator=(OpenGL const&) = delete;

            typedef UImGui_OpenGLProfile Profile;
            typedef UImGui_OpenGLContext Context;
            typedef UImGui_OpenGL_GetProcAddressFun GetProcAddressFun;

            // Call this inside the window hints interface function of the GenericRenderer class
            //
            // Recommended args:
            // Emscripten/Web targets - UIMGUI_LATEST_OPENGL_VERSION, UIMGUI_RENDERER_CLIENT_API_OPENGL_ES, UIMGUI_OPENGL_PROFILE_ANY, false, Renderer::data().msaaSamples
            // Desktop - UIMGUI_LATEST_OPENGL_VERSION, UIMGUI_RENDERER_CLIENT_API_OPENGL, UIMGUI_OPENGL_PROFILE_CORE, true, Renderer::data().msaaSamples
            //
            // Event safety - startup, post-startup
            static void setHints(int majorVersion, int minorVersion, RendererClientAPI clientApi, Profile profile, bool bForwardCompatible, uint32_t samples) noexcept;

            // Swaps buffers for OpenGL.
            // Event safety - post-begin
            static void swapFramebuffers() noexcept;

            // Create an OpenGL context(call this in post-window creation)
            // Event safety - startup, post-startup
            static Context* createContext() noexcept;

            // Set current OpenGL context(call this in post-window creation)
            // Event safety - startup, post-startup
            static void setCurrentContext(Context* ctx) noexcept;

            // Destroy the current OpenGL context
            // Event safety - post-startup
            static void destroyContext(Context* ctx) noexcept;

            // Get the current OpenGL context
            // Event safety - startup, post-startup
            static Context* getCurrentContext() noexcept;

            // Returns the function for getting the OpenGL proc address
            // Event safety - startup, post-startup
            static GetProcAddressFun getProcAddressFunction() noexcept;

            // Set the swap interval for the OpenGL renderer
            // Event safety - startup, post-startup
            static void setSwapInterval(int interval) noexcept;

            // Initialise dear imgui for rendering with OpenGL
            // Event safety - style, begin
            static void ImGuiInit(String glslVersion) noexcept;
        };

        class UIMGUI_PUBLIC_API Vulkan
        {
        public:
            Vulkan() = delete;
            Vulkan(const Vulkan&) = delete;
            void operator=(Vulkan const&) = delete;

#ifndef __EMSCRIPTEN__
            // Initialise dear imgui for rendering with Vulkan
            // Event safety - style, begin
            static void ImGuiInit(ImGui_ImplVulkan_InitInfo& initInfo) noexcept;

            // Event safety - post-startup
            static VkResult createWindowSurface(VkInstance instance, const VkAllocationCallbacks* allocator, VkSurfaceKHR* surface) noexcept;
            // Event safety - post-startup
            static void fillInstanceAndLayerExtensions(TVector<const char*>& instanceExtensions, TVector<const char*>& instanceLayers) noexcept;
#endif
        };

        class UIMGUI_PUBLIC_API WebGPU
        {
        public:
            WebGPU() = delete;
            WebGPU(const WebGPU&) = delete;
            void operator=(WebGPU const&) = delete;

            // Check for WebGPU support
            // Event safety - any time
            static bool supported() noexcept;
        };
    private:
    };
}
