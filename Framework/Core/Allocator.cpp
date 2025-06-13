#include "Allocator.hpp"

UImGui::AllocatorFuncs& UImGui::AllocatorFuncs::get(AllocatorFuncs* parent) noexcept
{
    static AllocatorFuncs* allocators = parent == nullptr ? getWithCreate() : parent;
    return *allocators;
}

UImGui::AllocatorFuncs* UImGui::AllocatorFuncs::getWithCreate() noexcept
{
    static AllocatorFuncs allocators
    {
        .allocate = UImGui_Allocator_private_allocate,
        .deallocate = UImGui_Allocator_private_deallocate
    };
    return &allocators;
}

void* operator new(const size_t size)
{
    return UImGui_Allocator_allocate(size);
}

void operator delete(void* ptr) noexcept
{
    UImGui_Allocator_deallocate(ptr);
}