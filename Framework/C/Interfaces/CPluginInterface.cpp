#include "CPluginInterface.h"
#include <Interfaces/PluginInterface.hpp>

bool UImGui_Plugins_load(const UImGui_String location)
{
    return UImGui::Plugins::load(location);
}

void UImGui_Plugins_loadStandard()
{
    UImGui::Plugins::loadStandard();
}
