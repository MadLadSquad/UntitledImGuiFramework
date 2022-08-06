#pragma once
#include <Defines.hpp>
#include <vector>
#include <Components/InlineComponent.hpp>
#include <Components/TitlebarComponent.hpp>
#include <Components/WindowComponent.hpp>
#include <imgui.h>
#include <imgui_internal.h>
#include <Global.hpp>

namespace UImGui
{
    struct UIMGUI_PUBLIC_API InitInfo
    {
        std::vector<InlineComponent*> inlineComponents;
        std::vector<TitlebarComponent*> titlebarComponents;
        std::vector<WindowComponent*> windowComponents;

        // Provide a global data struct to be shared with all components
        void* globalData = nullptr;
    };

    enum ComponentType
    {
        UIMGUI_COMPONENT_TYPE_INLINE,
        UIMGUI_COMPONENT_TYPE_TITLEBAR,
        UIMGUI_COMPONENT_TYPE_WINDOW
    };

    class UIMGUI_PUBLIC_API Instance
    {
    public:
        Instance() noexcept;
        virtual void begin() = 0;
        virtual void tick(float deltaTime) = 0;
        virtual void end() = 0;
        virtual ~Instance() noexcept;

        virtual void onEventConfigureStyle(ImGuiStyle& style, ImGuiIO& io) = 0;
        static void* getGlobal() noexcept;

        template<ComponentType cmpType>
        static auto* getComponentByIDs(const FString& name, uint64_t id)
        {
            if constexpr (cmpType == UIMGUI_COMPONENT_TYPE_INLINE)
            {
                for (auto& a : internalGlobal.instance->initInfo.inlineComponents)
                    if (a->name == name && a->id == id)
                        return a;
            }
            else if constexpr (cmpType == UIMGUI_COMPONENT_TYPE_TITLEBAR)
            {
                for (auto& a : internalGlobal.instance->initInfo.titlebarComponents)
                    if (a->name == name && a->id == id)
                        return a;
            }
            else if constexpr (cmpType == UIMGUI_COMPONENT_TYPE_WINDOW)
            {
                for (auto& a : internalGlobal.instance->initInfo.windowComponents)
                    if (a->name == name && a->id == id)
                        return a;
            }
            else
            {
                logger.consoleLog("Invalid UI component type provided for the getComponentByIDs function!", UVK_LOG_TYPE_ERROR);
                std::terminate();
            }
        }

        template<typename T>
        static T* cast()
        {
            return static_cast<T*>(internalGlobal.instance);
        }

        InitInfo initInfo;

        void beginAutohandle() noexcept;
        void tickAutohandle(float deltaTime) noexcept;
        void endAutohandle() noexcept;
    private:

    };
}