#include "TitlebarComponent.hpp"
#include <imgui.h>

#include "Framework/C/Components/CTitlebarComponent.h"

UImGui::TitlebarBuilder& UImGui::TitlebarBuilder::addMenuItem(const FString& label, const FString& hint, const std::function<void(void*)>& f, bool* bEnabled) noexcept
{
    events.emplace_back(TitlebarMenuItem{
        .label = label,
        .hint = hint,
        .f = f,
        .type = UIMGUI_TITLEBAR_MENU_ITEM_TYPE_MENU_ITEM,
        .membersLen = 1,
        .bEnabled = bEnabled,
        .bSelected = nullptr,
        .size = nullptr,
        .lsize = 0
    });
    return *this;
}

UImGui::TitlebarBuilder& UImGui::TitlebarBuilder::addSeparator() noexcept
{
    events.emplace_back(TitlebarMenuItem{
        .label = "",
        .hint = "",
        .f = [](void*) -> void {},
        .type = UIMGUI_TITLEBAR_MENU_ITEM_TYPE_SEPARATOR,
        .membersLen = 1,
        .bEnabled = nullptr,
        .bSelected = nullptr,
        .size = nullptr,
        .lsize = 0
    });
    return *this;
}

UImGui::TitlebarBuilder& UImGui::TitlebarBuilder::addSubmenu(const FString& label, const TitlebarBuilder& submenu, bool* bEnabled) noexcept
{
    // + 2 for the "begin submenu" and "end submenu" headers
    events.reserve(submenu.events.size() + 2);

    events.emplace_back(TitlebarMenuItem{
        .label = label,
        .hint = "",
        .f = [](void*) -> void {},
        .type = UIMGUI_TITLEBAR_MENU_ITEM_TYPE_SUBMENU,
        .membersLen = submenu.events.size(),
        .bEnabled = bEnabled,
        .bSelected = nullptr,
        .size = nullptr,
        .lsize = 0
    });

    events.insert(events.end(), submenu.events.begin(), submenu.events.end());

    events.emplace_back(TitlebarMenuItem{
        .label = "",
        .hint = "",
        .f = [](void*) -> void {},
        .type = UIMGUI_TITLEBAR_MENU_ITEM_TYPE_END_SUBMENU,
        .membersLen = 1,
        .bEnabled = nullptr,
        .bSelected = nullptr,
        .size = nullptr,
        .lsize = 0
    });
    return *this;
}

UImGui::TitlebarBuilder& UImGui::TitlebarBuilder::addCheckbox(const FString& label, bool& bSelected, bool* bEnabled) noexcept
{
    events.emplace_back(TitlebarMenuItem{
        .label = label,
        .hint = "",
        .f = [](void*) -> void {},
        .type = UIMGUI_TITLEBAR_MENU_ITEM_TYPE_CHECKBOX,
        .membersLen = 1,
        .bEnabled = bEnabled,
        .bSelected = &bSelected,
        .size = nullptr,
        .lsize = 0
    });
    return *this;
}

UImGui::TitlebarBuilder& UImGui::TitlebarBuilder::setBuildNativeOnMacOS(const bool bBuildNativeOnMacOS) noexcept
{
    bPreferNative = bBuildNativeOnMacOS;
    return *this;
}

UImGui::TitlebarBuilder& UImGui::TitlebarBuilder::setContext(void* data) noexcept
{
    this->data = data;
    return *this;
}

UImGui::RadioBuilder::RadioBuilder(int& selectedIndex) noexcept
{
    init(selectedIndex);
}

UImGui::RadioBuilder& UImGui::RadioBuilder::init(int& selectedIndex) noexcept
{
    currentEnabledIndex = &selectedIndex;
    currentEnabledIndexLong = currentEnabledIndex == nullptr ? 0 : *currentEnabledIndex;
    return *this;
}

UImGui::RadioBuilder& UImGui::RadioBuilder::add(const FString& label, bool* bEnabled)
{
    events.emplace_back(TitlebarMenuItem{
        .label = label,
        .hint = "",
        .f = [](void*) -> void {},
        .type = UIMGUI_TITLEBAR_MENU_ITEM_TYPE_RADIO_BUTTON,
        .membersLen = 1,
        .bEnabled = bEnabled,
        .bSelected = nullptr,
        .size = currentEnabledIndex,
        .lsize = currentEnabledIndexLong
    });
    return *this;
}

UImGui::TitlebarBuilder& UImGui::TitlebarBuilder::addRadioGroup(const UImGui::RadioBuilder& submenu) noexcept
{
    events.reserve(submenu.events.size() + 2);

    events.emplace_back(TitlebarMenuItem{
        .label = "",
        .hint = "",
        .f = [](void*) -> void {},
        .type = UIMGUI_TITLEBAR_MENU_ITEM_TYPE_BEGIN_RADIO,
        .membersLen = submenu.events.size(),
        .bEnabled = nullptr,
        .bSelected = nullptr,
        .size = submenu.currentEnabledIndex,
        .lsize = submenu.currentEnabledIndexLong
    });

    events.insert(events.end(), submenu.events.begin(), submenu.events.end());

    events.emplace_back(TitlebarMenuItem{
        .label = "",
        .hint = "",
        .f = [](void*) -> void {},
        .type = UIMGUI_TITLEBAR_MENU_ITEM_TYPE_END_RADIO,
        .membersLen = 1,
        .bEnabled = nullptr,
        .bSelected = nullptr,
        .size = nullptr,
        .lsize = submenu.currentEnabledIndexLong
    });

    return *this;
}

#ifndef __APPLE__
UImGui::TitlebarBuilder& UImGui::TitlebarBuilder::addAppMenuDefaultItems() noexcept
{
    return *this;
}

UImGui::TitlebarBuilder& UImGui::TitlebarBuilder::addWindowMenuDefaultItems() noexcept
{
    return *this;
}

UImGui::TitlebarBuilder& UImGui::TitlebarBuilder::addHelpMenuDefaultItems() noexcept
{
    return *this;
}

UImGui::TitlebarBuilder& UImGui::TitlebarBuilder::addEditMenuDefaultItems() noexcept
{
    return *this;
}
#endif

void UImGui::TitlebarBuilder::finish() noexcept
{
#ifdef __APPLE__
    if (bPreferNative)
        macOSFinish();
#endif
}

void UImGui::TitlebarBuilder::renderFull() const noexcept
{
#ifdef __APPLE__
    if (bPreferNative)
        return;
#endif
    if (ImGui::BeginMainMenuBar())
    {
        renderInline();
        ImGui::EndMainMenuBar();
    }
}

void UImGui::TitlebarBuilder::renderInline() const noexcept
{
#ifdef __APPLE__
    if (bPreferNative)
        return;
#endif
    size_t depth = 0;
    for (size_t i = 0; i < events.size(); i++)
    {
        const TitlebarMenuItem& a = events[i];
        int radioBegin = 0;

        switch (a.type)
        {
        case UIMGUI_TITLEBAR_MENU_ITEM_TYPE_MENU_ITEM:
            if (ImGui::MenuItem(a.label.c_str(), depth == 0 ? "" : a.hint.c_str(), false, a.bEnabled == nullptr ? true : *a.bEnabled))
                a.f(data);
            break;
        case UIMGUI_TITLEBAR_MENU_ITEM_TYPE_SUBMENU:
            if (ImGui::BeginMenu(a.label.c_str(), a.bEnabled == nullptr ? true : *a.bEnabled))
                depth++;
            else
                i += a.membersLen + 1;
            break;
        case UIMGUI_TITLEBAR_MENU_ITEM_TYPE_END_SUBMENU:
            depth--;
            ImGui::EndMenu();
            break;
        case UIMGUI_TITLEBAR_MENU_ITEM_TYPE_SEPARATOR:
            ImGui::Separator();
            break;
        case UIMGUI_TITLEBAR_MENU_ITEM_TYPE_CHECKBOX:
            if (a.bSelected == nullptr)
            {
                Logger::log("A checkbox with the following label is null, not rendering: ", ULOG_LOG_TYPE_ERROR, a.label.c_str());
                break;
            }
            if (a.bEnabled != nullptr && !(*a.bEnabled))
                ImGui::BeginDisabled();
            ImGui::Checkbox(a.label.c_str(), a.bSelected);
            if (a.bEnabled != nullptr && !(*a.bEnabled))
                ImGui::EndDisabled();
            break;
        case UIMGUI_TITLEBAR_MENU_ITEM_TYPE_BEGIN_RADIO:
            if (a.size == nullptr)
            {
                i += a.membersLen + 1;
                Logger::log("A radio button was submitted with a NULL index.\n"
                                    "Make sure to always initialise your radio button with UImGui::RadioBuilder::init()!"
                                    "Not rendering!", ULOG_LOG_TYPE_ERROR);
            }
            else
                radioBegin = CAST(int, i) + 1;
            break;
        case UIMGUI_TITLEBAR_MENU_ITEM_TYPE_RADIO_BUTTON:
            if (a.bEnabled != nullptr && !(*a.bEnabled))
                ImGui::BeginDisabled();
            ImGui::RadioButton(a.label.c_str(), a.size, CAST(int, i) - radioBegin);
            if (a.bEnabled != nullptr && !(*a.bEnabled))
                ImGui::EndDisabled();
            break;
        case UIMGUI_TITLEBAR_MENU_ITEM_TYPE_END_RADIO:
            radioBegin = 0;
            break;
        default:
            break;
        }
    }
}

void UImGui::TitlebarBuilder::clear() noexcept
{
    events.clear();
}
