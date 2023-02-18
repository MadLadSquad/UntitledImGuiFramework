#include "Global.hpp"
#include <Instance.hpp>
#ifdef _WIN32
    #include <windows.h>
#endif

UImGui::Global::Global() noexcept
{
    static bool bFirst = true;
    if (bFirst)
    {

        bFirst = false;
    }
}

UImGui::Global::~Global() noexcept
{
#ifdef _WIN32
    ExitProcess(0);
#endif
}

void UImGui::Global::init() noexcept
{
    window.createWindow();

    modulesManagerr.init();
}
