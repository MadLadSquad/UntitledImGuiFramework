#include "Window.hpp"
#include <GLFW/glfw3.h>

#include <Core/Global.hpp>
#include <Interfaces/WindowInterface.hpp>

UImGui::Monitor::Monitor(GLFWmonitor* monitor) noexcept
{
#ifndef __EMSCRIPTEN__
    this->monitor = monitor;
    glfwSetMonitorUserPointer(this->monitor, (void*)this);
#endif
}

UImGui::FVector2 UImGui::Monitor::getPhysicalSize() const noexcept
{
#ifndef __EMSCRIPTEN__
    int width = 0;
    int height = 0;
    glfwGetMonitorPhysicalSize(monitor, &width, &height);

    return FVector2{ static_cast<float>(width), static_cast<float>(height) };
#else
    return { 0.0f, 0.0f };
#endif
}

UImGui::FVector2 UImGui::Monitor::getContentScale() const noexcept
{
#ifndef __EMSCRIPTEN__
    FVector2 f = {};
    glfwGetMonitorContentScale(monitor, &f.x, &f.y);
    return f;
#else
    return { 0.0f, 0.0f };
#endif
}

UImGui::FVector2 UImGui::Monitor::getVirtualPosition() const noexcept
{
#ifndef __EMSCRIPTEN__
    int x = 0;
    int y = 0;
    glfwGetMonitorPos(monitor, &x, &y);

    return FVector2{ static_cast<float>(x), static_cast<float>(y) };
#else
    return { 0.0f, 0.0f };
#endif
}

UImGui::FVector4 UImGui::Monitor::getWorkArea() const noexcept
{
#ifndef __EMSCRIPTEN__
    int x = 0;
    int y = 0;
    int width = 0;
    int height = 0;

    glfwGetMonitorWorkarea(monitor, &x, &y, &width, &height);
    return FVector4
            {
                    static_cast<float>(x),static_cast<float>(y),
                    static_cast<float>(width), static_cast<float>(height)
            };
#else
    return { 0.0f, 0.0f, 0.0f, 0.0f };
#endif
}

UImGui::FString UImGui::Monitor::getName() const noexcept
{
#ifndef __EMSCRIPTEN__
    return { glfwGetMonitorName(monitor) };
#else
    return {};
#endif
}

void UImGui::Monitor::pushEvent(const std::function<void(Monitor&, MonitorState)>& f) noexcept
{
#ifndef __EMSCRIPTEN__
    events.push_back(f);
#endif
}

UImGui_CMonitorData UImGui::Monitor::CInternalGetMonitorClassDoNotTouch::UImGui_Window_getWindowMonitor()
{
#ifndef __EMSCRIPTEN__
    const auto tmp = Window::getWindowMonitor();
    return UImGui_CMonitorData
            {
                    .additionalData = tmp.additionalData,
                    .additionalDataSize = tmp.additionalDataSize,
                    .monitor = tmp.monitor,
            };
#else
    return {};
#endif
}

void UImGui::Monitor::CInternalGetMonitorClassDoNotTouch::pushGlobalMonitorCallbackFun(const UImGui::Monitor& monitor,
                                                                                       const UImGui::MonitorState state,
                                                                                       const UImGui_Window_pushGlobalMonitorCallbackFun f)
{
#ifndef __EMSCRIPTEN__
    UImGui_CMonitorData dt;
    UImGui_Monitor_initWithMonitor_Internal(&dt, monitor.monitor);
    dt.additionalData = monitor.additionalData;
    dt.additionalDataSize = monitor.additionalDataSize;

    f(&dt, state);
#endif
}

void UImGui::Monitor::CInternalGetMonitorClassDoNotTouch::UImGui_Monitor_pushEvent(UImGui_CMonitorData* data,
                                                                                   const UImGui_Monitor_EventsFun f)
{
#ifndef __EMSCRIPTEN__
    for (auto& a : UImGui::Window::getMonitors())
    {
        if (a.monitor == data->monitor)
        {
            a.pushEvent([&](Monitor& fMonitor, const MonitorState state) -> void
                        {
                            UImGui_CMonitorData dt;
                            UImGui_Monitor_initWithMonitor_Internal(&dt, data->monitor);
                            dt.additionalData = data->additionalData;
                            dt.additionalDataSize = data->additionalDataSize;

                            f(&dt, state);
                        });
            return;
        }
    }
    Logger::log("Invalid internal monitor address, used when pushing a monitor-local event! Address: ", ULOG_LOG_TYPE_ERROR, data->monitor);
#endif
}

void UImGui::Monitor::CInternalGetMonitorClassDoNotTouch::UImGui_Monitor_setWindowMonitor(const UImGui_CMonitorData* monitor)
{
#ifndef __EMSCRIPTEN__
    Monitor m;
    m.monitor = monitor->monitor;

    UImGui::Window::setWindowMonitor(m);
#endif
}

UImGui_CMonitorData* UImGui::Monitor::CInternalGetMonitorClassDoNotTouch::UImGui_Window_getMonitors(size_t* size)
{
#ifndef __EMSCRIPTEN__
    auto& monitors = Global::get().deallocationStruct.monitors;
    monitors.clear();
    for (const auto& a : Window::getMonitors())
    {
        monitors.push_back(
                {
                        .additionalData = a.additionalData,
                        .additionalDataSize = a.additionalDataSize,
                        .monitor = a.monitor
                });
    }
    *size = monitors.size();
    return monitors.data();
#else
    return nullptr;
#endif
}
