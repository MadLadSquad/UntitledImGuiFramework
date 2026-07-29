#pragma once
#include <Core/Types.hpp>

namespace UImGui
{
    class UIMGUI_PUBLIC_API WindowUtils
    {
    public:
        WindowUtils() = delete;
        WindowUtils(const WindowUtils&) = delete;
        void operator=(WindowUtils const&) = delete;

        // Returns true for as long as the main loop should keep rendering, and false once the window has been asked to
        // close
        // Event safety - post-begin
        static bool shouldRender() noexcept;

        // Event safety - post-begin
        // In milliseconds
        static void pollEvents(double& now, double& deltaTime, double& lastTime) noexcept;

        // Event safety - post-begin
        // Timeout in milliseconds
        static void waitEventsTimeout(double timeout) noexcept;

        // Event safety - post-begin
        static void waitEvents() noexcept;
    };
}