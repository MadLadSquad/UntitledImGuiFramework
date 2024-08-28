#include "PluginInterface.hpp"
#include <Global.hpp>
#include <urll/urll.h>

bool UImGui::Plugins::load(String location) noexcept
{
    auto* handle = URLL::dlopen(location);
    if (handle == nullptr)
    {
        Logger::log("Couldn't load the plugin at location: ", UVK_LOG_TYPE_WARNING, location, "', Error: ", URLL::dlerror());
        return false;
    }

    Plugin temp
    {
        .name = location,
        .handle = handle
    };

    if (URLL::dlsym(handle, "UImGui_Plugin_attach", temp.attach) != handle)
    {
        Logger::log("Couldn't load the attach symbol from the plugin at location: '", UVK_LOG_TYPE_WARNING, location, "', Error: ", URLL::dlerror());
        return false;
    }
    if (URLL::dlsym(handle, "UImGui_Plugin_detach", temp.detach) != handle)
    {
        Logger::log("Couldn't load the detach symbol from the plugin at location: ", UVK_LOG_TYPE_WARNING, location, "', Error: ", URLL::dlerror());
        return false;
    }

    ImGuiMemAllocFunc alloc;
    ImGuiMemFreeFunc free;
    void* userData;

    ImGui::GetAllocatorFunctions(&alloc, &free, &userData);
    temp.attach(&Global::get(), ImGui::GetCurrentContext(), &alloc, &free, &userData,
#ifdef UIMGUI_PLOTTING_MODULE_ENABLED
        Modules::data().plotting ? ImPlot::GetCurrentContext() : nullptr
#else
        nullptr
#endif
    );
    get().plugins.push_back(temp);
    return true;
}

const std::vector<UImGui::Plugin>& UImGui::Plugins::getPlugins() noexcept
{
    return get().plugins;
}

void UImGui::Plugins::loadStandard() noexcept
{
    for (auto& a : get().standardPlugins)
        load(a.c_str());
}

UImGui::Plugins::~Plugins() noexcept
{
    for (const auto& a : plugins)
        a.detach();
}

UImGui::Plugins& UImGui::Plugins::get() noexcept
{
    return Global::get().plugins;
}