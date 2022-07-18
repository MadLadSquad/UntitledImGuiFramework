#pragma once
#include <Defines.hpp>
#include <Types.hpp>

namespace UImGui
{
    class UIMGUI_PUBLIC_API Texture
    {
    public:
        Texture() = default;
        explicit Texture(String file) noexcept;
        void init(String file) noexcept;

        void load() noexcept;
        void loadImGui() noexcept;

        [[nodiscard]] const uint32_t& get() const noexcept;

        void use() const noexcept;
        [[nodiscard]] const FVector2& size() const noexcept;
        void clear() noexcept;
        ~Texture() noexcept;
    private:
        FString filename{};
        uint32_t id = 0;
        FVector2 sz = { 0.0f, 0.0f };
        int channels = 0;
    };
}