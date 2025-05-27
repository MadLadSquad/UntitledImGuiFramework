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

        class UIMGUI_PUBLIC_API OpenGL
        {
        public:
            OpenGL() = delete;
            OpenGL(const OpenGL&) = delete;
            void operator=(OpenGL const&) = delete;

            typedef UImGui_OpenGLProfile Profile;

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
            static void swapFramebuffer() noexcept;
        };

        class UIMGUI_PUBLIC_API WebGPU
        {
        public:
            WebGPU() = delete;
            WebGPU(const WebGPU&) = delete;
            void operator=(WebGPU const&) = delete;

            static bool supported() noexcept;
        };
    private:
    };
}
