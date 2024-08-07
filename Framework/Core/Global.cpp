#include "Global.hpp"
#include <Instance.hpp>
#ifdef _WIN32
    #include <windows.h>
#endif

UImGui::Global::Global() noexcept
{
    Utility::interruptSignalHandler();
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
}

UImGui::Global& UImGui::Global::get() noexcept
{
    static Global global{};
    return global;
}
