#pragma once
#include <Core/Types.hpp>

namespace UImGui
{
    class UIMGUI_PUBLIC_API Layouts
    {
    public:
        Layouts() noexcept = default;

        // Event Safety - begin, style, post-begin
        static bool& getLoadLayout() noexcept;
        // Event Safety - begin, style, post-begin
        static bool& getSaveLayout() noexcept;
        // Event Safety - begin, style, post-begin
        static FString& layoutLocation() noexcept;

        static void loadLayout(String layout) noexcept;
        static void saveLayout(String layout) noexcept;
    };
}