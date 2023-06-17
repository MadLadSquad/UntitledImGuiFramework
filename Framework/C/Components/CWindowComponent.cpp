#include "CWindowComponent.h"
#include <Components/WindowComponent.hpp>

class CWindowComponentInternalClass : public UImGui::WindowComponent
{
public:
    CWindowComponentInternalClass()
    {
        construct(&data);
    }

    virtual void begin() override
    {
        beginAutohandle();
        beginF(&data);
    }

    virtual void tick(float deltaTime) override
    {
        tickAutohandle(deltaTime);
        tickF(&data, deltaTime);
    }

    virtual void end() override
    {
        endAutohandle();
        endF(&data);
    }

    virtual ~CWindowComponentInternalClass() override
    {
        destruct(&data);
    }

    UImGui_CComponentData_P data =
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


UImGui_CComponentHandle UImGui_WindowComponent_makeCWindowComponent(UImGui_ComponentRegularFun construct,
                                            UImGui_ComponentRegularFun begin, UImGui_ComponentTickFun tick, UImGui_ComponentRegularFun end,
                                            UImGui_ComponentRegularFun destruct, UImGui_CComponentData data)
{
    auto* handle = (CWindowComponentInternalClass*)UImGui::WindowComponent::make<CWindowComponentInternalClass>();
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

UImGui_CComponentData_P* UImGui_WindowComponent_getCWindowComponentData(UImGui_CComponentHandle handle)
{
    return &static_cast<CWindowComponentInternalClass*>(handle)->data;
}

void UImGui_WindowComponent_destroyCWindowComponent(UImGui_CComponentHandle* handle)
{
    delete (CWindowComponentInternalClass*)handle;
}

UImGui_String UImGui_WindowComponent_getCWindowComponentName(UImGui_CComponentHandle handle)
{
    return static_cast<CWindowComponentInternalClass*>(handle)->name.c_str();
}