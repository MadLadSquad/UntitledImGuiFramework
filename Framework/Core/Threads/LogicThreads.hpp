#pragma once
#include <Core/Defines.hpp>
#include <Core/Types.hpp>
#include <thread>

namespace UImGui
{
    /**
     * @brief There are 2 types of logic threads, temporary or persistent. This enum defines them
     * @enum UIMGUI_LOGIC_THREAD_TYPE_TEMPORARY - A temporary thread, gets created when a level opens and gets destroyed when
     * it's closed or the application closes
     * @enum UIMGUI_LOGIC_THREAD_TYPE_PERSISTENT - A persistent thread, gets created when a level opens but doesn't get
     * terminated when switching levels
     */
    enum [[maybe_unused]] LogicThreadType
    {
        UIMGUI_LOGIC_THREAD_TYPE_TEMPORARY,
        UIMGUI_LOGIC_THREAD_TYPE_PERSISTENT
    };

    /**
     * @brief Defines the current state of the thread
     * @enum UIMGUI_LOGIC_THREAD_STATE_ACTIVE - Means that the thread is currently active and working on some job
     * @enum UIMGUI_LOGIC_THREAD_STATE_ORPHANED - Means the thread was terminated and is awaiting destruction and
     * removal from the internal thread pool. Any thread created by the threading API can take it over in this state
     */
    enum [[maybe_unused]] LogicThreadState
    {
        UIMGUI_LOGIC_THREAD_STATE_ACTIVE,
        UIMGUI_LOGIC_THREAD_STATE_ORPHANED,
    };

    /**
     * @brief Provides events and functionality needed by the threads API
     * @var standard - An std::function that takes a LogicThread& and returns void. Called on normal operation
     * @var terminate - An std::function that takes a LogicThread& and returns void. Called when the thread is stopped
     * @var type - An enum variable that defines the type of thread this one is i.e. temporary or persistent
     * @var name - The name string identifier for the thread(not related to any internal OS thread data)
     * @var id - The numerical ID of the thread(not related to any internal OS thread data)
     */
    struct UIMGUI_PUBLIC_API LogicThread
    {
    public:
        std::function<void(LogicThread&)> standard{};
        std::function<void(LogicThread&)> terminate{};

        LogicThreadType type = UIMGUI_LOGIC_THREAD_TYPE_TEMPORARY;

        const LogicThreadState& state() noexcept;

        FString name{};
        uint64_t id{};
    private:
        std::thread thread;
        LogicThreadState sstate = UIMGUI_LOGIC_THREAD_STATE_ACTIVE;
    };

    class LogicThreadsManager
    {
    public:

    private:
        // Set this default in case our compiler can't find how many threads we're using. We're going to assume that it's
        // running on a 2 core CPU as nobody uses a 1 core CPU nowadays and given how the toolkit requires a GPU I'm not
        // sure 1 core users have a good enough GPU to run this to begin with
        size_t threadNum = 4;
    };

    class UIMGUI_PUBLIC_API LogicThreads
    {
    public:

    private:

    };
}