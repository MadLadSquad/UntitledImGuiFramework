# UntitledImGuiFramework
A desktop software framework that uses Dear imgui as its UI and Rendering libraries
## Motivation
Desktop UI frameworks and libraries like QT and GTK are very bloated, complicated to use and rigid. [Dear imgui](https://github.com/ocornut/imgui) provides a GUI layer which provides the following benefits:
- Light
- Fast(graphically acceletrated)
- Immediate(rendering is done in the source code using function calls)
- Doesn't require config files for layouts or style
- Easy to work with
## Library features
The library is divided into multiple modules compiled as seperate shared libraries
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
  - Adds basic networking using [curl]()
- OS Module for core OS interaction
  - OS menu and bar interactions
  - OS accent colours and theme config loading
  - Notifications
  - OS system directory configuration
  - Dependency and program verification and repair
  - In-app updates and autoupdates
  - Native window decorations
## Learn
You can find the documentation in the [wiki](https://github.com/MadLadSquad/UntitledImGuiFramework/wiki)
## Showcase and Progress
Coming soon, follow our [youtube channel](https://www.youtube.com/channel/UCWKEvueStyfeMGnkvVJuGxQ) and the [UntitledDesktopEnvironment wiki](https://trello.com/b/HmfuRY2K/untitleddesktop) for updates and some feature highlights soon!