#pragma once
#include "CDefines.h"

#ifdef __cplusplus
extern "C"
{
#endif
    UIMGUI_PUBLIC_API void* UImGui_Allocator_allocate(size_t n);
    UIMGUI_PUBLIC_API void UImGui_Allocator_deallocate(void* ptr);

#ifdef __cplusplus
}
#endif