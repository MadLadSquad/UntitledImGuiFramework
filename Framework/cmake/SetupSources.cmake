set(FRAMEWORK_INCLUDE_DIRS "${CMAKE_SOURCE_DIR}/Source/" "${CMAKE_SOURCE_DIR}/Framework/"
        "${CMAKE_SOURCE_DIR}/Framework/Core/" "${CMAKE_SOURCE_DIR}/Framework/ThirdParty/imgui/core/"
        "${CMAKE_SOURCE_DIR}/Framework/Modules" "." "${CMAKE_SOURCE_DIR}/Framework/ThirdParty/imgui/backends/"
        "${CMAKE_SOURCE_DIR}/Framework/Renderer/" "${CMAKE_SOURCE_DIR}/Framework/ThirdParty/imgui/misc/"
        "${CMAKE_SOURCE_DIR}/Framework/ThirdParty/imgui/" "${CMAKE_SOURCE_DIR}/Framework/ThirdParty/logger/src/"
        "${CMAKE_SOURCE_DIR}/Framework/ThirdParty/source-libraries/" ${GLFW_INCLUDE_DIRS} ${LM_INCLUDE_DIRS}
        "${CMAKE_SOURCE_DIR}/Framework/Modules/CLIParser/ThirdParty/UntitledCLIParser/ThirdParty/"
        "${CMAKE_SOURCE_DIR}/Framework/ThirdParty/vulkan-headers/include" "${CMAKE_SOURCE_DIR}/Framework/ThirdParty/"
        "${CMAKE_SOURCE_DIR}/Framework/ThirdParty/source-libraries/cimgui/" ${YAML_CPP_INCLUDE_DIRS_T}
        ${FREETYPE_INCLUDE_DIRS})

if (USE_KNOBS_MODULE)
    list(APPEND FRAMEWORK_INCLUDE_DIRS "${CMAKE_SOURCE_DIR}/Framework/Modules/Knobs/ThirdParty/imgui-knobs/")
endif ()

if (USE_TOGGLES_MODULE)
    list(APPEND FRAMEWORK_INCLUDE_DIRS "${CMAKE_SOURCE_DIR}/Framework/Modules/Toggles/ThirdParty/imgui_toggle/")
endif ()

if (USE_SPINNER_MODULE)
    list(APPEND FRAMEWORK_INCLUDE_DIRS "${CMAKE_SOURCE_DIR}/Framework/Modules/Spinners/ThirdParty/imspinner/")
endif ()

if (NOT APPLE)
    list(APPEND FRAMEWORK_INCLUDE_DIRS "${CMAKE_SOURCE_DIR}/Framework/ThirdParty/glad/include/")
    file(GLOB_RECURSE GLAD_SRC "Framework/ThirdParty/glad/src/gl.c")
    file(GLOB_RECURSE GLAD_HEAD "Framework/ThirdParty/glad/include/*.h")
endif()

include_directories(${FRAMEWORK_INCLUDE_DIRS})
if (DEFINED PLUGIN_PREFIX)
    set(FRAMEWORK_INCLUDE_DIRS ${FRAMEWORK_INCLUDE_DIRS} PARENT_SCOPE) # Define once for parent and once for child
endif ()

link_directories("${CMAKE_SOURCE_DIR}/Framework/ThirdParty/vulkan" "UVKBuildTool/build")

if (EMSCRIPTEN)
    file(GLOB_RECURSE IMGUI_SRC "Framework/ThirdParty/imgui/backends/imgui_impl_glfw.cpp"
            "Framework/ThirdParty/imgui/backends/imgui_impl_opengl3.cpp"
            "Framework/ThirdParty/imgui/backends/imgui_impl_wgpu.cpp")

    file(GLOB_RECURSE IMGUI_HEAD "Framework/ThirdParty/imgui/backends/imgui_impl_glfw.h"
            "Framework/ThirdParty/imgui/backends/imgui_impl_opengl3.h"
            "Framework/ThirdParty/imgui/backends/imgui_impl_wgpu.h"
            "Framework/ThirdParty/imgui/backends/imgui_impl_opengl3_loader.h")
else()
    file(GLOB_RECURSE IMGUI_SRC "Framework/ThirdParty/imgui/backends/imgui_impl_glfw.cpp"
            "Framework/ThirdParty/imgui/backends/imgui_impl_opengl3.cpp"
            "Framework/ThirdParty/imgui/backends/imgui_impl_vulkan.cpp"
            "Framework/ThirdParty/imgui/misc/freetype/*.cpp")

    file(GLOB_RECURSE IMGUI_HEAD "Framework/ThirdParty/imgui/backends/imgui_impl_glfw.h"
            "Framework/ThirdParty/imgui/backends/imgui_impl_opengl3.h" "Framework/ThirdParty/imgui/misc/freetype/*.h"
            "Framework/ThirdParty/imgui/backends/imgui_impl_vulkan.h"
            "Framework/ThirdParty/imgui/backends/imgui_impl_opengl3_loader.h")
endif()

file(GLOB_RECURSE UGUI_SRC "Framework/Core/*.cpp" "Framework/Renderer/*.cpp" ${IMGUI_SRC} ${GLAD_SRC}
        "Framework/ThirdParty/imgui/core/*.cpp" "Framework/ThirdParty/imgui/misc/cpp/*.cpp" "Framework/C/*.cpp"
        "Framework/ThirdParty/logger/*.cpp" ${UIMGUI_CUSTOM_FRAMEWORK_SOURCES} "Framework/Modules/i18n/src/*.cpp"
        "Framework/ThirdParty/source-libraries/*.cpp" "Framework/Modules/Modules.hpp" "Framework/Modules/Undo/src/*.cpp"
        "Framework/Modules/Manager/*.cpp" "Framework/Modules/OS/src/*.cpp")
file(GLOB_RECURSE UGUI_HEAD "Framework/Core/*.hpp" "Framework/Renderer/*.hpp" ${IMGUI_HEAD} "Framework/Renderer/*.h"
        "Framework/ThirdParty/imgui/core/*.h" "Framework/ThirdParty/imgui/core/*.hpp" "Framework/C/*.h" ${GLAD_HEAD}
        "Framework/ThirdParty/imgui/misc/cpp/*.h" "Framework/ThirdParty/logger/*.h" "Framework/ThirdParty/logger/*.hpp"
        "Framework/C/*.hpp" ${UIMGUI_CUSTOM_FRAMEWORK_HEADERS} "Framework/ThirdParty/source-libraries/*.h"
        "Framework/Modules/OS/src/*.h" "Framework/ThirdParty/source-libraries/*.hpp" "Framework/Modules/i18n/src/*.hpp"
        "Framework/Modules/Undo/src/*.hpp" "Framework/Modules/Manager/*.hpp" "Framework/Modules/OS/src/*.hpp")

file(GLOB_RECURSE UGUI_APP_SRC "Source/*.cpp" "${UIMGUI_CUSTOM_APP_SOURCES}")
file(GLOB_RECURSE UGUI_APP_HEAD "Source/*.hpp" "Generated/Config.hpp" "${UIMGUI_CUSTOM_APP_HEADERS}")

file(GLOB_RECURSE EXEC_SRC "${UIMGUI_CUSTOM_EXEC_SOURCES}")

if (APPLE)
    file(GLOB_RECURSE APPLE_SRC "Framework/Renderer/*.mm" "Framework/Renderer/*.m")
endif()

# ----------------------------------------------------------------------------------------------------------------------
# ----------------------------------------------- Modify files for modules ---------------------------------------------
# ----------------------------------------------------------------------------------------------------------------------

if (USE_PLOTTING_MODULE)
    file(GLOB_RECURSE UGUI_IMPLOT_SRC "Framework/Modules/Plotting/*.cpp")
    file(GLOB_RECURSE UGUI_IMPLOT_HEAD "Framework/Modules/Plotting/*.hpp")
endif()

if (USE_KNOBS_MODULE)
    file(GLOB_RECURSE UGUI_KNOBS_SRC "Framework/Modules/Knobs/ThirdParty/imgui-knobs/imgui-knobs.cpp")
    file(GLOB_RECURSE UGUI_KNOBS_HEAD "Framework/Modules/Knobs/ThirdParty/imgui-knobs/imgui-knobs.h")
endif()

if (USE_SPINNER_MODULE)
    if (WIN32)
        file(GLOB_RECURSE UGUI_SPINNER_HEAD "Framework/Modules/Spinners/*.h")
    else()
        file(GLOB_RECURSE UGUI_SPINNER_HEAD "Framework/Modules/Spinners/*.h")
    endif()
endif()

if (USE_TOGGLES_MODULE)
    file(GLOB_RECURSE UGUI_TOGGLES_SRC "Framework/Modules/Toggles/*.cpp")
    file(GLOB_RECURSE UGUI_TOGGLES_HEAD "Framework/Modules/Toggles/*.h")
endif()

if (USE_TEXT_UTILS_MODULE)
    file(GLOB_RECURSE UGUI_TEXT_UTILS_SRC "Framework/Modules/TextUtils/*.cpp")
    file(GLOB_RECURSE UGUI_TEXT_UTILS_HEAD "Framework/Modules/TextUtils/*.hpp" "Framework/Modules/TextUtils/*.h")
endif()

if (USE_THEME_MODULE)
    file(GLOB_RECURSE UTHEME_SRC "Framework/Modules/Theming/ThirdParty/UntitledImGuiTheme/UTheme.cpp" "Framework/Modules/Theming/ThirdParty/UntitledImGuiTheme/C/CUTheme.cpp")
    file(GLOB_RECURSE UTHEME_HEAD "Framework/Modules/Theming/ThirdParty/UntitledImGuiTheme/UTheme.hpp"
            "Framework/Modules/Theming/ThirdParty/UntitledImGuiTheme/C/CUTheme.h"
            "Framework/Modules/Theming/ThirdParty/UntitledImGuiTheme/Common.h")
endif()

if (USE_I18N_MODULE)
    file(GLOB_RECURSE UI18N_SRC "Framework/Modules/i18n/src/*.cpp")
    file(GLOB_RECURSE UI18N_HEAD "Framework/Modules/i18n/src/*.hpp" "Framework/Modules/i18n/src/*.h")
endif()

if (BUILD_MODE_VENDOR)
    foreach(f IN ITEMS ${ENABLED_LIBRARIES})
        get_target_property(INCLUDE_DIRS ${f} INCLUDE_DIRECTORIES)
        list(APPEND LM_INCLUDE_DIRS ${INCLUDE_DIRS})
    endforeach()
endif()

set(LIBRARY_SOURCES "${UGUI_SRC}" "${UGUI_HEAD}" "Generated/BuildDef.hpp" "${UGUI_IMPLOT_SRC}" "${UGUI_IMPLOT_HEAD}"
        "${UGUI_TOGGLES_HEAD}" "${UGUI_TOGGLES_SRC}" "${UGUI_SPINNER_HEAD}" "${UGUI_KNOBS_HEAD}" "${UGUI_KNOBS_SRC}"
        "${UGUI_CLI_SRC}" "${UGUI_CLI_HEAD}" "${UGUI_TEXT_UTILS_SRC}" "${UGUI_TEXT_UTILS_HEAD}" "${LM_INCLUDE_DIRS}"
        "${UTHEME_SRC}" "${UTHEME_HEAD}" "${UI18N_SRC}" "${UI18n_HEAD}" "${APPLE_SRC}")
set(EXECUTABLE_SOURCES "Generated/main.cpp" "${UGUI_HEAD}" "${EXEC_SRC}" "Generated/BuildDef.hpp" "${UGUI_IMPLOT_HEAD}"
        "${UGUI_TOGGLES_HEAD}" "${UGUI_SPINNER_HEAD}" "${UGUI_KNOBS_HEAD}" "${UGUI_CLI_HEAD}" "${UGUI_APP_HEAD}"
        "${UGUI_TEXT_UTILS_HEAD}" "${UTHEME_HEAD}" "${UI18N_HEAD}")
set(APP_LIBRARY_SOURCES "${UGUI_APP_SRC}" "${UGUI_APP_HEAD}" "${LM_INCLUDE_DIRS}")
