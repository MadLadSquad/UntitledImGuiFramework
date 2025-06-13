#include "CInlineComponent.h"
#include <Components/InlineComponent.hpp>

class CInlineComponentInternalClass final : public UImGui::InlineComponent
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


UImGui_CComponentHandle* UImGui_Inline_makeCInlineComponent(const UImGui_ComponentRegularFun construct,
                                                            const UImGui_ComponentRegularFun begin, const UImGui_ComponentTickFun tick, const UImGui_ComponentRegularFun end,
                                                            const UImGui_ComponentRegularFun destruct, const UImGui_CComponentData data)
{
    auto* handle = dynamic_cast<CInlineComponentInternalClass*>(UImGui::InlineComponent::make<CInlineComponentInternalClass>());
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

const UImGui_CComponentData_P* UImGui_Inline_getCInlineComponentData(const UImGui_CComponentHandle* const handle)
{
    return &CAST(const CInlineComponentInternalClass*, handle)->data;
}

void UImGui_Inline_destroyCInlineComponent(const UImGui_CComponentHandle* const handle)
{
    delete CAST(const CInlineComponentInternalClass*, handle);
}

UImGui_String UImGui_Inline_getCInlineComponentName(const UImGui_CComponentHandle* const handle)
{
    return CAST(const CInlineComponentInternalClass*, handle)->name.c_str();
}