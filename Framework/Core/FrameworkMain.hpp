#pragma once
#include <C/CDefines.h>
#include "Global.hpp"

namespace UImGui
{
    class UIMGUI_PUBLIC_API FrameworkMain
    {
    public:
        FrameworkMain() = delete;
        FrameworkMain(const FrameworkMain&) = delete;
        void operator=(FrameworkMain const&) = delete;

        // Shares the important global context pointers between the executable and the shared library
        static void setupGlobal(Global* global, AllocatorFuncs* funcs, LoggerInternal* logger) noexcept;
        // Parser CLI arguments
        static void parseArguments(Instance* instance, int argc, char** argv) noexcept;
    };
}