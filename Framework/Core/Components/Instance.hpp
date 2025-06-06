#pragma once
#include <Defines.hpp>
#include <vector>
#include <Components/InlineComponent.hpp>
#include <Components/TitlebarComponent.hpp>
#include <Components/WindowComponent.hpp>
#include <imgui.h>

// This includes the C API, which contains the C version of the init info struct
#include <C/Components/CInstance.h>
#include <Renderer/GenericRenderer/GenericTexture.hpp>

namespace UImGui
{
    class GenericRenderer;

    /**
     * @brief A struct that defines initialization information for the framework, instantiated automatically in the Instance
     * @var inlineComponents - A list of inline component base class pointers
     * @var titlebarComponents - A list of titlebar component base class pointers
     * @var windowComponents - A list of window component base class pointers
     * @var globalData - A void pointer that points to a global data struct defined by the user to be accessed at whatever
     * location it is needed
     * @var bGlobalAllocatedOnHeap - whether to automatically free the global data if it's heap-allocated
     * @var customRenderer - A pointer to a custom renderer that can later be used by the renderer router if the
     * renderer field in Config/Core/Renderer.yaml is set to "custom"
     * @var cInitInfo - a pointer to the C version of this structure. This allows users of the C API to attach their
     * own components to the init info
     */
    struct UIMGUI_PUBLIC_API InitInfo
    {
        TVector<InlineComponent*> inlineComponents;
        TVector<TitlebarComponent*> titlebarComponents;
        TVector<WindowComponent*> windowComponents;

        // Provide a global data struct to be shared with all components
        void* globalData = nullptr;
        bool bGlobalAllocatedOnHeap = true; // Set this to false if the global is a stack pointer

        GenericRenderer* customRenderer = nullptr;
        GenericTexture* customTexture = nullptr;

        UImGui_CInitInfo* cInitInfo = nullptr;

        FString frameworkLibraryDir = ".";
        FString applicationDir = ".";
        FString applicationLibraryDir = ".";

        FString configDir = "../Config/";
        FString projectDir = "../";

        FString contentDir = "../Content/";

        FString frameworkIncludeDir = "../Framework/";
        FString applicationIncludeDir = "../Source/";
    };

    /**
     * @brief The base application instance class
     * @implements Instance - Constructs the instance, called at the beginning of the autogenerated main.cpp
     * @implements begin - The default begin event as detailed in the docs
     * @implements tick - The default tick event as detailed in the docs
     * @implements end - The default end event as detailed in the docs
     * @implements onEventConfigureStyle - A function called when the style of the different UI widgets needs to be configured
     * @static getGlobal - Returns the global data struct void pointer defined in the init info struct
     * @static getComponentByIDs - Given the name and the numeric ID of a component, as well as its type(a member of the ComponentType) as a template argument it returns a pointer to the given component if found, if not it returns a nullptr and an error
     * @static cast - Given a template parameter of an instance subclass type, it casts the current internal instance pointer to the pointer type provided and returns it
     * @var initInfo - The initInfo struct
     * @implements beginAutohandle - Used to automatically handle downstream begin events
     * @implements tickAutohandle - Used to automatically handle downstream tick events
     * @implements endAutohandle - Used to automatically handle downstream end events
     */
    class UIMGUI_PUBLIC_API Instance
    {
    public:
        Instance() noexcept;
        // Event Safety - All ready
        virtual void begin() = 0;
        // Event Safety - All ready
        virtual void tick(float deltaTime) = 0;
        // Event Safety - Pre-destruct
        virtual void end() = 0;
        virtual ~Instance() noexcept;

        /**
         * @brief A function called at the initialization of the application when the style for the different UI widgets
         * needs to be configured
         * @param style - A reference to the internal ImGuiStyle variable that holds all style data for every ImGui widget
         * @param io - A reference to the internal ImGuiIO variable that holds all IO data for ImGui
         * @note Event Safety - GUI
         */
        virtual void onEventConfigureStyle(ImGuiStyle& style, ImGuiIO& io) = 0;
        /**
         * @brief Returns the global void* defined in the beginInfo struct
         * @note Event Safety - Any time
         */
        static void* getGlobal() noexcept;

        /**
         * @brief Given the IDs below returns a component if it is found in the initInfo's lists or nullptr if it is not found
         * @tparam cmpType - Provides constexpr type information to know for which type of component to search for
         * @param name - The name of the component we're looking for
         * @param id - The numeric ID of the component we're looking for
         * @return A pointer to the component if found, or nullptr. Type depends on the provided ComponentType template parameter enum
         * @note Event Safety - Post-Startup
         */
        template<ComponentType cmpType>
        static auto* getComponentByIDs(const FString& name, const uint64_t id) noexcept
        {
            if constexpr (cmpType == UIMGUI_COMPONENT_TYPE_INLINE)
            {
                for (auto& a : get()->initInfo.inlineComponents)
                    if (a->name == name && a->id == id)
                        return a;
            }
            else if constexpr (cmpType == UIMGUI_COMPONENT_TYPE_TITLEBAR)
            {
                for (auto& a : get()->initInfo.titlebarComponents)
                    if (a->name == name && a->id == id)
                        return a;
            }
            else if constexpr (cmpType == UIMGUI_COMPONENT_TYPE_WINDOW)
            {
                for (auto& a : get()->initInfo.windowComponents)
                    if (a->name == name && a->id == id)
                        return a;
            }
            else
            {
                Logger::log("Invalid UI component type provided for the getComponentByIDs function!", ULOG_LOG_TYPE_ERROR);
                return nullptr;
            }
        }

        /**
         * @brief Casts the active instance struct to a subclass of it
         * @tparam T - The type of the subclass
         * @return The pointer of the active instance cast from Instance* to T*
         * @note Event Safety - Any time
         */
        template<typename T>
        static T* cast() noexcept
        {
            return static_cast<T*>(get());
        }

        /**
         * @brief Provides initialization information for the framework
         */
        InitInfo initInfo;

        /**
         * @brief Used to automatically handle downstream begin events
         * @note Event Safety - Any time
         */
        void beginAutohandle() const noexcept;
        /**
         * @brief Used to automatically handle downstream tick events
         * @param deltaTime - the delta time calculated in the application's render loop
         * @note Event Safety - Any time
         */
        void tickAutohandle(float deltaTime) const noexcept;
        /**
         * @brief Used to automatically handle downstream end events
         * @note Event Safety - Any time
         */
        void endAutohandle() const noexcept;

        /**
         * @brief Closes the application
         * @note Event Safety - Any time
         */
        static void shutdown() noexcept;

        /**
         * @brief CLI arguments for the application
         * @note Event Safety - Any time
         */
        TVector<FString> arguments;

        /**
         * @brief The raw array of CLI arguments passed to the application
         * @note Event Safety - Any time
         */
        char** argv{};
        /**
         * @brief The size of the raw CLI array
         * @note Event Safety - Any time
         */
        int argc{};

        /**
         * @brief The name of the application as defined in the uvproj.yaml file
         * @note Influences the WM_CLASS/Wayland app ID on Linux
         * @note Event Safety - post-construct
         */
        FString applicationName{};

        /**
         * @brief The application version as a string, as defined in the uvproj.yaml file
         * @note Event Safety - post-construct
         */
        FString applicationVersion{};

        /**
         * @brief The engine version as a string, as defined in the uvproj.yaml file. The engine version may refer to
         * the framework version, or to the version of some other base library you're using under the hood
         * @note Event Safety - post-construct
         */
        FString engineVersion{};

        // Event Safety - Any time
        static Instance* get() noexcept;

        // Reopens uvproj.yaml and reads in the application metadata
        // Event Safety - Any time
        void reloadApplicationMetadata() noexcept;
    private:
        friend class GUIRenderer;
        friend class RendererInternal;

        friend class ModulesManager;
        friend class Modules;

        friend class WindowInternal;
    };
}