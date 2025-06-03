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
#include <Renderer/Texture.hpp>
#include <Renderer/ImGui/ClientSideBar.hpp>
#include <urll/urll.h>
#include <Renderer/ImGui/UImGuiExtensions.hpp>

#include <Modules/Modules.hpp>
#include <Core/FrameworkMain.hpp>

#include <ThirdParty/imgui/backends/imgui_impl_opengl3.h>
#ifdef __EMSCRIPTEN__
#include <ThirdParty/imgui/backends/imgui_impl_wgpu.h>
#include <emscripten.h>
#include <emscripten/html5.h>
#include <emscripten/html5_webgpu.h>
#else
#include <ThirdParty/imgui/backends/imgui_impl_vulkan.h>
#endif
#include <GLFW/glfw3.h>
#include <ThirdParty/imgui/backends/imgui_impl_glfw.h>