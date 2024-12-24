add_library(${UIMGUI_PLUGIN_NAME} SHARED plugin.cpp)
if (NOT WIN32)
    target_link_libraries(${UIMGUI_PLUGIN_NAME} PUBLIC "${UIMGUI_PLUGIN_APP_NAME}Lib")
else()
    target_compile_options(${UIMGUI_PLUGIN_NAME} PRIVATE "/Zc:__cplusplus")
endif ()
target_link_libraries(${UIMGUI_PLUGIN_NAME} PUBLIC UntitledImGuiFramework)