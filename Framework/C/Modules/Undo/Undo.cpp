#include "Undo.h"
#ifdef UIMGUI_UNDO_MODULE_ENABLED
#ifdef __cplusplus
#include "Modules/Undo/src/Undo.hpp"
extern "C"
{
#endif
void UImGui_StateTracker_push(const UImGui_CTransaction transaction, const bool bRedoIsInit)
{
    UImGui::StateTracker::push({
        .undofunc = [&](UImGui::TransactionPayload& payload) -> void
        {
            transaction.undoFunc(&payload);
        },
        .redofunc = [&](UImGui::TransactionPayload& payload) -> void
        {
            transaction.redoFunc(&payload);
        },
        .payload = transaction.payload
    }, bRedoIsInit);
}

void UImGui_StateTracker_undo()
{
    UImGui::StateTracker::undo();
}

void UImGui_StateTracker_redo()
{
    UImGui::StateTracker::redo();
}
#ifdef __cplusplus
}
#endif
#endif