#include "CTitlebarComponent.h"
#include <Components/TitlebarComponent.hpp>

class CTitlebarComponentInternalClass final : public UImGui::TitlebarComponent
{
public:
    CTitlebarComponentInternalClass()
    {
        construct(&dataP);
    }

    virtual void begin() override
    {
        beginAutohandle();
        beginF(&dataP);
    }

    virtual void tick(const float deltaTime) override
    {
        tickAutohandle(deltaTime);
        tickF(&dataP, deltaTime);
    }

    virtual void end() override
    {
        endAutohandle();
        endF(&dataP);
    }

    virtual ~CTitlebarComponentInternalClass() override
    {
        destruct(&dataP);
    }

    UImGui_CComponentData_P dataP =
    {
        .state = &state,
        .id = &id,
    };

    UImGui_ComponentRegularFun construct = [](UImGui_CComponentData_P*) -> void {};
    UImGui_ComponentRegularFun beginF = [](UImGui_CComponentData_P*) -> void {};
    UImGui_ComponentTickFun tickF = [](UImGui_CComponentData_P*, float) -> void {};
    UImGui_ComponentRegularFun endF = [](UImGui_CComponentData_P*) -> void {};
    UImGui_ComponentRegularFun destruct = [](UImGui_CComponentData_P*) -> void {};
};


UImGui_CComponentHandle* UImGui_Titlebar_makeCTitlebarComponent(const UImGui_ComponentRegularFun construct,
                                                                const UImGui_ComponentRegularFun begin,
                                                                const UImGui_ComponentTickFun tick,
                                                                const UImGui_ComponentRegularFun end,
                                                                const UImGui_ComponentRegularFun destruct,
                                                                UImGui_CComponentData data)
{
    auto* handle = dynamic_cast<CTitlebarComponentInternalClass*>(UImGui::TitlebarComponent::make<CTitlebarComponentInternalClass>());
    handle->state = data.state;
    handle->name = data.name;
    handle->id = data.id;

    handle->construct = construct;
    handle->beginF = begin;
    handle->tickF = tick;
    handle->endF = end;
    handle->destruct = destruct;

    return handle;
}

const UImGui_CComponentData_P* UImGui_Titlebar_getCTitlebarComponentData(const UImGui_CComponentHandle* const handle)
{
    return &CAST(const CTitlebarComponentInternalClass*, handle)->dataP;
}

void UImGui_Titlebar_destroyCTitlebarComponent(const UImGui_CComponentHandle* const handle)
{
    delete CAST(const CTitlebarComponentInternalClass*, handle);
}

UImGui_String UImGui_Titlebar_getCTitlebarComponentName(const UImGui_CComponentHandle* const handle)
{
    return CAST(const CTitlebarComponentInternalClass*, handle)->name.c_str();
}

UImGui_CTitlebarBuilder* UImGui_TitlebarBuilder_init()
{
    return CAST(UImGui_CTitlebarBuilder*, new UImGui::TitlebarBuilder{});
}

void UImGui_TitlebarBuilder_setBuildNativeOnMacOS(UImGui_CTitlebarBuilder* builder, const bool bBuildNativeOnMacOS)
{
    CAST(UImGui::TitlebarBuilder*, builder)->setBuildNativeOnMacOS(bBuildNativeOnMacOS);
}

void UImGui_TitlebarBuilder_setContext(UImGui_CTitlebarBuilder* builder, void* data)
{
    CAST(UImGui::TitlebarBuilder*, builder)->setContext(data);
}

void UImGui_TitlebarBuilder_addMenuItem(UImGui_CTitlebarBuilder* builder, const UImGui_String label, const UImGui_String hint, const UImGui_TitlebarBuilderMenuItemFunc f, bool* bEnabled)
{
    CAST(UImGui::TitlebarBuilder*, builder)->addMenuItem(label, hint, f, bEnabled);
}

void UImGui_TitlebarBuilder_addSeparator(UImGui_CTitlebarBuilder* builder)
{
    CAST(UImGui::TitlebarBuilder*, builder)->addSeparator();
}

void UImGui_TitlebarBuilder_addSubmenu(UImGui_CTitlebarBuilder* builder, const UImGui_String label, UImGui_CTitlebarBuilder* submenu, bool* bEnabled)
{
    CAST(UImGui::TitlebarBuilder*, builder)->addSubmenu(label, *CAST(UImGui::TitlebarBuilder*, submenu), bEnabled);
}

void UImGui_TitlebarBuilder_addCheckbox(UImGui_CTitlebarBuilder* builder, const UImGui_String label, bool* bSelected, bool* bEnabled)
{
    CAST(UImGui::TitlebarBuilder*, builder)->addCheckbox(label, *bSelected, bEnabled);
}

void UImGui_TitlebarBuilder_addRadioGroup(UImGui_CTitlebarBuilder* builder, UImGui_CRadioBuilder* submenu)
{
    CAST(UImGui::TitlebarBuilder*, builder)->addRadioGroup(*CAST(UImGui::RadioBuilder*, submenu));
}

void UImGui_TitlebarBuilder_addAppMenuDefaultItems(UImGui_CTitlebarBuilder* builder)
{
    CAST(UImGui::TitlebarBuilder*, builder)->addAppMenuDefaultItems();
}

void UImGui_TitlebarBuilder_addWindowMenuDefaultItems(UImGui_CTitlebarBuilder* builder)
{
    CAST(UImGui::TitlebarBuilder*, builder)->addWindowMenuDefaultItems();
}

void UImGui_TitlebarBuilder_addHelpMenuDefaultItems(UImGui_CTitlebarBuilder* builder)
{
    CAST(UImGui::TitlebarBuilder*, builder)->addHelpMenuDefaultItems();
}

void UImGui_TitlebarBuilder_finish(UImGui_CTitlebarBuilder* builder)
{
    CAST(UImGui::TitlebarBuilder*, builder)->finish();
}

void UImGui_TitlebarBuilder_render(UImGui_CTitlebarBuilder* builder)
{
    CAST(UImGui::TitlebarBuilder*, builder)->render();
}

void UImGui_TitlebarBuilder_clear(UImGui_CTitlebarBuilder* builder)
{
    CAST(UImGui::TitlebarBuilder*, builder)->clear();
}

void UImGui_TitlebarBuilder_free(UImGui_CTitlebarBuilder* builder)
{
    delete CAST(UImGui::TitlebarBuilder*, builder);
}

UImGui_CRadioBuilder* UImGui_RadioBuilder_init(int* selectedIndex)
{
    return CAST(UImGui_CRadioBuilder*, new UImGui::RadioBuilder(*selectedIndex));
}

void UImGui_RadioBuilder_add(UImGui_CRadioBuilder* builder, const UImGui_String label, bool* bEnabled)
{
    CAST(UImGui::RadioBuilder*, builder)->add(label, bEnabled);
}

void UImGui_RadioBuilder_free(UImGui_CRadioBuilder* builder)
{
    delete CAST(UImGui::RadioBuilder*, builder);
}
