#include "GenericWindow.hpp"
#include <Components/Instance.hpp>
#include <Utilities.hpp>
#include <Types.hpp>

UImGui::FVector2 UImGui::GenericWindow::getMousePositionChange() noexcept
{
    const FVector2 ret = mouseOffset;
    mouseOffset = { 0.0f, 0.0f };
    return ret;
}

UImGui::FVector2 UImGui::GenericWindow::getCurrentMousePosition() const noexcept
{
    return mousePos;
}

UImGui::FVector2 UImGui::GenericWindow::getLastMousePosition() const noexcept
{
    return mouseLastPos;
}

UImGui::FVector2 UImGui::GenericWindow::getScroll() noexcept
{
    const FVector2 ret = scroll;
    scroll = { 0.0f, 0.0f };
    return ret;
}

#define SAVE_CONFIG_YAML_BASIC(x, y) root[#x] << windowData.y

void UImGui::GenericWindow::saveSettings(bool bSaveKeybinds) noexcept
{
    auto* instance = Instance::get();
    std::ofstream fout((instance->initInfo.configDir + "Core/Window.yaml").c_str());
    {
        ryml::Tree tree;

        ryml::NodeRef root = tree.rootref();
        root |= ryml::MAP;

        SAVE_CONFIG_YAML_BASIC(layout-location, layoutLocation);
        SAVE_CONFIG_YAML_BASIC(load-layout, bLoadLayout);
        SAVE_CONFIG_YAML_BASIC(save-layout, bSaveLayout);
        SAVE_CONFIG_YAML_BASIC(icon, iconLocation);

        // Since we multiply by content scale when creating the window...
        const auto contentScale = getWindowContentScale();
        root["width"] << windowSizeS.x / contentScale.x;
        root["height"] << windowSizeS.y / contentScale.y;

        SAVE_CONFIG_YAML_BASIC(fullscreen, fullscreen);
        SAVE_CONFIG_YAML_BASIC(window-name, name);
        SAVE_CONFIG_YAML_BASIC(resizeable, bResizeable);
        SAVE_CONFIG_YAML_BASIC(transparent-surface, bSurfaceTransparent);
        SAVE_CONFIG_YAML_BASIC(hidden, bHidden);
        SAVE_CONFIG_YAML_BASIC(focused, bFocused);
        SAVE_CONFIG_YAML_BASIC(size-limits, sizeLimits);
        SAVE_CONFIG_YAML_BASIC(aspect-ratio-size-limit, aspectRatioSizeLimit);
        SAVE_CONFIG_YAML_BASIC(decorated, bDecorated);
        SAVE_CONFIG_YAML_BASIC(maximised, bMaximised);

        fout << tree;
        fout.close();
    }

    if (bSaveKeybinds)
    {
        ryml::Tree tree;

        ryml::NodeRef root = tree.rootref();
        root |= ryml::MAP;

        auto bindings = root["bindings"];
        bindings |= ryml::SEQ;

        for (auto& a : inputActionList)
        {
            auto child = bindings.append_child();
            child |= ryml::MAP;
            child["key"] << a.name;

            auto val = child["val"];
            val |= ryml::SEQ | ryml::FLOW_SL;

            for (auto& f : a.keyCodes)
            {
                // Sanitise keys that vary in function between platforms
                // Defines are needed to prevent compilation errors
                switch (f)
                {
#ifdef __APPLE__
                case Keys_LeftControl:
                        f = Keys_LeftControl_InternalRepr;
                        break;
                case Keys_RightControl:
                        f = Keys_RightControl_InternalRepr;
                        break;
                case Keys_LeftControlCmd:
                        f = Keys_LeftControlCommand_InternalRepr;
                        break;
                case Keys_RightControlCmd:
                        f = Keys_RightControlCommand_InternalRepr;
                        break;
#endif
#ifndef __APPLE__
                case Keys_LeftSuper:
                        f = Keys_LeftSuper_InternalRepr;
                        break;
                case Keys_RightSuper:
                        f = Keys_RightSuper_InternalRepr;
                        break;
#endif
                default:
                        break;
                }
                val.append_child() << f;
            }
        }

        fout = std::ofstream((instance->initInfo.configDir + "Core/Keybindings.yaml").c_str());
        fout << tree;
        fout.close();
    }
}

#define OPEN_CONFIG_GET_YAML_BASIC(x, y) if (!root[#x].invalid() && !root[#x].empty()) root[#x] >> windowData.y

void UImGui::GenericWindow::openConfig() noexcept
{
    const auto* instance = Instance::get();
    auto string = Utility::loadFileToString(instance->initInfo.configDir + "Core/Window.yaml");

    c4::yml::Tree tree;
    ryml::NodeRef root;

    if (string.empty())
    {
        Logger::log("Couldn't open the Window.yaml config file, please fix this error before shipping for production! Starting with default settings!", ULOG_LOG_TYPE_ERROR);
        goto skip_window_config;
    }

    tree = ryml::parse_in_arena(string.c_str());
    if (tree.empty())
    {
        Logger::log("Couldn't parse the Window.yaml config file. Please fix this error before shipping for production! Starting with default settings!", ULOG_LOG_TYPE_ERROR);
        goto skip_window_config;
    }
    root = tree.rootref();

    {
        auto width = root["width"];
        auto height = root["height"];

        if (!width.invalid() && !width.empty() && !height.invalid() && !height.empty())
        {
            width >> windowSizeS.x;
            height >> windowSizeS.y;
        }
    }

    OPEN_CONFIG_GET_YAML_BASIC(icon, iconLocation);
    OPEN_CONFIG_GET_YAML_BASIC(layout-location, layoutLocation);
    OPEN_CONFIG_GET_YAML_BASIC(load-layout, bLoadLayout);
    OPEN_CONFIG_GET_YAML_BASIC(save-layout, bSaveLayout);
    OPEN_CONFIG_GET_YAML_BASIC(fullscreen, fullscreen);
    OPEN_CONFIG_GET_YAML_BASIC(window-name, name);
    OPEN_CONFIG_GET_YAML_BASIC(resizeable, bResizeable);
    OPEN_CONFIG_GET_YAML_BASIC(transparent-surface, bSurfaceTransparent);
    OPEN_CONFIG_GET_YAML_BASIC(hidden, bHidden);
    OPEN_CONFIG_GET_YAML_BASIC(focused, bFocused);
    OPEN_CONFIG_GET_YAML_BASIC(size-limits, sizeLimits);
    OPEN_CONFIG_GET_YAML_BASIC(aspect-ratio-size-limit, aspectRatioSizeLimit);
    OPEN_CONFIG_GET_YAML_BASIC(decorated, bDecorated);
    OPEN_CONFIG_GET_YAML_BASIC(maximised, bMaximised);
skip_window_config:

    string = Utility::loadFileToString(instance->initInfo.configDir + "Core/Keybindings.yaml");
    if (string.empty())
    {
        Logger::log("Couldn't open the Keybindings.yaml config file! Please fix this error before shipping for production! Starting with default settings!", ULOG_LOG_TYPE_ERROR);
        return;
    }

    tree = ryml::parse_in_arena(string.c_str());
    if (tree.empty())
    {
        Logger::log("Couldn't parse the Keybindings.yaml config file! Please fix this error before shipping for production! Starting with default settings!", ULOG_LOG_TYPE_ERROR);
        return;
    }
    root = tree.rootref();

    auto binds = root["bindings"];
    if (!binds.invalid() && !binds.empty() && binds.is_seq())
    {
        for (const auto& a : binds.children())
        {
            InputAction action;
            a["key"] >> action.name;
            a["val"] >> action.keyCodes;

            // Sanitise keys that vary in function between platforms
            for (auto& f : action.keyCodes)
            {
                switch (f)
                {
                case Keys_LeftControl_InternalRepr:
                    f = Keys_LeftControl;
                    break;
                case Keys_RightControl_InternalRepr:
                    f = Keys_RightControl;
                    break;
                case Keys_LeftControlCommand_InternalRepr:
                    f = Keys_LeftControlCmd;
                    break;
                case Keys_RightControlCommand_InternalRepr:
                    f = Keys_RightControlCmd;
                    break;
                case Keys_LeftSuper_InternalRepr:
                    f = Keys_LeftSuper;
                    break;
                case Keys_RightSuper_InternalRepr:
                    f = Keys_RightSuper;
                    break;
                default:
                    break;
                }
            }
            inputActionList.push_back(action);
        }
    }
}
