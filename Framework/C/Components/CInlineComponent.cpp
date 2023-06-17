#include "CInlineComponent.h"
#include <Components/InlineComponent.hpp>

class CInlineComponentInternalClass : public UImGui::InlineComponent
{
public:
    CInlineComponentInternalClass()
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

    virtual ~CInlineComponentInternalClass() override
    {
        destruct(&data);
    }

    UImGui_CComponentData_P data =
    {
        .state = &state,
        .id = &id
    };

    UImGui_ComponentRegularFun construct = [](UImGui_CComponentData_P*) -> void {};
    UImGui_ComponentRegularFun beginF = [](UImGui_CComponentData_P*) -> void {};
    UImGui_ComponentTickFun tickF = [](UImGui_CComponentData_P*, float) -> void {};
    UImGui_ComponentRegularFun endF = [](UImGui_CComponentData_P*) -> void {};
    UImGui_ComponentRegularFun destruct = [](UImGui_CComponentData_P*) -> void {};
};


UImGui_CComponentHandle UImGui_Inline_makeCInlineComponent(UImGui_ComponentRegularFun construct,
                                            UImGui_ComponentRegularFun begin, UImGui_ComponentTickFun tick, UImGui_ComponentRegularFun end,
                                            UImGui_ComponentRegularFun destruct, UImGui_CComponentData data)
{
    auto* handle = (CInlineComponentInternalClass*)UImGui::InlineComponent::make<CInlineComponentInternalClass>();
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

UImGui_CComponentData_P* UImGui_Inline_getCInlineComponentData(UImGui_CComponentHandle handle)
{
    return &static_cast<CInlineComponentInternalClass*>(handle)->data;
}

void UImGui_Inline_destroyCInlineComponent(UImGui_CComponentHandle* handle)
{
    delete (CInlineComponentInternalClass*)handle;
}

UImGui_String UImGui_Inline_getCInlineComponentName(UImGui_CComponentHandle handle)
{
    return static_cast<CInlineComponentInternalClass*>(handle)->name.c_str();
}