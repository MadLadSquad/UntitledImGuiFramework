#include "CMonitor.h"
#include <Core/Interfaces/WindowInterface.hpp>
#include <Window/GenericWindow/GenericMonitor.hpp>

#define cast(x) reinterpret_cast<UImGui::Monitor*>(x)

UImGui_FVector4 UImGui_Monitor_getWorkArea(UImGui_MonitorData* data)
{
    return cast(data)->getWorkArea();
}

double UImGui_Monitor_getContentScale(UImGui_MonitorData* data)
{
    return cast(data)->getContentScale();
}

UImGui_String UImGui_Monitor_getName(UImGui_MonitorData* data)
{
    return cast(data)->getName();
}

UImGui_FVector2 UImGui_Monitor_getSize(UImGui_MonitorData* data)
{
    return cast(data)->getSize();
}

float UImGui_Monitor_getPixelDensity(UImGui_MonitorData* data)
{
    return cast(data)->getPixelDensity();
}

class CGenericMonitor final : public UImGui::GenericMonitor
{
public:
    UImGui::FVector4 getWorkArea(UImGui::MonitorData& data) noexcept override
    {
        return getWorkAreaFun(&data);
    }

    UImGui::FVector2 getSize(UImGui::MonitorData& data) noexcept override
    {
        return getSizeFun(&data);
    }

    UImGui::String getName(UImGui::MonitorData& data) noexcept override
    {
        return getNameFun(&data);
    }

    double getContentScale(UImGui::MonitorData& data) noexcept override
    {
        return getContentScaleFun(&data);
    }

    float getPixelDensity(UImGui::MonitorData& data) noexcept override
    {
        return getPixelDensityFun(&data);
    }

    UImGui_FVector4(*getWorkAreaFun)(UImGui_MonitorData*){};
    double(*getContentScaleFun)(UImGui_MonitorData*){};
    UImGui_String(*getNameFun)(UImGui_MonitorData*){};
    UImGui_FVector2(*getSizeFun)(UImGui_MonitorData*){};
    float(*getPixelDensityFun)(UImGui_MonitorData*){};
};

UImGui_CGenericMonitor* UImGui_CGenericMonitor_allocate(
                                                            UImGui_FVector4(*getWorkArea)(UImGui_MonitorData*),
                                                            double(*getContentScale)(UImGui_MonitorData*),
                                                            UImGui_String(*getName)(UImGui_MonitorData*),
                                                            UImGui_FVector2(*getSize)(UImGui_MonitorData*),
                                                            float(*getPixelDensity)(UImGui_MonitorData*)
                                                        )
{
    auto* result = new CGenericMonitor{};
    result->getWorkAreaFun = getWorkArea;
    result->getContentScaleFun = getContentScale;
    result->getNameFun = getName;
    result->getSizeFun = getSize;
    result->getPixelDensityFun = getPixelDensity;
    return result;
}

void UImGui_CGenericMonitor_free(UImGui_CGenericMonitor* monitor)
{
    delete static_cast<CGenericMonitor*>(monitor);
}
