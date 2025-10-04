#pragma once
#include <C/CDefines.h>

#ifdef __cplusplus
extern "C"
{
#endif
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