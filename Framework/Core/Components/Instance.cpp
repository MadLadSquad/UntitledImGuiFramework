#include "Instance.hpp"
#include <Core/Global.hpp>

UImGui::Instance::Instance() noexcept
{

}

UImGui::Instance::~Instance() noexcept
{
    initInfo.titlebarComponents.clear();
    initInfo.windowComponents.clear();
    initInfo.inlineComponents.clear();
    // Delete doesn't work with void*
    free(initInfo.globalData);
}

void UImGui::Instance::beginAutohandle() noexcept
{

}

void UImGui::Instance::tickAutohandle(float deltaTime) noexcept
{

}

void UImGui::Instance::endAutohandle() noexcept
{

}

void* UImGui::Instance::getGlobal() noexcept
{
    return internalGlobal.instance->initInfo.globalData;
}

void UImGui::Instance::shutdown() noexcept
{
    internalGlobal.window.close();
}
