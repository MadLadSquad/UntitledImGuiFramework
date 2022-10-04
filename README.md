# UntitledImGuiFramework
[![CI](https://github.com/MadLadSquad/UntitledImGuiFramework/actions/workflows/ci.yaml/badge.svg?branch=master)](https://github.com/MadLadSquad/UntitledImGuiFramework/actions/workflows/ci.yaml)
[![MIT license](https://img.shields.io/badge/License-MIT-blue.svg)](https://lbesson.mit-license.org/)
[![trello](https://img.shields.io/badge/Trello-UDE-blue])](https://trello.com/b/HmfuRY2K/untitleddesktop)
[![Discord](https://img.shields.io/discord/717037253292982315.svg?label=&logo=discord&logoColor=ffffff&color=7389D8&labelColor=6A7EC2)](https://discord.gg/4wgH8ZE)

A desktop software development framework that uses Dear imgui as its UI and Rendering library

## Motivation
Desktop UI frameworks and libraries like QT and GTK are very bloated, complicated to use and rigid. [Dear imgui](https://github.com/ocornut/imgui) provides a GUI layer which provides the following benefits:
- Light
- Fast(graphically acceletrated)
- Immediate(rendering is done in the source code using function calls)
- Doesn't require config files for layouts or style
- Easy to work with
- Used by a multitude of high profile developers, an incomplete list can be seen [here](https://github.com/ocornut/imgui/wiki/Software-using-dear-imgui)

## Library features
The library is divided into multiple modules compiled statically into your program. Users can fully decide which modules and submodules they want or don't want to include in their application. Module list and development status below:
- Core Module 🚧
  - Window ✅
  - Core ImGui rendering ✅
  - Textures ✅
  - Renderer submodules 🚧 
    - OpenGL ✅
    - Vulkan 🚧
- Locale Module ✅
  - Adds localization as a feature
- Audio Module 🚧
  - Adds audio playback using [OpenAL](https://www.openal.org/)
- Video Module 🚧
  - Adds video playback using [ffmpeg](https://ffmpeg.org/)
- Plotting Module ✅
  - Adds [ImPlot](https://github.com/epezent/implot) for plotting
- Undo/Redo Module ✅
  - Adds Undo/Redo operation support
- Networking module 🚧
  - Adds basic networking using [curl](https://curl.se/)
- OS Module for core OS interaction 🚧
  - OS menu and bar interactions 🚧
  - OS accent colours and theme config loading 🚧
  - Notifications 🚧
  - OS system directory configuration 🚧
  - Dependency and program verification and repair 🚧
  - In-app updates and autoupdates 🚧
  - Native window decorations 🚧
  - Unix: 🚧
    - XDG, [X](http://www.x.org/) and [Wayland](https://wayland.freedesktop.org/) integration
    - [dbus](https://www.freedesktop.org/wiki/Software/dbus/) integration
    - [polkit](https://www.freedesktop.org/wiki/Software/PolicyKit/) integration
    - [fontconfig](https://www.freedesktop.org/wiki/Software/fontconfig/) integration

## Learn
You can find the documentation in the [wiki](https://github.com/MadLadSquad/UntitledImGuiFramework/wiki)

## Showcase and Progress
Coming soon, follow our [youtube channel](https://www.youtube.com/channel/UCWKEvueStyfeMGnkvVJuGxQ) and the 
[UntitledDesktopEnvironment wiki](https://trello.com/b/HmfuRY2K/untitleddesktop) for updates and some feature highlights soon!

The organization board can be found [in this trello board](https://trello.com/b/HmfuRY2K/untitleddesktop), it contains organization information 
on all projects releated to UDE and what features, we have on the list. You can find the framework in its corresponding card
