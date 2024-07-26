#include "Global.hpp"
#include <Instance.hpp>
#ifdef _WIN32
    #include <windows.h>
#endif

UImGui::Global::Global() noexcept
{
    Logger::log("Constructed global", UVK_LOG_TYPE_NOTE);
    Utility::interruptSignalHandler();
}

UImGui::Global::~Global() noexcept
{
    Logger::log("Destroyed global", UVK_LOG_TYPE_NOTE);
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
