#include "LogicThreads.hpp"

const UImGui::LogicThreadState& UImGui::LogicThread::state() noexcept
{
    return sstate;
}

UImGui::LogicThreadsManager::LogicThreadsManager() noexcept
{
    threadNum = std::thread::hardware_concurrency() - 1;
    events.resize(threadNum);
    threads.resize(threadNum);

    for (size_t i = 0; i < threadNum; i++)
    {
        //threads[i] = std::thread([&]() -> void {
//
        //    switch (currentLogicThreadExecutionType)
        //    {
        //    case UIMGUI_LOGIC_THREAD_TYPE_EVENT_QUEUE_BEGIN:
        //
        //        break;
        //    case UIMGUI_LOGIC_THREAD_TYPE_EVENT_QUEUE_TICK:
//
        //        break;
        //    case UIMGUI_LOGIC_THREAD_TYPE_EVENT_QUEUE_END:
//
        //        break;
        //    default:
        //        break;
        //    }
//
        //    //for (auto& a : event)
        //    //{
        //    //    a->event(*a);
        //    //}
        //});
    }
}

void UImGui::LogicThreadsManager::addThread(UImGui::LogicThread& thread) noexcept
{
    // Push the thread to the current active thread
    events[currentThreadBalanceIndex].push_back(&thread);

    // Update index
    ++currentThreadBalanceIndex;
    if (currentThreadBalanceIndex == threadNum)
        currentThreadBalanceIndex = 0;
}

UImGui::LogicThreadsManager::~LogicThreadsManager() noexcept
{
    //for (auto& thread : threads)
    //    thread->terminate(*thread);
}

void UImGui::LogicThreadsManager::runInlineBeginThreads() noexcept
{

}

void UImGui::LogicThreadsManager::runInlineTickThreads(float deltaTime) noexcept
{

}

void UImGui::LogicThreadsManager::runInlineEndThreads() noexcept
{

}
