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
