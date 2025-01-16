# UntitledImGuiFramework
[![CI](https://github.com/MadLadSquad/UntitledImGuiFramework/actions/workflows/ci.yaml/badge.svg?branch=master)](https://github.com/MadLadSquad/UntitledImGuiFramework/actions/workflows/ci.yaml)
[![MIT license](https://img.shields.io/badge/License-MIT-blue.svg)](https://lbesson.mit-license.org/)
[![trello](https://img.shields.io/badge/Trello-UDE-blue])](https://trello.com/b/HmfuRY2K/untitleddesktop)
[![Discord](https://img.shields.io/discord/717037253292982315.svg?label=&logo=discord&logoColor=ffffff&color=7389D8&labelColor=6A7EC2)](https://discord.gg/4wgH8ZE)

A desktop software development framework that uses dear imgui as its UI and rendering library.

## NEW: Interactive web demo
You can try out the demo [here](https://uimgui.madladsquad.com).

## Motivation
Building UI using a traditional GUI application framework is hard and tedious. One has to deal with different files and languages for building
out the scaffold, layout, and logic. Most GUI application frameworks are also retained-mode, which introduces bugs with tracking state, especially
when the application you're building is multithreaded.

We also wanted a small and light core, which provides most-minimal features, yet can be extended for large-scale application development. 

Another motivating factor was simply our decision to create our own desktop environment for Freedesktop-based systems, that also had general compatibility
with other operating systems, such as Windows and macOS.

Finally, we wanted to also be able to distribute the core to basically any platform.

[Dear imgui](https://github.com/ocornut/imgui) filled all our requirements. It provides a GUI layer which provides the following benefits:

- Light
- Fast(graphically accelerated)
- Immediate(rendering is done in the source code using function calls)
- Your styling, layout, scaffold and scripting is all in your source code
- Easy to work with
- Used by a multitude of high profile developers, an incomplete list can be seen [here](https://github.com/ocornut/imgui/wiki/Software-using-dear-imgui)

### But the UntitledImGuiFramework provides many of the features that QT and GTK provides, how can you say that it is lighter then them!?
Yes, the framework provides many of the features that can be found in larger toolkits such as QT and GTK. The difference is that the UntitledImGuiFramework
only provides a minimal renderer, component system and some interfaces for things like input out of the box. 

To enable additional features, you need to enable modules, which can be compiled out of your application, as opposed to toolkits like QT and GTK, where many 
of the features that are modules here, are actually part of the core toolkit and cannot be removed. Here is a short list of features that we provide as modules
that other libraries provide as part of their core:

1. System font querying
1. CLI parsing
1. System theme fetching
1. Rich text rendering
1. Undo/Redo
1. URL & default file/folder opening
1. I18N features

## Framework features
The above section says a lot, but let's talk features.

### Interfaces
The framework provides access to many core features through so-called interfaces. Currently we have the following interfaces:

1. Window interface - covers almost all parts of Window management on most platforms and even has additional X11 features
1. Input interface - an easy way to deal with input devices, key bindings and more
1. Renderer interface - gives you access to renderer settings
1. Utility interface - contains many utility functions
1. Plugins interface - allows you to interact with the built-in plugin support

### Modules
The framework is divided into multiple modules compiled statically into your program. Users can fully decide which modules 
and submodules they want or don't want to include in their application. Module list and development status below:

- Core Module ✅
  - Window ✅
  - Core ImGui rendering ✅
  - Textures ✅
  - Renderer subsystems ✅
    - OpenGL ✅
    - Vulkan ✅
    - WebGPU ✅
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

### C & C++ APIs
The framework uses C++ as its main development language. Additionally, because we want to include support for full modability and 
plugins in mutiple languages, the user-facing API has a separate, completely C version that can be used to develop 
applications too!

Simply write the required bindings to your language or generate them automatically from C using a relevant tool. As long as 
you have the main engine library compiled you should easily be able to write applications in C or any other programming 
language that supports C style functions. C and C++ ABI stability of the core is generally guaranteed.

### Native plugin support
The framework has native support for plugins with a handy plugin manager and interface that make it easy to make your application
extensible from both C & C++, as well as other languages through the C & C++ APIs.

### Supported platforms
We currently support the following platforms as official targets:

1. Windows
1. macOS
1. Linux
1. WASM

All of the operating systems above have generally the same features, as we're trying to have a generic platform to build desktop applications with. 

The only exception is the Freedesktop submodule of the OS module, which provides more libraries for working with desktop environment features, that are 
otherwise baked into the core OS libraries, when talking about Windows and macOS.

### And much more
There are countless more small useful features that we could name, here's a short list:

1. Easy texturing
1. Bundled with utilities for dealing with UTF-8/16/32
1. Client-side header bar
1. Comes with a library for logging
1. Comes with a library for working with YAML files
1. Is extensively documented with up-to-date and stable documenation

## Learn
We provide an always up-to-date, stable and extensive documentation, which you can find on the [wiki](https://github.com/MadLadSquad/UntitledImGuiFramework/wiki).

It is written as pure learning material, with code examples using both the C and C++ APIs. Aside from users of the framework,
the documentation also covers topics such as:

1. Shipping the application to production for package maintainers
1. Plugin development examples
1. Developer tips
1. Internal documentation and reference
1. Collaboration tips

## Showcase and Progress
Coming soon, follow the [UntitledDesktopEnvironment webpage](https://madladsquad.com/desktop) for updates 
and some feature highlights.

Try out the new interactive web demo [here](https://uimgui.madladsquad.com/).

There are many applications, already in production, that use the framework. A list can be found 
[here](https://github.com/MadLadSquad/UntitledImGuiFramework/wiki/Applications-using-the-framework). If your application 
uses the framework, please contribute to the list!

The organization trello board can be found [here](https://trello.com/b/HmfuRY2K/untitleddesktop). It
contains organization information on all projects related to UDE. The framework can be found in its corresponding cards.
