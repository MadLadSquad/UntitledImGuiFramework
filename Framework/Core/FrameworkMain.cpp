#include "FrameworkMain.hpp"

#include <Components/Instance.hpp>
#include <Renderer/Renderer.hpp>

void UImGui::FrameworkMain::setupGlobal(Global* global, AllocatorFuncs* funcs, LoggerInternal* logger) noexcept
{
    UNUSED(Global::get(global));
    UNUSED(AllocatorFuncs::get(funcs));
    UNUSED(LoggerInternal::get(logger));
}

void UImGui::FrameworkMain::parseArguments(Instance* instance, const int argc, char** argv) noexcept
{
    instance->argc = argc;
    instance->argv = argv;
    instance->reloadApplicationMetadata();

    instance->arguments.resize(argc);
    for (int i = 0; i < argc; i++)
        instance->arguments[i] = argv[i];
    Global::get().instance = instance;
}