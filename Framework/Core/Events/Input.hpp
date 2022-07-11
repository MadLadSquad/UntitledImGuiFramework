#pragma once
#include <Core/Defines.hpp>
#include <Core/Types.hpp>

namespace UImGui
{
    struct UIMGUI_PUBLIC_API InputAction
    {
        InputAction() = default;

        bool operator==(const uint8_t& st) const noexcept;
        bool operator!=(const uint8_t& st) const noexcept;

        FString name{};
        uint16_t keyCode{};
        uint8_t state{};
    };

    class UIMGUI_PUBLIC_API Input
    {
    public:
        Input() = delete;
        Input(const Input&) = delete;
        void operator=(Input const&) = delete;

        static uint8_t getKey(uint16_t key) noexcept;
        static const InputAction& getAction(const UImGui::FString& name) noexcept;

        static std::vector<InputAction>& getActions() noexcept;

        static FVector2 getMousePositionChange() noexcept;
        static FVector2 getCurrentMousePosition() noexcept;
        static FVector2 getLastMousePosition() noexcept;

        static FVector2 getScroll() noexcept;
    };
}