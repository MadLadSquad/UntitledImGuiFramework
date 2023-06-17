#include "CInstance.h"
#include <Instance.hpp>
#include <Global.hpp>

void UImGui_Instance_setCInitInfo(UImGui_CInitInfo* initInfo)
{
    UImGui::internalGlobal.instance->initInfo.cInitInfo = initInfo;
}

void* UImGui_Instance_getCppInitInfoGlobalData(bool* bAllocatedOnHeap)
{
    auto& initInfo = UImGui::internalGlobal.instance->initInfo;

    *bAllocatedOnHeap = initInfo.bGlobalAllocatedOnHeap;
    return initInfo.globalData;
}

char** UImGui_Instance_getCLIArguments(int* argc)
{
    auto* instance = UImGui::internalGlobal.instance;
    *argc = instance->argc;

    return instance->argv;
}