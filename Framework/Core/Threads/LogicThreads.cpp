#include "LogicThreads.hpp"

const UImGui::LogicThreadState& UImGui::LogicThread::state() noexcept
{
    return sstate;
}
