#pragma once
#ifdef __APPLE__

namespace UImGui::MacOSWindow
{
    void setShowWindowOnTaskbar(void* window, bool bShow);
    void setShowWindowInPager(void* window, bool bShow);
    void setWindowAlwaysBelow(void* window);
    void setWindowAlwaysAbove(void* window);
}
#endif