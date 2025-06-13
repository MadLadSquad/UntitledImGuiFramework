#pragma once
#include <Core/Types.hpp>

namespace UImGui
{
    class UIMGUI_PUBLIC_API Layouts
    {
    public:
        Layouts() = delete;
        Layouts(const Layouts&) = delete;
        void operator=(Layouts const&) = delete;

        // Get/Set whether layouts should be saved
        // Event Safety - Construct, post-construct
        static bool& getLoadLayout() noexcept;
        // Get/Set whether layouts should be saved
        // Event Safety - Construct, post-construct
        static bool& getSaveLayout() noexcept;
        // Event Safety - begin, style, post-begin
        static FString& layoutLocation() noexcept;

        // Event Safety - begin, style, post-begin
        static void loadLayout(String layout) noexcept;
        // Event Safety - begin, style, post-begin
        static void saveLayout(String layout) noexcept;
    };
}