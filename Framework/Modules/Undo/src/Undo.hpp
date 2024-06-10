#pragma once
#ifdef UIMGUI_UNDO_MODULE_ENABLED
#include <Core.hpp>
#include <deque>
#include <C/Modules/Undo/Undo.h>

namespace UImGui
{
    typedef UImGui_TransactionPayload TransactionPayload;

    struct UIMGUI_PUBLIC_API Transaction
    {
        std::function<void(TransactionPayload&)> undofunc{};
        std::function<void(TransactionPayload&)> redofunc{};
        TransactionPayload payload{};
    };

    class UIMGUI_PUBLIC_API StateTracker
    {
    public:
        StateTracker() = default;
        StateTracker(const StateTracker&) = delete;
        void operator=(StateTracker const&) = delete;

        // UntitledImGuiFramework Event Safety - Post-begin
        static void push(const Transaction& transaction, bool bRedoIsInit = false) noexcept;

        // UntitledImGuiFramework Event Safety - Post-begin
        static void undo() noexcept;
        // UntitledImGuiFramework Event Safety - Post-begin
        static void redo() noexcept;
    private:
        friend class ModulesManager;

        void init() noexcept;
        void pushAction(const Transaction& transaction, bool bRedoIsInit);

        void uundo() noexcept;
        void rredo() noexcept;

        size_t transactionSize = 100;

        std::deque<Transaction*> undoStack;
        std::deque<Transaction*> redoStack;
        std::deque<Transaction> transactions;
    };
}
#endif