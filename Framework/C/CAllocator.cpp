#include "CAllocator.h"
#include <Global.hpp>

void* UImGui_Allocator_private_allocate(const size_t n)
{
    return malloc(n);
}

void UImGui_Allocator_private_deallocate(void* ptr)
{
    free(ptr);
}

void* UImGui_Allocator_allocate(const size_t n)
{
    return UImGui::Global::get().allocFunc(n);
}

void UImGui_Allocator_deallocate(void* ptr)
{
    UImGui::Global::get().deallocFunc(ptr);
}

