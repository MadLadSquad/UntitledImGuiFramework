if (WIN32)
    include(WindowsPlatform)
    initialise_platform()
elseif(APPLE)
    include(ApplePlatform)
    initialise_platform()
else()
    include(UnixPlatform)
    initialise_platform()
endif()

setup_output_path()
include(UImGuiHeader)

include_directories(. ${UIMGUI_PLUGIN_APP_NAME}/Source ${UIMGUI_PLUGIN_APP_NAME}/Generated ${UIMGUI_PLUGIN_APP_NAME}/Framework ${UIMGUI_PLUGIN_APP_NAME}/)

set(OLD_SRC "${CMAKE_SOURCE_DIR}")
set(PLUGIN_PREFIX "${CMAKE_SOURCE_DIR}/${UIMGUI_PLUGIN_APP_NAME}")

add_subdirectory(${UIMGUI_PLUGIN_APP_NAME})

set(CMAKE_SOURCE_DIR "${OLD_SRC}")
include_directories(${FRAMEWORK_INCLUDE_DIRS})