#include "CInstance.h"
#include <Components/Instance.hpp>

#define INIT_INFO UImGui::Instance::get()->initInfo

void UImGui_Instance_setCInitInfo(UImGui_CInitInfo* initInfo)
{
    INIT_INFO.cInitInfo = initInfo;
}

void* UImGui_Instance_getCppInitInfoGlobalData(bool* bAllocatedOnHeap)
{
    *bAllocatedOnHeap = INIT_INFO.bGlobalAllocatedOnHeap;
    return INIT_INFO.globalData;
}

char** UImGui_Instance_getCLIArguments(int* argc)
{
    const auto* instance = UImGui::Instance::get();
    *argc = instance->argc;

    return instance->argv;
}

UImGui_String UImGui_InitInfo_getFrameworkLibraryDir()
{
    return INIT_INFO.frameworkLibraryDir.c_str();
}

UImGui_String UImGui_InitInfo_getApplicationDir()
{
    return INIT_INFO.applicationDir.c_str();
}

UImGui_String UImGui_InitInfo_getApplicationLibraryDir()
{
    return INIT_INFO.applicationLibraryDir.c_str();
}

UImGui_String UImGui_InitInfo_getConfigDir()
{
    return INIT_INFO.configDir.c_str();
}

UImGui_String UImGui_InitInfo_getProjectDir()
{
    return INIT_INFO.projectDir.c_str();
}

UImGui_String UImGui_InitInfo_getContentDir()
{
    return INIT_INFO.contentDir.c_str();
}

UImGui_String UImGui_InitInfo_getFrameworkIncludeDir()
{
    return INIT_INFO.frameworkIncludeDir.c_str();
}

UImGui_String UImGui_InitInfo_getApplicationIncludeDir()
{
    return INIT_INFO.applicationIncludeDir.c_str();
}