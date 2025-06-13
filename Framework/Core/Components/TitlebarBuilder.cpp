#include "TitlebarComponent.hpp"
#include <imgui.h>

#include "Framework/C/Components/CTitlebarComponent.h"

UImGui::TitlebarBuilder& UImGui::TitlebarBuilder::addMenuItem(const FString& label, const FString& hint, const std::function<void(void*)>& f, bool* bEnabled) noexcept
{
    events.emplace_back(label, hint, f, UIMGUI_TITLEBAR_MENU_ITEM_TYPE_MENU_ITEM, 1, bEnabled, nullptr);
    return *this;
}

UImGui::TitlebarBuilder& UImGui::TitlebarBuilder::addSeparator() noexcept
{
    events.emplace_back("", "", [](void*) -> void {}, UIMGUI_TITLEBAR_MENU_ITEM_TYPE_SEPARATOR, 1, nullptr, nullptr);
    return *this;
}

UImGui::TitlebarBuilder& UImGui::TitlebarBuilder::addSubmenu(const FString& label, const TitlebarBuilder& submenu, bool* bEnabled) noexcept
{
    // + 2 for the "begin submenu" and "end submenu" headers
    events.reserve(submenu.events.size() + 2);

    events.emplace_back(label, "", [](void*) -> void{}, UIMGUI_TITLEBAR_MENU_ITEM_TYPE_SUBMENU, submenu.events.size(), bEnabled, nullptr);
    events.insert(events.end(), submenu.events.begin(), submenu.events.end());
    events.emplace_back("", "", [](void*) -> void{}, UIMGUI_TITLEBAR_MENU_ITEM_TYPE_END_SUBMENU, 1, nullptr, nullptr);

    return *this;
}

UImGui::TitlebarBuilder& UImGui::TitlebarBuilder::addCheckbox(const FString& label, bool& bSelected, bool* bEnabled) noexcept
{
    events.emplace_back(label, "", [](void*) -> void {}, UIMGUI_TITLEBAR_MENU_ITEM_TYPE_CHECKBOX, 1, bEnabled, &bSelected);
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

void UImGui::TitlebarBuilder::finish() noexcept
{
#ifdef __APPLE__
    if (bPreferNative)
        macOSFinish();
#endif
}

void UImGui::TitlebarBuilder::render() noexcept
{
#ifdef __APPLE__
    if (bPreferNative)
        ;
    else
    {
#endif
        if (ImGui::BeginMainMenuBar())
        {
            size_t depth = 0;
            int radioCounter = 0;
            int radioValue = -1;
            for (size_t i = 0; i < events.size(); i++)
            {
                const TitlebarMenuItem& a = events[i];

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
                    if (a.bEnabled != nullptr)
                        ImGui::BeginDisabled(!(*a.bEnabled));
                    ImGui::Checkbox(a.label.c_str(), a.bSelected);
                    if (a.bEnabled != nullptr && !(*a.bEnabled))
                        ImGui::EndDisabled();
                    break;
                }
            }
            ImGui::EndMainMenuBar();
        }
#ifdef __APPLE__
    }
#endif
}