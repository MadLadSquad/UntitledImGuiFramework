#include "Global.hpp"
#include <Components/Instance.hpp>
#include <Utilities.hpp>

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

UImGui::Global& UImGui::Global::get(Global* parent) noexcept
{
    static Global* global = parent == nullptr ? getWithCreate() : parent;
    return *global;
}

UImGui::Global* UImGui::Global::getWithCreate() noexcept
{
    static Global global{};
    return &global;
}
