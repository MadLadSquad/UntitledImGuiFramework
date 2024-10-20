#include "CAllocator.h"

void* UImGui_Allocator_allocate(const size_t n)
{
    return malloc(n);
}

void UImGui_Allocator_deallocate(void* ptr)
{
    free(ptr);
}

