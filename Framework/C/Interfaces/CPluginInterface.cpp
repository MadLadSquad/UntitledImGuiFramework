#include "CPluginInterface.h"
#include <Interfaces/PluginInterface.hpp>
#include <Core/CDeallocation.hpp>
#include <Core/Global.hpp>

bool UImGui_Plugins_load(const UImGui_String location)
{
    return UImGui::Plugins::load(location);
}

void UImGui_Plugins_loadStandard()
{
    UImGui::Plugins::loadStandard();
}

UImGui_CPlugin* UImGui_Plugins_getPlugins(size_t* size)
{
    auto& plugins = UImGui::Global::get().deallocationStruct.plugins;
    auto& cppPlugins = UImGui::Plugins::getPlugins();

    plugins.resize(cppPlugins.size());
    *size = plugins.size();

    for (size_t i = 0; i < *size; i++)
    {
        plugins[i].name = cppPlugins[i].name.c_str();
        plugins[i].handle = cppPlugins[i].handle;
    }
    return plugins.data();
}
