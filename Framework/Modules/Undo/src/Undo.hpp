#pragma once
#ifdef UIMGUI_UNDO_MODULE_ENABLED
#include <Core.hpp>
#include <deque>

namespace UImGui
{
    struct UIMGUI_PUBLIC_API TransactionPayload
    {
        void* payload;
        size_t size;
    };

    struct UIMGUI_PUBLIC_API Transaction
    {
        std::function<void(TransactionPayload&)> undofunc;
        std::function<void(TransactionPayload&)> redofunc;
        TransactionPayload payload;
    };

    class UIMGUI_PUBLIC_API StateTracker
    {
    public:
        StateTracker() = default;
        StateTracker(const StateTracker&) = delete;
        void operator=(StateTracker const&) = delete;

        void init() noexcept;
        static void push(const Transaction& transaction) noexcept;

        static void undo() noexcept;
        static void redo() noexcept;
    private:
        void pushAction(const Transaction& transaction);

        void uundo() noexcept;
        void rredo() noexcept;

        size_t transactionSize = 100;

        std::deque<Transaction*> undoStack;
        std::deque<Transaction*> redoStack;
        std::deque<Transaction> transactions;
    };
}
#endif