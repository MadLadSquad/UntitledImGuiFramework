#pragma once
#include <Core.hpp>

#include <Components/InlineComponent.hpp>
#include <Components/WindowComponent.hpp>
#include <Components/TitlebarComponent.hpp>
#include <Components/Instance.hpp>

#include <Interfaces/RendererInterface.hpp>
#include <Interfaces/WindowInterface.hpp>
#include <Interfaces/PluginInterface.hpp>

#include <Core/Utilities.hpp>

#include <C/UImGuiCAPI.h>

#include <imgui.h>
#include <misc/cpp/imgui_stdlib.h>
#include <misc/freetype/imgui_freetype.h>
#include <custom_funcs.hpp>
#include <Renderer/Renderer.hpp>
#include <Renderer/Texture.hpp>
#include <ImGui/ClientSideBar.hpp>
#include <ImGui/UImGuiExtensions.hpp>
#include <Window/Window.hpp>
#include <Window/WindowUtils.hpp>

#include <urll/urll.h>

#include <Modules/Modules.hpp>

#include <Core/FrameworkMain.hpp>

#include <ThirdParty/imgui/backends/imgui_impl_opengl3.h>
#ifdef __EMSCRIPTEN__
    #include <emscripten.h>
    #include <emscripten/html5.h>
#else
    #include <ThirdParty/imgui/backends/imgui_impl_vulkan.h>
#endif