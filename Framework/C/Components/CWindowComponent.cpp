#include "CWindowComponent.h"
#include <Components/WindowComponent.hpp>

class CWindowComponentInternalClass final : public UImGui::WindowComponent
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

    virtual void tick(const float deltaTime) override
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


UImGui_CComponentHandle* UImGui_WindowComponent_makeCWindowComponent(const UImGui_ComponentRegularFun construct,
                                                                    const UImGui_ComponentRegularFun begin, const UImGui_ComponentTickFun tick, const UImGui_ComponentRegularFun end,
                                                                    const UImGui_ComponentRegularFun destruct, UImGui_CComponentData data)
{
    auto* handle = dynamic_cast<CWindowComponentInternalClass*>(UImGui::WindowComponent::make<CWindowComponentInternalClass>());
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

const UImGui_CComponentData_P* UImGui_WindowComponent_getCWindowComponentData(const UImGui_CComponentHandle* handle)
{
    return &CAST(const CWindowComponentInternalClass*, handle)->data;
}

void UImGui_WindowComponent_destroyCWindowComponent(const UImGui_CComponentHandle* handle)
{
    delete CAST(const CWindowComponentInternalClass*, handle);
}

UImGui_String UImGui_WindowComponent_getCWindowComponentName(const UImGui_CComponentHandle* handle)
{
    return CAST(const CWindowComponentInternalClass*, handle)->name.c_str();
}