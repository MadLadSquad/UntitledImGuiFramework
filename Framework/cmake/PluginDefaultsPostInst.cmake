add_library(${UIMGUI_PLUGIN_NAME} SHARED plugin.cpp)
setup_platform_compilation_plugin()
target_link_libraries(${UIMGUI_PLUGIN_NAME} PUBLIC UntitledImGuiFramework)