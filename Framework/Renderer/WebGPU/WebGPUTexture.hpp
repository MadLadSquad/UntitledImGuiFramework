#pragma once
#include <GenericRenderer/GenericTexture.hpp>

#include "parallel-hashmap/parallel_hashmap/phmap_dump.h"

namespace UImGui
{
    class WebGPUTexture final : public GenericTexture
    {
    public:
        WebGPUTexture() noexcept = default;
        explicit WebGPUTexture(String location) noexcept;

        // Event Safety - Any time
        virtual void init(String location) noexcept override;

        virtual void load(void* data, FVector2 size, uint32_t depth, bool bFreeImageData,
                                const std::function<void(void*)>& freeFunc) noexcept override;

        // Event Safety - Post-begin
        virtual void* get() noexcept override;

        // Cleans up the image data
        // Event Safety - All initiated
        virtual void clear() noexcept override;
        virtual ~WebGPUTexture() noexcept override;
    private:
        uint32_t id = 0;
    };

}
