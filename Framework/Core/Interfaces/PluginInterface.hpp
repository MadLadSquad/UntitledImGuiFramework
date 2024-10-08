#pragma once
#include <Types.hpp>
#include <Utilities.hpp>

namespace UImGui
{
    class Global;

    struct UIMGUI_PUBLIC_API PluginContext
    {
        Global* global = nullptr;
        LoggerInternal* loggerContext = nullptr;
        ImGuiContext* imguiContext = nullptr;
        ImGuiMemAllocFunc* allocFunc = nullptr;
        ImGuiMemFreeFunc* freeFunc = nullptr;
        void** userData = nullptr;
        void* implotContext = nullptr;
        void* textUtilsContext = nullptr;
    };

    struct UIMGUI_PUBLIC_API Plugin
    {
        FString name{};
        void* handle = nullptr;

        // 1. Global context pointer
        // 2. Dear imgui context pointer
        // 3. Dear imgui allocate function
        // 4. Dear imgui free function
        // 5. Dear imgui memory user data
        // 6. ImPlot context pointer(if enabled)
        std::function<void(void*)> attach = [](void*) -> void {};
        std::function<void()> detach = []() -> void {};
    };

    class UIMGUI_PUBLIC_API Plugins
    {
    public:
        Plugins() noexcept = default;

        /**
         * @brief Loads a plugin from a location string
         * @param location - the file location for the plugin shared library
         * @note Event safety - post-startup
         * @return A boolean that is true on success and false on error
         */
        static bool load(String location) noexcept;

        /**
         * @note Event safety - post-startup
         * @return A constant reference to an array of strings that represent the list of user-defined plugins, fetched
         * using the standard plugins interface
         */
        static const std::vector<Plugin>& getPlugins() noexcept;

        /**
         * @brief A helper function that automatically loads all plugins that are added by the user through the standard
         * plugins interface
         * @note Event safety - post-startup
         */
        static void loadStandard() noexcept;

        ~Plugins() noexcept;
    private:
        friend class ModulesManager;
        static Plugins& get() noexcept;

        std::vector<Plugin> plugins{};
        std::vector<FString> standardPlugins{};
    };
}