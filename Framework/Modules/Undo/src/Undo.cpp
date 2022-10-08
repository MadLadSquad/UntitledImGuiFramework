#ifdef UIMGUI_UNDO_MODULE_ENABLED
#include "Undo.hpp"
#include "Global.hpp"
#include <Modules/Manager/ModulesManager.hpp>

void UImGui::StateTracker::init() noexcept
{
    transactionSize = Modules::data().maxTransactions;
}

void UImGui::StateTracker::push(const UImGui::Transaction& transaction) noexcept
{
    internalGlobal.modulesManager.stateTracker.pushAction(transaction);
}

void UImGui::StateTracker::undo() noexcept
{
    internalGlobal.modulesManager.stateTracker.uundo();
}

void UImGui::StateTracker::redo() noexcept
{
    internalGlobal.modulesManager.stateTracker.rredo();
}

void UImGui::StateTracker::pushAction(const UImGui::Transaction& transaction)
{
    if (transactions.size() == transactionSize)
    {
        // Destroying half of the buffer saves memory and performance for future transactions
        for (uint32_t i = 0; i < (transactionSize/2); i++)
        {
            for (int j = 0; j < undoStack.size(); j++)
            {
                if (&transactions[i] == undoStack[j])
                {
                    undoStack[j] = nullptr;
                    for (int m = 0; m <= j; m++)
                        undoStack.pop_front();
                }
            }

            for (int j = 0; j < redoStack.size(); j++)
            {
                if (&transactions[i] == redoStack[j])
                {
                    redoStack[j] = nullptr;
                    for (int m = 0; m <= j; m++)
                        redoStack.pop_front();
                }
            }

            transactions.pop_front();
        }
    }
    transactions.push_back(transaction);
    undoStack.push_back(&transactions.back());
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