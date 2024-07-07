#pragma once
#ifdef __APPLE__

namespace UImGui::MacOSWindow
{
    void setWindowAlwaysBelow(void* window);
    void setWindowAlwaysAbove(void* window);
}
#endif