#pragma once
#include <C/Rendering/CRendererUtils.h>

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

        // Renderer a new dear imgui frame
        // Event safety - post-begin
        static void beginImGuiFrame() noexcept;

        class UIMGUI_PUBLIC_API OpenGL
        {
        public:
            OpenGL() = delete;
            OpenGL(const OpenGL&) = delete;
            void operator=(OpenGL const&) = delete;

            typedef UImGui_OpenGLProfile Profile;
            typedef UImGui_OpenGLContext Context;

            // Call this inside the window hints interface function of the GenericRenderer class
            //
            // Recommended args:
            // Emscripten/Web targets - UIMGUI_LATEST_OPENGL_VERSION, UIMGUI_RENDERER_CLIENT_API_OPENGL_ES, UIMGUI_OPENGL_PROFILE_ANY, false
            // Desktop - UIMGUI_LATEST_OPENGL_VERSION, UIMGUI_RENDERER_CLIENT_API_OPENGL, UIMGUI_OPENGL_PROFILE_CORE, true
            //
            // Event safety - startup, post-startup
            static void setHints(int majorVersion, int minorVersion, RendererClientAPI clientApi, Profile profile, bool bForwardCompatible) noexcept;

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

            // Set the swap interval for the OpenGL renderer
            // Event safety - startup, post-startup
            static void setSwapInterval(int interval) noexcept;
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
