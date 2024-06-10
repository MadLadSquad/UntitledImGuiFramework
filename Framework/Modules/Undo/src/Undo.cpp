#ifdef UIMGUI_UNDO_MODULE_ENABLED
#include "Undo.hpp"
#include "Global.hpp"
#include <Modules/Manager/ModulesManager.hpp>

void eraseWhenOverBufferSize(std::deque<UImGui::Transaction*>& container, std::deque<UImGui::Transaction>& transactions, size_t i) noexcept
{
    for (size_t j = 0; j < container.size(); j++)
        if (&transactions[i] == container[j])
            container.erase(container.begin(), container.begin() + static_cast<std::remove_reference_t<decltype(container)>::difference_type>(j));
}

void UImGui::StateTracker::init() noexcept
{
    transactionSize = Modules::data().maxTransactions;
}

void UImGui::StateTracker::push(const UImGui::Transaction& transaction, bool bRedoIsInit) noexcept
{
    Modules::get().stateTracker.pushAction(transaction, bRedoIsInit);
}

void UImGui::StateTracker::undo() noexcept
{
    Modules::get().stateTracker.uundo();
}

void UImGui::StateTracker::redo() noexcept
{
    Modules::get().stateTracker.rredo();
}

void UImGui::StateTracker::pushAction(const UImGui::Transaction& transaction, bool bRedoIsInit)
{
    if (transactions.size() == transactionSize)
    {
        // Destroying half of the buffer saves memory and performance for future transactions
        size_t size = transactionSize / 2;

        for (size_t i = 0; i < size; i++)
        {
            eraseWhenOverBufferSize(undoStack, transactions, i);
            eraseWhenOverBufferSize(redoStack, transactions, i);
        }
        transactions.erase(transactions.begin(), transactions.begin() + static_cast<decltype(transactions)::difference_type>(size));
    }
    transactions.push_back(transaction);
    undoStack.push_back(&transactions.back());
    if (bRedoIsInit)
        transactions.back().redofunc(transactions.back().payload);
}

void UImGui::StateTracker::uundo() noexcept
{
    if (!undoStack.empty())
    {
        redoStack.emplace_back(undoStack.back());
        undoStack.back()->undofunc(redoStack.back()->payload);

        undoStack.pop_back();
    }
}

void UImGui::StateTracker::rredo() noexcept
{
    if (!redoStack.empty())
    {
        undoStack.emplace_back(redoStack.back());
        redoStack.back()->redofunc(redoStack.back()->payload);

        redoStack.pop_back();
    }
}
#endif