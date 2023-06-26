#pragma once
#include <Core/Defines.hpp>
#include <Core/Types.hpp>

// C API, contains the renderer data header, since it is shared between the 2 APIs
#include <C/Internal/RendererData.h>

namespace UImGui
{
    typedef UImGui_RendererData RendererData;

    class UIMGUI_PUBLIC_API RendererInternal
    {
    public:
        RendererInternal() = default;

        void start() noexcept;
        static void stop() noexcept;
    private:
        friend class Renderer;

        FString vendorString;
        FString apiVersion;
        FString driverVersion;
        FString gpuName;

        void loadConfig();
        void saveConfig() const noexcept;

        RendererData data =
        {
            .bVulkan = false,
            .bUsingVSync = true,
            .msaaSamples = 8,
            .bSampleRateShading = false,
            .sampleRateShadingMult = 0.0f,
        };
    };

}