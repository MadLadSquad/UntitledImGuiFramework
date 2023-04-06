#include "Instance.hpp"
#include <Core/Global.hpp>
#include <Interfaces/WindowInterface.hpp>

UImGui::Instance::Instance() noexcept
{

}

UImGui::Instance::~Instance() noexcept
{
    initInfo.titlebarComponents.clear();
    initInfo.windowComponents.clear();
    initInfo.inlineComponents.clear();

    // Delete doesn't work with void*
    if (initInfo.bGlobalAllocatedOnHeap)
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
    return Instance::get()->initInfo.globalData;
}

void UImGui::Instance::shutdown() noexcept
{
    Window::get().close();
}

UImGui::Instance* UImGui::Instance::get() noexcept
{
    return internalGlobal.instance;
}
