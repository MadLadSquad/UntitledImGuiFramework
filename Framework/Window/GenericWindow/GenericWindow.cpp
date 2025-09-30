#include "GenericWindow.hpp"
#include <Components/Instance.hpp>

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

#define SAVE_CONFIG_YAML_BASIC(x, y) out << YAML::Key << #x << YAML::Value << windowData.y

void UImGui::GenericWindow::saveSettings(bool bSaveKeybinds) noexcept
{
    auto* instance = Instance::get();
    std::ofstream fout((instance->initInfo.configDir + "Core/Window.yaml").c_str());
    {
        YAML::Emitter out;
        out << YAML::BeginMap;

        SAVE_CONFIG_YAML_BASIC(layout-location, layoutLocation);
        SAVE_CONFIG_YAML_BASIC(load-layout, bLoadLayout);
        SAVE_CONFIG_YAML_BASIC(save-layout, bSaveLayout);
        SAVE_CONFIG_YAML_BASIC(icon, iconLocation);

        out << YAML::Key << "width" << YAML::Value << windowSizeS.x;
        out << YAML::Key << "height" << YAML::Value << windowSizeS.y;

        SAVE_CONFIG_YAML_BASIC(fullscreen, fullscreen);
        SAVE_CONFIG_YAML_BASIC(window-name, name);
        SAVE_CONFIG_YAML_BASIC(resizeable, bResizeable);
        SAVE_CONFIG_YAML_BASIC(transparent-surface, bSurfaceTransparent);
        SAVE_CONFIG_YAML_BASIC(hidden, bHidden);
        SAVE_CONFIG_YAML_BASIC(focusedisplay, bFocused);
        SAVE_CONFIG_YAML_BASIC(size-limits, sizeLimits);
        SAVE_CONFIG_YAML_BASIC(aspect-ratio-size-limit, aspectRatioSizeLimit);
        SAVE_CONFIG_YAML_BASIC(decoratedisplay, bDecorated);
        SAVE_CONFIG_YAML_BASIC(maximisedisplay, bMaximised);

        out << YAML::EndMap;

        fout << out.c_str();
        fout.close();
    }

    if (bSaveKeybinds)
    {
        YAML::Emitter out;
        out << YAML::BeginMap << YAML::Key << "bindings" << YAML::BeginSeq;

        for (auto& a : inputActionList)
        {
            out << YAML::BeginMap << YAML::Key << "key" << YAML::Value << a.name;
            out << YAML::Key << "val" << YAML::Value << YAML::Flow << YAML::BeginSeq;
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
                out << static_cast<int>(f);
            }
            out << YAML::EndSeq;
            out << YAML::EndMap;
        }
        out << YAML::EndSeq << YAML::EndMap;

        fout = std::ofstream((instance->initInfo.configDir + "Core/Keybindings.yaml").c_str());
        fout << out.c_str();
        fout.close();
    }
}

#define OPEN_CONFIG_GET_YAML_BASIC(x, y, z) if (out[#x]) windowData.y = out[#x].as<z>()

void UImGui::GenericWindow::openConfig() noexcept
{
    YAML::Node out;

    const auto* instance = Instance::get();
    try
    {
        out = YAML::LoadFile((instance->initInfo.configDir + "Core/Window.yaml").c_str());
    }
    catch (YAML::BadFile&)
    {
        Logger::log("Couldn't open the Window.yaml config file, please fix this error before shipping for production! Starting with default settings!", ULOG_LOG_TYPE_ERROR);
        goto skip_window_config;
    }

    if (out["width"] && out["height"])
    {
        windowSizeS.x = out["width"].as<float>();
        windowSizeS.y = out["height"].as<float>();
    }

    OPEN_CONFIG_GET_YAML_BASIC(icon, iconLocation, FString);
    OPEN_CONFIG_GET_YAML_BASIC(layout-location, layoutLocation, FString);
    OPEN_CONFIG_GET_YAML_BASIC(load-layout, bLoadLayout, bool);
    OPEN_CONFIG_GET_YAML_BASIC(save-layout, bSaveLayout, bool);
    OPEN_CONFIG_GET_YAML_BASIC(fullscreen, fullscreen, bool);
    OPEN_CONFIG_GET_YAML_BASIC(window-name, name, FString);
    OPEN_CONFIG_GET_YAML_BASIC(resizeable, bResizeable, bool);
    OPEN_CONFIG_GET_YAML_BASIC(transparent-surface, bSurfaceTransparent, bool);
    OPEN_CONFIG_GET_YAML_BASIC(visible, bHidden, bool);
    OPEN_CONFIG_GET_YAML_BASIC(focusedisplay, bFocused, bool);
    OPEN_CONFIG_GET_YAML_BASIC(size-limits, sizeLimits, FVector4);
    OPEN_CONFIG_GET_YAML_BASIC(aspect-ratio-size-limit, aspectRatioSizeLimit, FVector2);
    OPEN_CONFIG_GET_YAML_BASIC(decoratedisplay, bDecorated, bool);
    OPEN_CONFIG_GET_YAML_BASIC(maximisedisplay, bMaximised, bool);
skip_window_config:

    try
    {
        out = YAML::LoadFile((instance->initInfo.configDir + "Core/Keybindings.yaml").c_str());
    }
    catch (YAML::BadFile&)
    {
        Logger::log("Couldn't open the Keybindings.yaml config file, please fix this error before shipping for production! Starting with default settings!", ULOG_LOG_TYPE_ERROR);
        return;
    }

    auto binds = out["bindings"];
    if (binds)
    {
        for (const YAML::Node& a : binds)
        {
            InputAction action;
            action.name = a["key"].as<FString>();
            action.keyCodes = a["val"].as<TVector<uint64_t>>();

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
