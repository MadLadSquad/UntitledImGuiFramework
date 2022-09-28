#pragma once
#include <Core/Defines.hpp>
#include <Core/Types.hpp>

namespace UImGui
{
    struct UIMGUI_PUBLIC_API RendererData
    {
        bool bVulkan = false;
        bool bUsingVSync = true;
        uint32_t msaaSamples = 8;
        bool bSampleRateShading = false;
        float sampleRateShadingMult = 0.0f;
    };

    class UIMGUI_PUBLIC_API RendererInternal
    {
    public:
        RendererInternal() = default;

        void start() noexcept;
        void stop() noexcept;
    private:
        friend class Renderer;

        void loadConfig();
        void saveConfig() const noexcept;

        RendererData data{};
    };

}