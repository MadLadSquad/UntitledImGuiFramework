#pragma once
#include <Core/Defines.hpp>
#include <Core/Types.hpp>
#include <thread>

namespace UImGui
{
    /**
     * @brief There are 2 types of logic threads, temporary or persistent. This enum defines them
     * @enum UIMGUI_LOGIC_THREAD_TYPE_EVENT_QUEUE_BEGIN - Called as part of calling the begin events but multi-threaded
     * @enum UIMGUI_LOGIC_THREAD_TYPE_EVENT_QUEUE_TICK - Called as part of calling the tick events but multi-threaded
     * @enum UIMGUI_LOGIC_THREAD_TYPE_EVENT_QUEUE_END - Called as part of calling the end events but multi-threaded
     * @enum UIMGUI_LOGIC_THREAD_TYPE_EVENT_QUEUE_INDEPENDENT - Independent thread that calls itself, instead of being
     * part of an event queue
     */
    enum [[maybe_unused]] LogicThreadType
    {
        UIMGUI_LOGIC_THREAD_TYPE_EVENT_QUEUE_BEGIN,
        UIMGUI_LOGIC_THREAD_TYPE_EVENT_QUEUE_TICK,
        UIMGUI_LOGIC_THREAD_TYPE_EVENT_QUEUE_END,
        UIMGUI_LOGIC_THREAD_TYPE_INDEPENDENT
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
     * @var event - An std::function that takes a LogicThread& and returns void. Called on normal operation
     * @var terminate - An std::function that takes a LogicThread& and returns void. Called when the thread is stopped
     * @var type - An enum variable that defines the type of the thread
     * @var name - The name string identifier for the thread(not related to any internal OS thread data)
     * @var id - The numerical ID of the thread(not related to any internal OS thread data)
     */
    struct UIMGUI_PUBLIC_API LogicThread
    {
    public:
        // Event safety - all ready
        std::function<void(LogicThread&)> event{};
        // Event safety - all ready
        std::function<void(LogicThread&)> terminate{};

        LogicThreadType type = UIMGUI_LOGIC_THREAD_TYPE_EVENT_QUEUE_TICK;

        const LogicThreadState& state() noexcept;

        FString name{};
        uint64_t id{};

        void* additionalData = nullptr;
        size_t additionalDataSize = 0;

        float deltaTime = 0.0f; // Only used for tick events
    private:
        LogicThreadState sstate = UIMGUI_LOGIC_THREAD_STATE_ACTIVE;
    };

    class LogicThreadsManager
    {
    public:
        LogicThreadsManager() noexcept;
        ~LogicThreadsManager() noexcept;

        void addThread(LogicThread& thread) noexcept;
    private:
        void runInlineBeginThreads() noexcept;
        void runInlineTickThreads(float deltaTime) noexcept;
        void runInlineEndThreads() noexcept;

        typedef std::vector<std::vector<LogicThread*>> Events;

        std::vector<std::thread> threads;
        Events events;

        LogicThreadType currentLogicThreadExecutionType;

        Events beginEvents;
        Events endEvents;
        Events tickEvents;

        // Set this default in case our compiler can't find how many threads we're using. We're going to assume that it's
        // running on a 6 core CPU because of the latest Steam Hardware survey(Winter 2023). -1 for the main thread
        size_t threadNum = 11;

        size_t currentThreadBalanceIndex = 0;
    };

    class UIMGUI_PUBLIC_API LogicThreads
    {
    public:

    private:

    };
}