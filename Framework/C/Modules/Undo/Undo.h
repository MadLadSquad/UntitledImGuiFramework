#pragma once
#ifdef UIMGUI_UNDO_MODULE_ENABLED
#include <C/CDefines.h>
#include <C/CTypes.h>
#ifdef __cplusplus
extern "C"
{
#endif
    typedef struct UIMGUI_PUBLIC_API UImGui_TransactionPayload
    {
        void* payload;
        size_t size;
    } UImGui_TransactionPayload;

    typedef void(*UImGui_CTransactionCallbackFun)(UImGui_TransactionPayload*);

    typedef struct UIMGUI_PUBLIC_API UImGui_CTransaction
    {
        UImGui_CTransactionCallbackFun undoFunc;
        UImGui_CTransactionCallbackFun redoFunc;
        UImGui_TransactionPayload payload;
    } UImGui_CTransaction;

    // UntitledImGuiFramework Event Safety - Post-begin
    UIMGUI_PUBLIC_API void UImGui_StateTracker_push(UImGui_CTransaction transaction);
    // UntitledImGuiFramework Event Safety - Post-begin
    UIMGUI_PUBLIC_API void UImGui_StateTracker_undo();
    // UntitledImGuiFramework Event Safety - Post-begin
    UIMGUI_PUBLIC_API void UImGui_StateTracker_redo();
#ifdef __cplusplus
}
#endif
#endif