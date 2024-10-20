#pragma once
#include <C/CAllocator.h>

namespace UImGui
{
    template<typename T>
    class UIMGUI_PUBLIC_API Allocator
    {
    public:
        using value_type = T;

        Allocator() noexcept = default;

        template<typename T1>
        explicit Allocator(const Allocator<T1>&) noexcept
        {
        }

        static T* allocate(const size_t n) noexcept
        {
            return (n == 0) ? nullptr : static_cast<T*>(UImGui_Allocator_allocate(n * sizeof(T)));
        }

        static void deallocate(T* ptr, size_t) noexcept
        {
            if (ptr != nullptr)
                UImGui_Allocator_deallocate(ptr);
        }

        template<typename T1>
        bool operator==(const Allocator<T1>&) const noexcept
        {
            return true;
        }

        template<typename T1>
        bool operator!=(const Allocator<T1>&) const noexcept
        {
            return false;
        }
    private:
    };
}
