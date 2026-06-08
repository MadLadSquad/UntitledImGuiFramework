# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview

UntitledImGuiFramework is a cross-platform desktop application framework built on [dear imgui](https://github.com/ocornut/imgui). It provides an immediate-mode GUI system with a module architecture, plugin support, and both C++ and C APIs. Target platforms: Windows, macOS, Linux (X11 + Wayland), WASM.

The framework is maintained by [MadLadSquad](https://madladsquad.com). Comprehensive end-user documentation lives in `docs/` (mirrored from the project wiki) — consult it before guessing at framework conventions.

## Repository Structure

```
/
├── Framework/                  # Core framework source (shared across all projects)
│   ├── Core/                   # Instance, Global, Allocator, FrameworkMain, types, interfaces, components
│   │   ├── Components/         # InlineComponent, WindowComponent, TitlebarComponent, Instance
│   │   ├── Interfaces/         # Input, Layouts, Plugin, Renderer, Window interfaces
│   │   ├── Platform/           # Platform-specific code (e.g. WASM)
│   │   └── Utilities.{cpp,hpp} # Utility interface (loadContext, etc.)
│   ├── Renderer/               # Built-in renderers + abstractions
│   │   ├── GenericRenderer/    # Abstract base for custom renderers + textures
│   │   ├── OpenGL/             # Built-in OpenGL backend
│   │   ├── Vulkan/             # Built-in Vulkan backend
│   │   ├── WebGPU/             # Built-in WebGPU backend (used as the default on WASM in place of Vulkan)
│   │   ├── RendererUtils.{cpp,hpp}  # Helpers for writing custom renderers
│   │   └── Texture.{cpp,hpp}   # User-facing Texture class
│   ├── Window/                 # Window backends
│   │   ├── GenericWindow/      # Abstract base for custom window/monitor backends
│   │   ├── GLFW/               # Built-in GLFW backend (default)
│   │   ├── Window.{cpp,hpp}    # Static Window interface
│   │   └── WindowUtils.{cpp,hpp}
│   ├── ImGui/                  # Dear ImGui integration
│   │   ├── ImGui.{cpp,hpp}     # GUIRenderer — internal imgui lifecycle
│   │   ├── ClientSideBar.*     # Client-side title bar (.mm for macOS)
│   │   └── UImGuiExtensions.*  # Glue between imgui and framework types (FString, etc.)
│   ├── Modules/                # Optional feature modules (controlled by uvproj.yaml)
│   │   ├── Manager/            # ModulesManager + Modules interface
│   │   ├── i18n/, Knobs/, Plotting/, Spinners/, TextUtils/, Theming/, Toggles/, Undo/
│   │   ├── OS/                 # UntitledOpen, UntitledExec, plus Unix-only DBus + XDG submodules
│   │   └── CLIParser/
│   ├── C/                      # C API wrappers (~97% coverage of public C++ APIs)
│   ├── ThirdParty/             # imgui, glfw, freetype, rapidyaml, parallel-hashmap, utfcpp, etc.
│   ├── cmake/                  # CMake helpers
│   └── Framework.hpp           # Umbrella header included by all generated sources
├── UVKBuildTool/               # Build & code generation tool (git submodule)
├── Projects/                   # Generated projects live here (e.g., UImGuiDemo)
├── Config/                     # Template config files copied into new projects
│   ├── Core/                   # Window.yaml, Renderer.yaml, Modules.yaml, Keybindings.yaml, *.ini layouts
│   ├── Translation/            # translation-base.yaml + locale-specific files for i18n
│   ├── WASM/                   # pre.js / post.js for emscripten builds
│   └── cmake/                  # Per-project CMake customisations (`<project>.cmake`)
├── Content/                    # Template content directory copied into new projects
├── docs/                       # End-user docs (mirrored from the GitHub wiki)
├── install.sh                  # First-time setup: builds UVKBuildTool, creates Projects/
├── create-project.sh           # Scaffold a new application project
├── create-plugin.sh            # Scaffold a new plugin project
├── export.sh                   # Package a project for production release
└── update.sh                   # Pull latest framework + rebuild UVKBuildTool
```

Per-project layout (under `Projects/<Name>/`): `Source/`, `Generated/`, `Exported/`, `Config/` and `Content/` symlinks back to the framework, `CMakeLists.txt`, `uvproj.yaml`.

## Development Workflow

### Initial Setup
```bash
./install.sh            # Builds UVKBuildTool and creates Projects/ directory
```

### Creating a New Project
```bash
./create-project.sh MyApp                     # Interactive scaffold + initial build
./create-project.sh MyApp --skip-compilation  # Scaffold only
./create-project.sh MyApp                     # Pass name as arg for headless/CI mode
```

This creates `Projects/MyApp/` with symlinks back to `Framework/` and `UVKBuildTool/`, a `uvproj.yaml` config, and runs UVKBuildTool to generate `CMakeLists.txt` and `Generated/main.cpp`.

### Building a Project
Projects are built with CMake inside `Projects/<Name>/build/`:
```bash
cd Projects/UImGuiDemo/build
cmake .. -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=RELEASE
make -j$(nproc)
```

For WASM:
```bash
emcmake cmake .. -DCMAKE_BUILD_TYPE=RELEASE
emmake make -j$(nproc)
emrun <project name>.html
```

### Regenerating Build Files
After changing `uvproj.yaml` (e.g., enabling/disabling modules, adding plugins, changing install overrides), re-run UVKBuildTool:
```bash
cd UVKBuildTool/build
./UVKBuildTool --install ../../Projects/MyApp     # First-time setup
./UVKBuildTool --generate ../../Projects/MyApp    # Refresh existing project
```

### Generating UI Components
The UVKBuildTool scaffolds component source pairs into `Source/`:
```bash
./UVKBuildTool --inline    <name> <project path>
./UVKBuildTool --window    <name> <project path>
./UVKBuildTool --title-bar <name> <project path>
```

### Production Export
```bash
./UVKBuildTool --build <staging prefix> <prefix> <project path>
# or simply:
./export.sh
```
See `docs/Production-export-and-deployment.md` for install-prefix overrides per platform.

### Updating the Framework
```bash
./update.sh    # git pull + submodule update + rebuild UVKBuildTool
```

## Architecture

### Component System
Applications are built from three component types that inherit from base classes and implement `begin()`, `tick(float deltaTime)`, and `end()` lifecycle methods:

- **`WindowComponent`** – Renders into a dockable/movable ImGui window
- **`TitlebarComponent`** – Renders into the client-side title bar. For portable menu bars, use the `TitlebarBuilder` / `RadioBuilder` fluent API (in `Framework/Core/Components/TitlebarBuilder.{cpp,mm}`) inside the component's `tick` — it renders via dear imgui on Windows/Linux/WASM and registers with the macOS global menu automatically. See `docs/Building-better-titlebar-menus.md`.
- **`InlineComponent`** – Renders inline (not inside an ImGui window)

The **`Instance`** subclass (one per application) owns the component lists and wires them together via the `InitInfo` struct:

```cpp
// Source/Instance.cpp
UImGuiDemo::Instance::Instance() noexcept {
    initInfo = {
        .titlebarComponents = { reinterpret_cast<UImGui::TitlebarComponent*>(&title) },
        .windowComponents   = { reinterpret_cast<UImGui::WindowComponent*>(&demoWindow) },
        UIMGUI_INIT_INFO_DEFAULT_DIRS,
    };
}
```

`Instance::begin/tick/endAutohandle` propagate the lifecycle events down to all registered components. Override `Instance::onEventConfigureStyle(ImGuiStyle&, ImGuiIO&)` to customise imgui style during the `GUI` event.

The `Instance` also stores application metadata loaded from `uvproj.yaml` (`applicationName`, `applicationVersion`, `engineVersion`) and the CLI arguments (`argc`, `argv`, `arguments`). Call `reloadApplicationMetadata()` after manually fixing up `initInfo` directory strings.

### Code Generation
UVKBuildTool reads `uvproj.yaml` and generates:
- `Generated/main.cpp` – Application entry point invoking the `UIMGUI_START` macro
- `Generated/BuildDef.hpp` – `PRODUCTION`/`DEVELOPMENT` build defines
- `Generated/Config.hpp` – Directory macros (`UIMGUI_CONFIG_DIR`, `UIMGUI_CONTENT_DIR`, `UIMGUI_FRAMEWORK_LIBRARY_DIR`, etc.) and the `UIMGUI_INIT_INFO_DEFAULT_DIRS` aggregate-init macro
- `CMakeLists.txt` – Full build configuration

**Never hand-edit files in `Generated/`** — they are regenerated on each UVKBuildTool run. Customise builds via `Config/cmake/<project>.cmake` instead (see "Build Customisation" below).

### Library Layout (Static vs Shared mode)
Controlled by `BUILD_VARIANT_STATIC` (CMake) and `build-mode-static` (uvproj.yaml).

- **Shared, Unix (default)**: 3 binaries — framework library, application library, wrapper executable. Lets the framework be shipped system-wide and lets plugins access application code through the application library.
- **Shared, Windows**: 2 binaries — combined `framework-application` DLL + wrapper executable (MSVC restrictions force the merge; disabling modules at compile time is fine here since the lib isn't intended to be system-wide).
- **Static (any platform)**: everything compiled into a single executable.

`BUILD_VARIANT_VENDOR` / `build-mode-vendor` controls whether bundled third-party libraries are used (`ON`) or system equivalents are searched (`OFF`). Vendored mode is forced on Windows.

### Module System
Modules are controlled in `uvproj.yaml` under `enabled-modules:`. Each boolean flag compiles in or out an optional module:

```yaml
enabled-modules:
  plotting: true    # ImPlot
  knobs: true       # imgui-knobs
  spinners: true    # imspinner
  toggles: true     # imgui_toggle
  text-utils: true  # UntitledImGuiTextUtils
  i18n: false       # UntitledI18N
  theming: false    # UntitledImGuiTheme
  os: false         # UntitledOpen, UntitledExec
  dbus: false       # UntitledDBusUtils (Linux only)
  xdg: false        # UntitledXDGBasedir (Linux only)
  undo-redo: false  # Undo/Redo support
  cli-parser: false # UntitledCLIParser
```

Some modules ("shared modules": OS/Exec, OS/Open, OS/Unix DBus + XDG, CLIParser) are libraries that don't need to be statically compiled into the framework. When `build-mode-vendor: false`, those libraries must be available system-wide.

Runtime module settings live in `Config/Core/Modules.yaml`. The `UImGui::Modules` interface (`data()`, `save()`, `get()`) gives access to runtime-settings booleans that mirror the compile-time flags 1:1 — needed because a system-wide framework lib has *every* module compiled in, but each application chooses which to actually use.

### Configuration Files
All runtime configuration is YAML, located in `Config/Core/`:

- **`Window.yaml`** – Window size, name, icon, fullscreen, decoration, layout file, transparency, resizable, focus, hidden, maximised
- **`Renderer.yaml`** – Backend (`opengl`/`vulkan`/`webgpu`/`custom`), v-sync, MSAA, power saving, idle frame rate, emscripten canvas selector
- **`Modules.yaml`** – Module-specific runtime settings (undo max transactions, theme location, etc.)
- **`Keybindings.yaml`** – Input key bindings
- **`DefaultLayout.ini`** / **`FallbackLayout.ini`** – ImGui docking layouts (do not edit by hand)

The `uvproj.yaml` file in each project additionally controls: metadata (`name`, `version`, `engine-version`), enabled modules, plugins to auto-load (`plugins:` keyed by platform), production export settings (`production:`), install-prefix overrides (`install-override:`), additional install directives (`additional-installs:`), and build mode (`build-mode-static`, `build-mode-vendor`, `system-wide`, `install-framework`).

### Renderer Backends
Set `renderer:` in `Config/Core/Renderer.yaml`. Built-in options: `opengl` (aliases: `gl`, `ogl`, `legacy`), `vulkan` (aliases: `vk`), `webgpu` (aliases: `wgpu`). For a custom renderer, set `renderer: custom` and assign a `GenericRenderer*` subclass to `initInfo.customRenderer` (and optionally `customTexture`).

Custom renderer lifecycle (override on the `GenericRenderer` subclass): `setupWindowIntegration` → `setupPostWindowCreation` → `init` → per-frame `renderStart`/`ImGuiNewFrame`/`ImGuiRenderData`/`renderEnd` → `destroy`. The `parseCustomConfig`/`saveCustomConfig` hooks read/write the `custom-renderer:` block in `Renderer.yaml`.

Additional CMake options unlock more backends for custom renderers:
- `IMGUI_BUILD_WITH_METAL` – macOS-only, links the Metal imgui backend
- `IMGUI_BUILD_WITH_DX11` – Windows-only, DirectX 11
- `IMGUI_BUILD_WITH_DX12` – Windows-only, DirectX 12

Reference custom renderers live in [UImGuiRendererExamples](https://github.com/MadLadSquad/UImGuiRendererExamples) (Metal, DX12, bgfx) and the demo project's `Projects/UImGuiDemo/Source/UImGuiRendererExamples/`.

### Window Backends
Default is GLFW (`Framework/Window/GLFW/`). A custom backend is a `GenericWindow` (+ `GenericMonitor`) subclass assigned to `initInfo.customWindow`. Reference implementation: [UImGuiSDL](https://github.com/MadLadSquad/UImGuiSDL) (SDL3); also vendored at `Projects/UImGuiDemo/Source/UImGuiSDL/` in the demo project.

### Interfaces (Static Utility Classes)
All interfaces are static-only (no instances); they wrap internal state:
- `UImGui::Window` – Window management, title, icon, fullscreen, size, position, monitors, close callbacks. Nested `UImGui::Window::Platform` for platform-specific operations (always-on-top, X11 atoms, etc.)
- `UImGui::Renderer` – `data()` (RendererData ref), `saveSettings()`, GPU info getters (`getVendorString`, `getAPIVersion`, `getGPUName`, `getDriverVersion`), `forceUpdate()` (temporarily disable power-saving)
- `UImGui::Input` – Key bindings and input device handling
- `UImGui::Plugins` – `load()`, `loadStandard()` (reads `plugins:` from `uvproj.yaml`), `getPlugins()`
- `UImGui::Layouts` – Load/save imgui ini layouts (`layoutLocation`, `loadLayout`, `saveLayout`, `getLoadLayout`, `getSaveLayout`)
- `UImGui::Modules` – Runtime module-enable booleans + settings (`data()`, `save()`, `get()`)
- `UImGui::Utility` – `loadContext()` (called first thing by plugins)

### Internal Events & Event Safety
Functions are tagged in code comments with the *earliest* internal event at which they're safe to call:

`Startup` → `Post-startup` → `Begin` → `Post-begin` → `GUI` (style configuration) → `All ready` (tick loop running) → `Pre-destruct` → `Destruct`.

`Any time` means it's safe regardless of the current event. Respect these tags — many getters that return interface state will return uninitialised data if called before `Begin`. The `tick` event lives inside `All ready`.

### C API
`Framework/C/` provides a complete C wrapper (~97% coverage) for all public APIs. Use it for plugins written in languages other than C++, or to expose bindings to scripting languages. The C API requires more heap allocations than the C++ API, so prefer C++ for primary application code.

Conventions: C type names prefix `UImGui_` (e.g. `UImGui_FVector2`, `UImGui_String`, `UImGui_CTexture`). Functions follow `UImGui_<Class>_<method>` (e.g. `UImGui_Window_setTitle`). Memory: handles default to auto-deallocation tracked by `CDeallocationStruct`; pass `bManualDeallocation = true` to opt into explicit `*_release` calls. Use `UImGui_Allocator_allocate`/`_deallocate` instead of raw `malloc`/`free` for plugin-compatible allocations.

### Plugin System
Plugins are shared libraries that export `UImGui_Plugin_attach(void* context)` and `UImGui_Plugin_detach()`. The attach function must first call `UImGui::Utility::loadContext(context)` (or `UImGui_Utility_loadContext`) — its pointer arguments are 1:1 with what the framework passes in. Wrap exports in `extern "C"` and add `__declspec(dllexport)` on Windows.

Use `create-plugin.sh` to scaffold the boilerplate (it'll create the project skeleton under `Projects/<plugin-name>/`). List plugins to auto-load in `uvproj.yaml`:
```yaml
plugins:
  linux:   [myplugin.so]
  macos:   [myplugin.dylib]
  windows: [myplugin.dll]
```
Then call `UImGui::Plugins::loadStandard()` in `Instance::begin()`.

Plugin support is unavailable on WASM (Emscripten requires static linking) and effectively requires the shared-library build variant. Plugins must be recompiled per-platform and may need to match the framework version exactly.

## Memory Management

The framework ships a custom allocator (`UImGui::Allocator`) used to make plugin support on Windows work. Use the framework's custom container typedefs (see "Custom Types" below) instead of raw STL containers when plugin support matters. For simple apps that don't need plugins on Windows, the standard allocator is largely compatible.

## Build Customisation

Per-project CMake customisation goes in `Config/cmake/<project>.cmake` (loaded *before* other CMake scripts).

Useful variables:
- `${APP_LIB_TARGET}` – application library name (Unix; doesn't exist on Windows)
- `${APP_TARGET}` – application executable name
- Framework target: literally `UntitledImGuiFramework`
- `${UIMGUI_CUSTOM_FRAMEWORK_HEADERS}` / `${UIMGUI_CUSTOM_FRAMEWORK_SOURCES}`
- `${UIMGUI_CUSTOM_APP_HEADERS}` / `${UIMGUI_CUSTOM_APP_SOURCES}`
- `${UIMGUI_CUSTOM_EXEC_SOURCES}`

Use the `custom_setup_step` and `custom_compile_step` callbacks for setup that must happen *after* the framework configures itself. The `multicast(<fn> <args>...)` helper applies a CMake function call to all targets that exist on the current platform (handles the missing-app-lib-on-Windows case automatically).

WASM-specific options inside `Config/cmake/<project>.cmake`:
- `set(USE_HTML_GENERATION OFF)` – disable default HTML wrapper
- `set(ENABLE_PRE_SCRIPT ON)` / `set(ENABLE_POST_SCRIPT ON)` – inject `Config/WASM/pre.js` and `post.js`

## Key Types

Defined in `Framework/Core/Types.hpp` and `Framework/C/CTypes.h`:

Primitive vector / string types (C-compatible):
- `FVector2`, `FVector`, `FVector4` – 2D/3D/4D float vectors with YAML conversion specialisations
- `FString` – `std::string`; also `FString8`, `FString16`, `FString32`, `FWString` for the other char widths
- `String` – `const char*` alias

Containers (allocator-aware wrappers; prefer these for plugin-safe code):
- `TVector<T>` – `std::vector`
- `TFunction<R(Args...)>` – `std::function`
- `TQueue`, `TDeque`, `TPriorityQueue`, `TStack`, `TForwardList`, `TList`
- `TMap` (`phmap::btree_map`) / `TSTDMap` (`std::map`) / `TUnorderedMap` (`phmap::parallel_flat_hash_map`) / `TSTDUnorderedMap`
- `TMultimap`, `TSTDMultimap`, `TSTDUnorderedMultimap`
- `TSet` (`phmap::btree_set`) / `TSTDSet` / `TUnorderedSet` (`phmap::parallel_flat_hash_set`) / `TSTDUnorderedSet`
- `TMultiset`, `TSTDMultiset`, `TSTDUnorderedMultiset`

Enums:
- `ComponentState` – `RUNNING`, `PAUSED`, `OFF`
- `ComponentType` – `UIMGUI_COMPONENT_TYPE_INLINE/TITLEBAR/WINDOW`
- `RendererType` – `OPENGL`, `VULKAN_WEBGPU`, `CUSTOM` (+ `COUNT`, `ALT_NAMES_COUNT`)

## Logging

The framework uses [UntitledLog](https://github.com/MadLadSquad/UntitledLog) (`using namespace UVKLog;` is applied by `Types.cpp`). Common helpers:
```cpp
Logger::log("message", ULOG_LOG_TYPE_NOTE, extraArg1, extraArg2);
Logger::setCurrentLogFile("log.txt");
Logger::setLogOperation(UVK_LOG_OPERATION_FILE_AND_TERMINAL);
Logger::setCrashOnError(false);   // call in Instance ctor to disable crash-on-error before renderer start
```
In production builds, the framework crashes on error by default unless `production.crash-on-error: false` is set in `uvproj.yaml`.

## Third-Party Dependencies (Submodules)

All managed as git submodules under `Framework/ThirdParty/` and `Framework/Modules/*/ThirdParty/`:
- **imgui** – MadLadSquad fork of dear imgui (1.92+ dynamic font API, multi-viewports, dynamic textures)
- **glfw** – MadLadSquad fork of GLFW
- **freetype** – Font rendering
- **rapidyaml** – YAML parsing (used for all config files)
- **parallel-hashmap** – High-performance hash maps (powers `TMap`/`TUnorderedMap`)
- **utfcpp** – UTF-8/16/32 utilities for Unicode support
- **UntitledLog** – Logging
- **UntitledRuntimeLibraryLoader (urll)** – Cross-platform `dlopen`-style API (`#include <urll/urll.h>`)
- **implot**, **imgui-knobs**, **imspinner**, **imgui_toggle** – Widget modules
- Module-specific: **UntitledI18N**, **UntitledImGuiTheme**, **UntitledImGuiTextUtils**, **UntitledOpen**, **UntitledExec**, **UntitledCLIParser**, **UntitledDBusUtils**, **UntitledXDGBasedir**

MinGW is explicitly unsupported (`#error` in `Defines.hpp`).

## Platform Notes

- **Windows**: requires Visual Studio / MSVC, Vulkan SDK, GitLFS, and *symlink permissions* (configure via `secpol.msc` → `Create symbolic links`). Static + vendored builds recommended for production unless plugins are needed.
- **macOS**: install GLFW via Homebrew and the Vulkan SDK manually (Homebrew Vulkan is incomplete for local dev but fine for CI). Production distribution requires bundling as a `.app` for anything besides CLI tools. Client-side bar has a dedicated `.mm` Objective-C++ implementation.
- **Linux**: X11 fully supported; Wayland support is partial (most platform-dependent window functions not yet implemented due to GLFW reliance). Many distro packages are needed — see `docs/Install-guide.md` for per-distro lists.
- **WASM**: OS module + submodules disabled, plugins unavailable (Emscripten requires static linking), Vulkan auto-replaced with WebGPU, most window-platform getters and the `Renderer::get*` GPU info functions don't work. The `Renderer.yaml` `emscripten.canvas-selector` *must* match the HTML canvas id — a mismatch silently distorts the view.

## Version Macros

Compile-time framework version checks:
- `UIMGUI_FRAMEWORK_VERSION` – string form
- `UIMGUI_FRAMEWORK_VERSION_NUMERIC` – base-10 integer for `#if` comparisons (`0.9.9.7` → `997`, `1.0.0.0` → `1000`)

Build-mode defines (set by CMake based on the matching `BUILD_VARIANT_*` option):
- `UIMGUI_BUILD_VARIANT_STATIC`
- `UIMGUI_BUILD_VARIANT_VENDOR`

Module presence: each enabled module sets a `UIMGUI_<NAME>_MODULE_ENABLED` define (e.g. `UIMGUI_LOCALE_MODULE_ENABLED`, `UIMGUI_UNDO_MODULE_ENABLED`).
