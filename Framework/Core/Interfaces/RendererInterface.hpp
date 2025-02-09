#pragma once
#include <Core/Types.hpp>
#include "Renderer.hpp"

namespace UImGui
{
    class UIMGUI_PUBLIC_API Renderer
    {
    public:
        // Event Safety - Any time
        static RendererData& data() noexcept;
        // Event Safety - Any time
        static void saveSettings() noexcept;

        // Event Safety - begin, post-begin
        static const FString& getVendorString() noexcept;
        // Event Safety - begin, post-begin
        static const FString& getAPIVersion() noexcept;
        // Event Safety - begin, post-begin
        static const FString& getGPUName() noexcept;
        // Event Safety - begin, post-begin
        static const FString& getDriverVersion() noexcept;

        // Forces an update even when idling in power saving mode
        // Event Safety - begin, post-begin
        static void forceUpdate() noexcept;
    private:
        friend class RendererInternal;
        friend class WindowInternal;
        friend class WebGPUTexture;
        friend class VulkanTexture;
        friend class Texture;

        static RendererInternal& get() noexcept;
    };
}