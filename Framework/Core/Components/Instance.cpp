#include "Instance.hpp"
#include <Core/Global.hpp>
#include <Interfaces/WindowInterface.hpp>

UImGui::Instance::Instance() noexcept
{
    if (initInfo.cInitInfo != nullptr && initInfo.cInitInfo->constructFuncs != nullptr)
        for (size_t i = 0; i < initInfo.cInitInfo->constructSize; i++)
            initInfo.cInitInfo->constructFuncs[i](initInfo.cInitInfo);
}

UImGui::Instance::~Instance() noexcept
{
    if (initInfo.cInitInfo != nullptr && initInfo.cInitInfo->destructFuncs != nullptr)
        for (size_t i = 0; i < initInfo.cInitInfo->destructSize; i++)
            initInfo.cInitInfo->destructFuncs[i](initInfo.cInitInfo);

    initInfo.titlebarComponents.clear();
    initInfo.windowComponents.clear();
    initInfo.inlineComponents.clear();

    // Delete doesn't work with void*
    if (initInfo.bGlobalAllocatedOnHeap)
        free(initInfo.globalData);
    if (initInfo.cInitInfo != nullptr && initInfo.cInitInfo->bGlobalAllocatedOnHeap)
        free(initInfo.cInitInfo->globalData);

    for (auto& a : Plugins::getPlugins())
        a.detach();
}

void UImGui::Instance::beginAutohandle() const noexcept
{
    if (initInfo.cInitInfo != nullptr && initInfo.cInitInfo->beginFuncs != nullptr)
        for (size_t i = 0; i < initInfo.cInitInfo->beginSize; i++)
            initInfo.cInitInfo->beginFuncs[i](initInfo.cInitInfo);
}

void UImGui::Instance::tickAutohandle(const float deltaTime) const noexcept
{
    if (initInfo.cInitInfo != nullptr && initInfo.cInitInfo->tickFuncs != nullptr)
        for (size_t i = 0; i < initInfo.cInitInfo->tickSize; i++)
            initInfo.cInitInfo->tickFuncs[i](initInfo.cInitInfo, deltaTime);
}

void UImGui::Instance::endAutohandle() const noexcept
{
    if (initInfo.cInitInfo != nullptr && initInfo.cInitInfo->endFuncs != nullptr)
        for (size_t i = 0; i < initInfo.cInitInfo->endSize; i++)
            initInfo.cInitInfo->endFuncs[i](initInfo.cInitInfo);
}

void* UImGui::Instance::getGlobal() noexcept
{
    return get()->initInfo.globalData;
}

void UImGui::Instance::shutdown() noexcept
{
    Window::close();
}

UImGui::Instance* UImGui::Instance::get() noexcept
{
    return Global::get().instance;
}

void UImGui::Instance::reloadApplicationMetadata() noexcept
{
    const auto string = Utility::loadFileToString(initInfo.projectDir + "uvproj.yaml");
    if (string.empty())
    {
        Logger::log("Couldn't open the uvproj.yaml file. Application name, version and other metadata are not available!", ULOG_LOG_TYPE_WARNING);
        return;
    }

    const auto tree = ryml::parse_in_arena(string.c_str());
    if (tree.empty())
    {
        Logger::log("Couldn't parse the uvproj.yaml file. Application name, version and other metadata are not available!", ULOG_LOG_TYPE_WARNING);
        return;
    }

    const auto root = tree.rootref();
    if (keyValid(root["name"]))
        root["name"] >> applicationName;

    if (keyValid(root["version"]))
        root["version"] >> applicationVersion;

    if (keyValid(root["engine-version"]))
        root["engine-version"] >> engineVersion;
}
