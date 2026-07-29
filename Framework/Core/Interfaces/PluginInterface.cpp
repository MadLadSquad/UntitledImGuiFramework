#include "PluginInterface.hpp"
#include <Global.hpp>
#include <urll/urll.h>

bool UImGui::Plugins::load(String location) noexcept
{
#ifndef __EMSCRIPTEN__
    auto* handle = URLL::dlopen(location);
    if (handle == nullptr)
    {
        Logger::log("Couldn't load the plugin at location: ", ULOG_LOG_TYPE_WARNING, location, "', Error: ", URLL::dlerror());
        return false;
    }

    Plugin temp
    {
        .name = location,
        .handle = handle
    };

    // The handle has to be closed on every failure path from here on - the plugin never makes it into get().plugins,
    // so nothing else holds a reference to it and it would leak for the lifetime of the process
    if (URLL::dlsym(handle, "UImGui_Plugin_attach", temp.attach) != handle)
    {
        Logger::log("Couldn't load the attach symbol from the plugin at location: '", ULOG_LOG_TYPE_WARNING, location, "', Error: ", URLL::dlerror());
        URLL::dlclose(handle);
        return false;
    }
    if (URLL::dlsym(handle, "UImGui_Plugin_detach", temp.detach) != handle)
    {
        Logger::log("Couldn't load the detach symbol from the plugin at location: ", ULOG_LOG_TYPE_WARNING, location, "', Error: ", URLL::dlerror());
        URLL::dlclose(handle);
        return false;
    }

    ImGuiMemAllocFunc alloc;
    ImGuiMemFreeFunc free;
    void* userData;

    ImGui::GetAllocatorFunctions(&alloc, &free, &userData);

    // NOTE: allocFunc/freeFunc/userData below point at the three stack locals above, so the context is only valid for
    // the duration of the attach() call. This is fine because Utility::loadContext dereferences them immediately, but
    // it does mean a plugin must not stash the PluginContext pointer and read it later.
    PluginContext ctx
    {
        .global = &Global::get(),
        .allocators = &AllocatorFuncs::get(),
        .loggerContext = &LoggerInternal::get(),
        .imguiContext = ImGui::GetCurrentContext(),
        .allocFunc = &alloc,
        .freeFunc = &free,
        .userData = &userData,
#ifdef UIMGUI_PLOTTING_MODULE_ENABLED
        .implotContext = Modules::data().plotting ? ImPlot::GetCurrentContext() : nullptr,
#else
        .implotContext = nullptr,
#endif
#ifdef UIMGUI_TEXT_UTILS_MODULE_ENABLED
        .textUtilsContext = Modules::data().text_utils ? TextUtils::getTextUtilsData() : nullptr,
#else
        .textUtilsContext = nullptr
#endif
    };
    temp.attach(&ctx);
    get().plugins.push_back(temp);
    Logger::log("Loaded plugin at location: ", ULOG_LOG_TYPE_SUCCESS, location);
#endif
    return true;
}

const UImGui::TVector<UImGui::Plugin>& UImGui::Plugins::getPlugins() noexcept
{
    return get().plugins;
}

void UImGui::Plugins::loadStandard() noexcept
{
    for (auto& a : get().standardPlugins)
        load(a.c_str());
}

void UImGui::Plugins::unloadAll() noexcept
{
#ifndef __EMSCRIPTEN__
    auto& plugins = get().plugins;
    for (auto& a : plugins)
    {
        a.detach();
        if (a.handle != nullptr)
            URLL::dlclose(a.handle);
    }
    plugins.clear();
#endif
}

UImGui::Plugins::~Plugins() noexcept
{
}

UImGui::Plugins& UImGui::Plugins::get() noexcept
{
    return Global::get().plugins;
}
