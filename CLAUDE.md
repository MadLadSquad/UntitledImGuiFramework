# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview

UntitledImGuiFramework is a cross-platform desktop application framework built on [dear imgui](https://github.com/ocornut/imgui). It provides an immediate-mode GUI system with a module architecture, plugin support, and both C++ and C APIs. Target platforms: Windows, macOS, Linux, WASM.

## Repository Structure

```
/
├── Framework/          # Core framework source (shared across all projects)
│   ├── Core/           # Instance, Global, types, interfaces, components
│   ├── Renderer/       # OpenGL, Vulkan, WebGPU, and generic renderer backends
│   ├── Window/         # GLFW window backend + generic window abstraction
│   ├── ImGui/          # Dear ImGui integration, client-side bar, extensions
│   ├── Modules/        # Optional feature modules (i18n, theming, plotting, etc.)
│   ├── C/              # C API wrappers for all public-facing C++ APIs
│   └── ThirdParty/     # imgui, glfw, freetype, rapidyaml, vulkan-headers, etc.
├── UVKBuildTool/       # Build & code generation tool (git submodule)
├── Projects/           # Generated projects live here (e.g., UImGuiDemo)
├── Config/             # Template config YAML files copied into new projects
├── Content/            # Template content directory copied into new projects
├── install.sh          # First-time setup: builds UVKBuildTool, creates Projects/
├── create-project.sh   # Scaffold a new application project
├── create-plugin.sh    # Scaffold a new plugin project
├── export.sh           # Package a project for production release
└── update.sh           # Pull latest framework + rebuild UVKBuildTool
```

## Development Workflow

### Initial Setup
```bash
./install.sh            # Builds UVKBuildTool and creates Projects/ directory
```

### Creating a New Project
```bash
./create-project.sh MyApp           # Interactive scaffold + initial build
./create-project.sh MyApp --skip-compilation  # Scaffold only
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
make -j$(nproc)
```

### Regenerating Build Files
After changing `uvproj.yaml` (e.g., enabling/disabling modules), re-run UVKBuildTool:
```bash
cd UVKBuildTool/build
./UVKBuildTool --install ../../Projects/MyApp
```

### Updating the Framework
```bash
./update.sh    # git pull + submodule update + rebuild UVKBuildTool
```

## Architecture

### Component System
Applications are built from three component types that inherit from base classes and implement `begin()`, `tick(float deltaTime)`, and `end()` lifecycle methods:

- **`WindowComponent`** – Renders into a dockable/movable ImGui window
- **`TitlebarComponent`** – Renders into the client-side title bar
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

`begin/tickAutohandle` propagate the lifecycle events down to all registered components.

### Code Generation
UVKBuildTool reads `uvproj.yaml` and generates:
- `Generated/main.cpp` – Application entry point with the `UIMGUI_START` macro
- `Generated/BuildDef.hpp` – `PRODUCTION`/`DEVELOPMENT` build defines
- `Generated/Config.hpp` – Directory macros (`UIMGUI_CONFIG_DIR`, etc.)
- `CMakeLists.txt` – Full build configuration

**Never hand-edit files in `Generated/`** — they are regenerated on each UVKBuildTool run.

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

Runtime module settings (undo max transactions, theme location) live in `Config/Core/Modules.yaml`.

### Configuration Files
All runtime configuration is YAML, located in `Config/Core/`:

- **`Window.yaml`** – Window size, name, icon, fullscreen, decoration, layout file
- **`Renderer.yaml`** – Backend (`opengl`/`vulkan`/`webgpu`/`custom`), v-sync, MSAA, power saving
- **`Modules.yaml`** – Module-specific runtime settings
- **`Keybindings.yaml`** – Input key bindings
- **`DefaultLayout.ini`** / **`FallbackLayout.ini`** – ImGui docking layouts

### Renderer Backends
Set `renderer:` in `Config/Core/Renderer.yaml`. Built-in options: `opengl`, `vulkan`, `webgpu`. For a custom renderer, set `renderer: custom` and assign a `GenericRenderer*` subclass to `initInfo.customRenderer`.

### Interfaces (Static Utility Classes)
All interfaces are static-only (no instances); they wrap internal state:
- `UImGui::Window` – Window management, fullscreen, title, icon, close callbacks
- `UImGui::Renderer` – GPU info, force update, renderer data
- `UImGui::Input` – Key bindings and input device handling
- `UImGui::Plugins` – Plugin loading/unloading at runtime

### C API
`Framework/C/` provides a complete C wrapper (~97% coverage) for all public APIs. Use it for plugins written in languages other than C++, or to expose bindings to scripting languages. The C API requires more heap allocations than the C++ API, so prefer C++ for primary application code.

### Plugin System
Plugins are shared libraries that export `UImGui_Plugin_attach(void* context)` and `UImGui_Plugin_detach()`. Use `create-plugin.sh` to scaffold the boilerplate. Plugins receive the global context pointer via `UImGui::Utility::loadContext(context)`.

## Key Types

Defined in `Framework/Core/Types.hpp` and `Framework/C/CTypes.h`:
- `FString` – `std::string` alias
- `FVector2`, `FVector`, `FVector4` – 2D/3D/4D float vectors
- `TFunction<R(Args...)>` – `std::function` alias
- `TVector<T>` – `std::vector` alias
- `ComponentState` – `RUNNING`, `PAUSED`, `OFF`

## Third-Party Dependencies (Submodules)

All managed as git submodules under `Framework/ThirdParty/` and `Framework/Modules/*/ThirdParty/`:
- **imgui** – MadLadSquad fork of dear imgui
- **glfw** – MadLadSquad fork of GLFW
- **freetype** – Font rendering
- **rapidyaml** – YAML parsing (used for all config files)
- **parallel-hashmap** – High-performance hash maps
- **utfcpp** – UTF-8/16/32 utilities
- **implot**, **imgui-knobs**, **imspinner**, **imgui_toggle** – Widget modules

MinGW is explicitly unsupported (`#error` in `Defines.hpp`).
