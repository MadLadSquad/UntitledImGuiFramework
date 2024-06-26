# UntitledImGuiFramework
[![CI](https://github.com/MadLadSquad/UntitledImGuiFramework/actions/workflows/ci.yaml/badge.svg?branch=master)](https://github.com/MadLadSquad/UntitledImGuiFramework/actions/workflows/ci.yaml)
[![MIT license](https://img.shields.io/badge/License-MIT-blue.svg)](https://lbesson.mit-license.org/)
[![trello](https://img.shields.io/badge/Trello-UDE-blue])](https://trello.com/b/HmfuRY2K/untitleddesktop)
[![Discord](https://img.shields.io/discord/717037253292982315.svg?label=&logo=discord&logoColor=ffffff&color=7389D8&labelColor=6A7EC2)](https://discord.gg/4wgH8ZE)

A desktop software development framework that uses dear imgui as its UI and rendering library.

## Motivation
Desktop UI frameworks and libraries like QT and GTK are complicated and really rigid. Using them or system-specific UI libraries
would hard-lock us into using only what they use. 

We also wanted a small and light core, which provides most-minimal features. We also wanted good developer experience, as 
QT and GTK seemed overengineered to us. [Dear imgui](https://github.com/ocornut/imgui) filled all our requirements.

[Dear imgui](https://github.com/ocornut/imgui) provides a GUI layer which provides the following benefits:

- Light
- Fast(graphically accelerated)
- Immediate(rendering is done in the source code using function calls)
- Doesn't require config files for layouts or style \*
- Easy to work with
- Used by a multitude of high profile developers, an incomplete list can be seen [here](https://github.com/ocornut/imgui/wiki/Software-using-dear-imgui)

\* It depends on 1 for window management and compositing but it is small, autogenerated and is mainly used to save window 
coordinates for the next user session.

## Library features
The library is divided into multiple modules compiled statically into your program. Users can fully decide which modules 
and submodules they want or don't want to include in their application. Module list and development status below:

- Core Module ✅
  - Window ✅
  - Core ImGui rendering ✅
  - Textures ✅
  - Renderer submodules ✅
    - OpenGL ✅
    - Vulkan 🚧
- I18N module ✅
  - Adds the [UntitledI18N](https://github.com/MadLadSquad/UntitledI18N) library for internationalisation support
- Plotting Module ✅
  - Adds [ImPlot](https://github.com/epezent/implot) for plotting ✅
- Knobs Module ✅
  - Adds [imgui-knobs](https://github.com/altschuler/imgui-knobs) for knob widgets ✅
- Spinner Module ✅
  - Adds [imspinner](https://github.com/dalerank/imspinner) for different spinner widgets ✅
- Toggles Module ✅
  - Adds [imgui_toggle](https://github.com/cmdwtf/imgui_toggle) library for different types of toggle widgets ✅
- Text Utils Module ✅
  - Adds the [UntitledImGuiTextUtils](https://github.com/MadLadSquad/UntitledImGuiTextUtils) library that adds additional utility 
functions for easily rendering bold, italic, underlined and other types of text
- Undo/Redo Module ✅
  - Adds Undo/Redo operation support ✅
- CLI Args module ✅
  - Adds a parser for CLI arguments using the [UntitledCLIParser](https://github.com/MadLadSquad/UntitledCLIParser)
- Theming module ✅
  - Adds the [UntitledImGuiTheme](https://github.com/MadLadSquad/UntitledImGuiTheme) library for reading and writing themes ✅
- OS Module for core OS interaction
  - URL and file/folder opener with default application using the [UntitledOpen](https://github.com/MadLadSquad/UntitledOpen) library ✅
  - Exec integration using the [UntitledExec](https://github.com/MadLadSquad/UntitledExec) library ✅
  - Cross-platform system font querying using the [UntitledFontUtils](https://github.com/MadLadSquad/UntitledFontUtils) library ✅
  - Freedesktop: ✅
    - [XDG Basedir](https://specifications.freedesktop.org/basedir-spec/basedir-spec-latest.html) integration ✅
    - [dbus](https://www.freedesktop.org/wiki/Software/dbus/) integration ✅

The framework uses C++ as its main development language. Additionally, because we want to include support for full modability and 
plugins in mutiple languages, the user-facing API has a separate, completely C version that can be used to develop 
applications too!

Simply write the required bindings to your language or generate them automatically from C using a relevant tool. As long as 
you have the main engine library compiled you should easily be able to write applications in C or any other programming 
language that supports C style functions. C and C++ ABI stability of the core is generally guaranteed.

## Supported platforms
We currently support the following platforms as official targets:

1. Windows
1. macOS
1. Linux
1. WASM

All of the operating systems above have generally the same features, as we're trying to have a generic platform to build desktop applications with. 

The only exception is the Freedesktop submodule of the OS module, which provides more libraries for working with desktop environment features, that are 
otherwise baked into the core OS libraries, when talking about Windows and macOS.

### Future platform support
For the 2.0 release of the framework, we plan to have first class support for the following additional platforms:

1. Android
1. iOS

## Learn
You can find the documentation in the [wiki](https://github.com/MadLadSquad/UntitledImGuiFramework/wiki).

Documentation is written as pure learning material, code examples are, in most cases, provided and are written with both 
the C and C++ API in mind. Additionally, there is specific documentation for distibuting applications including the 
framework on different platforms that may be used by OS maintainers to create packages for the framework.

## Showcase and Progress
Coming soon, follow our [YouTube channel](https://www.youtube.com/channel/UCWKEvueStyfeMGnkvVJuGxQ) and the 
[UntitledDesktopEnvironment wiki](https://trello.com/b/HmfuRY2K/untitleddesktop) for updates and some feature highlights 
soon!

There are many applications, already in production, that use the framework. A list can be found 
[here](https://github.com/MadLadSquad/UntitledImGuiFramework/wiki/Applications-using-the-framework). If your application 
uses the framework, please contribute to the list!

The organization trello board can be found [here](https://trello.com/b/HmfuRY2K/untitleddesktop). It
contains organization information on all projects related to UDE. The framework can be found in its corresponding cards.

