#pragma once
#include <Core/Types.hpp>
#include <C/Window/CMonitor.h>

namespace UImGui
{
    typedef UImGui_MonitorData MonitorData;

    class UIMGUI_PUBLIC_API GenericMonitor
    {
    public:
        GenericMonitor() noexcept = default;
        virtual ~GenericMonitor() = default;

        virtual FVector4 getWorkArea(MonitorData& data) noexcept = 0;
        virtual FVector2 getSize(MonitorData& data) noexcept = 0;

        virtual String getName(MonitorData& data) noexcept = 0;

        virtual double getContentScale(MonitorData& data) noexcept = 0;
        virtual float getPixelDensity(MonitorData& data) noexcept = 0;

        virtual void* getPlatformHandle(MonitorData& data) noexcept = 0;
    };

    class UIMGUI_PUBLIC_API Monitor
    {
    public:
        Monitor() noexcept = default;

        // Get the monitor bounds as FVector4 where x = x position, y = y position, z = width, w = height
        // Event safety - begin, style, post-begin
        FVector4 getWorkArea() noexcept;

        // Get the monitor's content scale
        // Event safety - begin, style, post-begin
        double getContentScale() noexcept;

        // Get the monitor's name in UTF-8 encoding
        // Event safety - begin, style, post-begin
        String getName() noexcept;

        // Get the monitor's size
        // Event safety - begin, style, post-begin
        FVector2 getSize() noexcept;

        // Get the monitor's pixel density
        // Event safety - begin, style, post-begin
        float getPixelDensity() noexcept;

        // Get the monitor's platform-specific handle
        // Event safety - begin, style, post-begin
        void* getPlatformHandle() noexcept;

        // Event safety - any time
        MonitorData& get() noexcept;
    private:
        MonitorData data{};
    };
}