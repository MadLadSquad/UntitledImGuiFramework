#pragma once
#include <C/CDefines.h>

#ifdef __cplusplus
extern "C"
{
#endif
    // Returns true for as long as the main loop should keep rendering, and false once the window has been asked to
    // close
    // Event safety - post-begin
    UIMGUI_PUBLIC_API bool UImGui_WindowUtils_shouldRender();

    // Event safety - post-begin
    // In milliseconds
    UIMGUI_PUBLIC_API void UImGui_WindowUtils_pollEvents(double* now, double* deltaTime, double* lastTime);

    // Event safety - post-begin
    // Timeout in milliseconds
    UIMGUI_PUBLIC_API void UImGui_WindowUtils_waitEventsTimeout(double timeout);

    // Event safety - post-begin
    UIMGUI_PUBLIC_API void UImGui_WindowUtils_waitEvents();
#ifdef __cplusplus
}
#endif