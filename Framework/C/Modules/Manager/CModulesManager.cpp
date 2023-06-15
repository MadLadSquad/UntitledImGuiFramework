#include "CModulesManager.hpp"
#include <Modules/Manager/ModulesManager.hpp>

void UImGui_Modules_save()
{
    UImGui::Modules::save();
}

UImGui_ModuleSettings* UImGui_Modules_data()
{
    return &UImGui::Modules::data();
}