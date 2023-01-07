# UntitledImGuiFramework
[![CI](https://github.com/MadLadSquad/UntitledImGuiFramework/actions/workflows/ci.yaml/badge.svg?branch=master)](https://github.com/MadLadSquad/UntitledImGuiFramework/actions/workflows/ci.yaml)
[![MIT license](https://img.shields.io/badge/License-MIT-blue.svg)](https://lbesson.mit-license.org/)
[![trello](https://img.shields.io/badge/Trello-UDE-blue])](https://trello.com/b/HmfuRY2K/untitleddesktop)
[![Discord](https://img.shields.io/discord/717037253292982315.svg?label=&logo=discord&logoColor=ffffff&color=7389D8&labelColor=6A7EC2)](https://discord.gg/4wgH8ZE)

A desktop software development framework that uses Dear imgui as its UI and Rendering library

## Motivation
Desktop UI frameworks and libraries like QT and GTK are bloated, complicated and rigid. [Dear imgui](https://github.com/ocornut/imgui) provides a GUI layer which provides the following benefits:
- Light
- Fast(graphically accelerated)
- Immediate(rendering is done in the source code using function calls)
- Doesn't require config files for layouts or style
- Easy to work with
- Used by a multitude of high profile developers, an incomplete list can be seen [here](https://github.com/ocornut/imgui/wiki/Software-using-dear-imgui)

## Library features
The library is divided into multiple modules compiled statically into your program. Users can fully decide which modules and submodules they want or don't 
want to include in their application. Module list and development status below:
- Core Module ✅
  - Window ✅
  - Core ImGui rendering ✅
  - Textures ✅
  - Renderer submodules ✅
    - OpenGL ✅
    - Vulkan 🚧
- Locale Module ✅
  - Adds localization ✅
  - Adds utilities for accessing the user locale ✅
  - Adds additional utilify functions for localization ✅
- Audio Module 🚧
  - Adds audio playback using [OpenAL](https://www.openal.org/) 🚧
  - Adds an audio player widget 🚧
- Video Module 🚧
  - Adds video playback using [ffmpeg](https://ffmpeg.org/)
  - Adds a video player widget 🚧
- Plotting Module ✅
  - Adds [ImPlot](https://github.com/epezent/implot) for plotting ✅
- Knobs Module ✅
  - Adds [imgui-knobs](https://github.com/altschuler/imgui-knobs) for knob widgets ✅
- Spinner Module ✅
  - Adds [imspinner](https://github.com/dalerank/imspinner) for different spinner widgets ✅
- Toggles Module ✅
  - Adds [imgui_toggle](https://github.com/cmdwtf/imgui_toggle) library for different types of toggle widgets ✅
- Text Utils Module 🚧
  - Adds the [UntitledImGuiTextUtils](https://github.com/MadLadSquad/UntitledImGuiTextUtils) library that adds additional utility functions for 
  easily rendering bold, italic, underlined and other types of text
- Markdown Module 🚧
  - Adds the [UntitledImGuiMDViewerWidget](https://github.com/MadLadSquad/UntitledImGuiMDViewerWidget) library which provides full markdown parsing 
  including of standard extensions
- Undo/Redo Module ✅
  - Adds Undo/Redo operation support ✅
- Networking module 🚧
  - Adds basic networking using [curl](https://curl.se/)
- OS Module for core OS interaction 🚧
  - OS menu and bar interactions 🚧
  - OS accent colours and theme config loading 🚧
  - Notifications 🚧
  - OS system directory configuration 🚧
  - Exec integration using the [UntitledExec](https://github.com/MadLadSquad/UntitledExec) library ✅
  - Cross-platform system font interaction using the [UntitledFontUtils](https://github.com/MadLadSquad/UntitledFontUtils) library ✅
  - Unix: 🚧
    - XDG, [X](http://www.x.org/) and [Wayland](https://wayland.freedesktop.org/) integration 🚧
    - [dbus](https://www.freedesktop.org/wiki/Software/dbus/) integration 🚧
    - [polkit](https://www.freedesktop.org/wiki/Software/PolicyKit/) integration 🚧

The framework uses C++ as its main development language, but because we want to include support for full modability and plugins in mutiple languages, the 
user-facing API has a separate completely C version that can be used to develop applications too! Simply write the required bindings to your language or
generate them automatically from C using a relevant tool, and as long as you have the main engine library compiled you should easily be able to write
applications in C or any other programming language that supports C style functions.

## Learn
You can find the documentation in the [wiki](https://github.com/MadLadSquad/UntitledImGuiFramework/wiki)

Documentation is written as pure learning material, code examples are in most cases provided and are written with both the C and C++ API in mind.
Additionally there is specific documentation for distibuting applications including the framework on different platforms that may be used by OS maintainers
to create packages for the framework

## Showcase and Progress
Coming soon, follow our [youtube channel](https://www.youtube.com/channel/UCWKEvueStyfeMGnkvVJuGxQ) and the 
[UntitledDesktopEnvironment wiki](https://trello.com/b/HmfuRY2K/untitleddesktop) for updates and some feature highlights soon!

There are many applications currently in production using the framework:
1. [UntitledDEPolkitAgent](https://github.com/MadLadSquad/UntitledDEPolkitAgent)
1. [UntitledDESessionLogout](https://github.com/MadLadSquad/UntitledDESessionLogout/)
1. [UntitledImageViewer](https://github.com/MadLadSquad/UntitledImageViewer)
1. [UntitledMarkdownViewer](https://github.com/MadLadSquad/UntitledMarkdownViewer)
1. [UntitledLinuxGameManager](https://github.com/MadLadSquad/UntitledLinuxGameManager)
1. [UntitledTextEditor](https://github.com/MadLadSquad/UntitledTextEditor)
1. [UntitledCalculator](https://github.com/MadLadSquad/UntitledCalculator)

Generally there are many more, but they are going to be developed soon!

The organization trello board can be found [in this trello board](https://trello.com/b/HmfuRY2K/untitleddesktop), it contains organization information 
on all projects releated to UDE. The framework can be found in its corresponding cards
