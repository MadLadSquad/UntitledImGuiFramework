#include "CTitlebarComponent.h"
#include <Components/TitlebarComponent.hpp>

class CTitlebarComponentInternalClass : public UImGui::TitlebarComponent
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

    virtual void tick(float deltaTime) override
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


UImGui_CComponentHandle UImGui_Titlebar_makeCTitlebarComponent(UImGui_ComponentRegularFun construct,
                                                               UImGui_ComponentRegularFun begin, UImGui_ComponentTickFun tick, UImGui_ComponentRegularFun end,
                                                               UImGui_ComponentRegularFun destruct, UImGui_CComponentData data)
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

UImGui_CComponentData_P* UImGui_Titlebar_getCTitlebarComponentData(UImGui_CComponentHandle handle)
{
    return &static_cast<CTitlebarComponentInternalClass*>(handle)->dataP;
}

void UImGui_Titlebar_destroyCTitlebarComponent(UImGui_CComponentHandle handle)
{
    delete (CTitlebarComponentInternalClass*)handle;
}

UImGui_String UImGui_Titlebar_getCTitlebarComponentName(UImGui_CComponentHandle handle)
{
    return static_cast<CTitlebarComponentInternalClass*>(handle)->name.c_str();
}