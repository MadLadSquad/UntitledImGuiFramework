#include <Interfaces/Input.hpp>
#include <Interfaces/WindowInterface.hpp>

bool UImGui::InputAction::operator==(const CKeyState& st) const noexcept
{
    return state == st;
}

bool UImGui::InputAction::operator!=(const CKeyState& st) const noexcept
{
    return state != st;
}

CKeyState UImGui::Input::getKey(const CKeys key) noexcept
{
    return Window::get()->getKey(key);
}

const UImGui::InputAction& UImGui::Input::getAction(const FString& name) noexcept
{
    for (auto& a : Window::get()->inputActionList)
        if (a.name == name)
            return a;

    Logger::log("Input action with name: ", ULOG_LOG_TYPE_ERROR, name, ", does not exist!");
    static InputAction empty{};
    return empty;
}

UImGui::TVector<UImGui::InputAction>& UImGui::Input::getActions() noexcept
{
    return Window::get()->inputActionList;
}

UImGui::FVector2 UImGui::Input::getMousePositionChange() noexcept
{
    return Window::get()->getMousePositionChange();
}

UImGui::FVector2 UImGui::Input::getCurrentMousePosition() noexcept
{
    return Window::get()->getCurrentMousePosition();
}

UImGui::FVector2 UImGui::Input::getLastMousePosition() noexcept
{
    return Window::get()->getLastMousePosition();
}

UImGui::FVector2 UImGui::Input::getScroll() noexcept
{
    return Window::get()->getScroll();
}

void UImGui::Input::setCursorVisibility(const CursorVisibilityState visibility) noexcept
{
    Window::get()->setCursorVisibility(visibility);
}

void UImGui::Input::setRawMouseMotion(const bool bEnable) noexcept
{
    Window::get()->setRawMouseMotion(bEnable);
}

bool UImGui::Input::getRawMouseMotion() noexcept
{
    return Window::get()->getRawMouseMotion();
}