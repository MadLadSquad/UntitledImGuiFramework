set(FRAMEWORK_INCLUDE_DIRS "${CMAKE_SOURCE_DIR}/Source/" "${UIMGUI_SRC_PREFIX}/Framework/"
        "${UIMGUI_SRC_PREFIX}/Framework/Core/" "${UIMGUI_SRC_PREFIX}/Framework/ThirdParty/imgui/core/"
        "${UIMGUI_SRC_PREFIX}/Framework/Modules" "." "${UIMGUI_SRC_PREFIX}/Framework/ThirdParty/imgui/backends/"
        "${UIMGUI_SRC_PREFIX}/Framework/Renderer/" "${UIMGUI_SRC_PREFIX}/Framework/ThirdParty/imgui/misc/"
        "${UIMGUI_SRC_PREFIX}/Framework/Window/" "${UIMGUI_SRC_PREFIX}/Framework/ImGui/"
        "${UIMGUI_SRC_PREFIX}/Framework/ThirdParty/imgui/" "${UIMGUI_SRC_PREFIX}/Framework/ThirdParty/logger/src/"
        "${UIMGUI_SRC_PREFIX}/Framework/ThirdParty/source-libraries/" ${GLFW_INCLUDE_DIRS} ${LM_INCLUDE_DIRS}
        "${UIMGUI_SRC_PREFIX}/Framework/Modules/CLIParser/ThirdParty/UntitledCLIParser/ThirdParty/"
        "${UIMGUI_SRC_PREFIX}/Framework/ThirdParty/vulkan-headers/include" "${UIMGUI_SRC_PREFIX}/Framework/ThirdParty/"
        "${UIMGUI_SRC_PREFIX}/Framework/ThirdParty/source-libraries/cimgui/" ${YAML_CPP_INCLUDE_DIRS_T}
        "${UIMGUI_SRC_PREFIX}/Framework/ThirdParty/utfcpp/" "${UIMGUI_SRC_PREFIX}/Framework/ThirdParty/utfcpp/source/"
        ${FREETYPE_INCLUDE_DIRS}
)

if (USE_KNOBS_MODULE)
    list(APPEND FRAMEWORK_INCLUDE_DIRS "${UIMGUI_SRC_PREFIX}/Framework/Modules/Knobs/ThirdParty/imgui-knobs/")
endif ()

if (USE_TOGGLES_MODULE)
    list(APPEND FRAMEWORK_INCLUDE_DIRS "${UIMGUI_SRC_PREFIX}/Framework/Modules/Toggles/ThirdParty/imgui_toggle/")
endif ()

if (USE_SPINNER_MODULE)
    list(APPEND FRAMEWORK_INCLUDE_DIRS "${UIMGUI_SRC_PREFIX}/Framework/Modules/Spinners/ThirdParty/imspinner/")
endif ()

if (USE_PLOTTING_MODULE)
    list(APPEND FRAMEWORK_INCLUDE_DIRS "${UIMGUI_SRC_PREFIX}/Framework/Modules/Plotting/ThirdParty/implot/")
endif ()

setup_opengl_loader_sources()

include_directories(${FRAMEWORK_INCLUDE_DIRS})
if (DEFINED PLUGIN_PREFIX)
    set(FRAMEWORK_INCLUDE_DIRS ${FRAMEWORK_INCLUDE_DIRS} PARENT_SCOPE) # Define once for parent and once for child
endif ()

link_directories("${UIMGUI_SRC_PREFIX}/Framework/ThirdParty/vulkan" "UVKBuildTool/build")

setup_platform_imgui_sources()
if (EMSCRIPTEN)
    file(GLOB_RECURSE IMGUI_SRC
            "${UIMGUI_SRC_PREFIX}/Framework/ThirdParty/imgui/backends/imgui_impl_glfw.cpp"
            "${UIMGUI_SRC_PREFIX}/Framework/ThirdParty/imgui/backends/imgui_impl_opengl3.cpp"
            "${UIMGUI_SRC_PREFIX}/Framework/ThirdParty/imgui/backends/imgui_impl_wgpu.cpp"
            "${UIMGUI_SRC_PREFIX}/Framework/ThirdParty/imgui/misc/freetype/*.cpp"
    )

    file(GLOB_RECURSE IMGUI_HEAD
            "${UIMGUI_SRC_PREFIX}/Framework/ThirdParty/imgui/backends/imgui_impl_glfw.h"
            "${UIMGUI_SRC_PREFIX}/Framework/ThirdParty/imgui/backends/imgui_impl_opengl3.h"
            "${UIMGUI_SRC_PREFIX}/Framework/ThirdParty/imgui/backends/imgui_impl_wgpu.h"
            "${UIMGUI_SRC_PREFIX}/Framework/ThirdParty/imgui/backends/imgui_impl_opengl3_loader.h"
            "${UIMGUI_SRC_PREFIX}/Framework/ThirdParty/imgui/misc/freetype/*.h"
    )
else()
    file(GLOB_RECURSE IMGUI_SRC
            "${UIMGUI_SRC_PREFIX}/Framework/ThirdParty/imgui/backends/imgui_impl_glfw.cpp"
            "${UIMGUI_SRC_PREFIX}/Framework/ThirdParty/imgui/backends/imgui_impl_opengl3.cpp"
            "${UIMGUI_SRC_PREFIX}/Framework/ThirdParty/imgui/backends/imgui_impl_vulkan.cpp"
            "${UIMGUI_SRC_PREFIX}/Framework/ThirdParty/imgui/misc/freetype/*.cpp" ${IMGUI_ADDITIONAL_BACKENDS_SRC}
    )

    file(GLOB_RECURSE IMGUI_HEAD
            "${UIMGUI_SRC_PREFIX}/Framework/ThirdParty/imgui/backends/imgui_impl_glfw.h"
            "${UIMGUI_SRC_PREFIX}/Framework/ThirdParty/imgui/backends/imgui_impl_opengl3.h"
            "${UIMGUI_SRC_PREFIX}/Framework/ThirdParty/imgui/misc/freetype/*.h" ${IMGUI_ADDITIONAL_BACKENDS_HEAD}
            "${UIMGUI_SRC_PREFIX}/Framework/ThirdParty/imgui/backends/imgui_impl_vulkan.h"
            "${UIMGUI_SRC_PREFIX}/Framework/ThirdParty/imgui/backends/imgui_impl_opengl3_loader.h"
    )
endif()

file(GLOB_RECURSE UGUI_SRC
        "${UIMGUI_SRC_PREFIX}/Framework/Core/*.cpp" "${UIMGUI_SRC_PREFIX}/Framework/Renderer/*.cpp"
        "${UIMGUI_SRC_PREFIX}/Framework/ImGui/*.cpp" "${UIMGUI_SRC_PREFIX}/Framework/Window/*.cpp" ${IMGUI_SRC}
        ${GLAD_SRC} ${UIMGUI_CUSTOM_FRAMEWORK_SOURCES} "${UIMGUI_SRC_PREFIX}/Framework/ThirdParty/imgui/core/*.cpp"
        "${UIMGUI_SRC_PREFIX}/Framework/ThirdParty/imgui/misc/cpp/*.cpp" "${UIMGUI_SRC_PREFIX}/Framework/C/*.cpp"
        "${UIMGUI_SRC_PREFIX}/Framework/ThirdParty/logger/*.cpp" "${UIMGUI_SRC_PREFIX}/Framework/Modules/Undo/src/*.cpp"
        "${UIMGUI_SRC_PREFIX}/Framework/Modules/i18n/src/*.cpp" "${UIMGUI_SRC_PREFIX}/Framework/Modules/OS/src/*.cpp"
        "${UIMGUI_SRC_PREFIX}/Framework/ThirdParty/source-libraries/*.cpp"
        "${UIMGUI_SRC_PREFIX}/Framework/Modules/Modules.hpp" "${UIMGUI_SRC_PREFIX}/Framework/Modules/Manager/*.cpp"
)
file(GLOB_RECURSE UGUI_HEAD
        "${UIMGUI_SRC_PREFIX}/Framework/Core/*.hpp" "${UIMGUI_SRC_PREFIX}/Framework/Renderer/*.hpp"
        "${UIMGUI_SRC_PREFIX}/Framework/ImGui/*.hpp" "${UIMGUI_SRC_PREFIX}/Framework/Window/*.hpp" ${IMGUI_HEAD}
        "${UIMGUI_SRC_PREFIX}/Framework/Renderer/*.h" "${UIMGUI_SRC_PREFIX}/Framework/C/*.hpp"
        ${GLAD_HEAD} "${UIMGUI_SRC_PREFIX}/Framework/ThirdParty/imgui/core/*.h" ${UIMGUI_CUSTOM_FRAMEWORK_HEADERS}
        "${UIMGUI_SRC_PREFIX}/Framework/ThirdParty/imgui/core/*.hpp" "${UIMGUI_SRC_PREFIX}/Framework/C/*.h"
        "${UIMGUI_SRC_PREFIX}/Framework/ThirdParty/imgui/misc/cpp/*.h"
        "${UIMGUI_SRC_PREFIX}/Framework/ThirdParty/logger/*.h" "${UIMGUI_SRC_PREFIX}/Framework/ThirdParty/logger/*.hpp"
        "${UIMGUI_SRC_PREFIX}/Framework/ThirdParty/source-libraries/*.h"
        "${UIMGUI_SRC_PREFIX}/Framework/Modules/OS/src/*.h" "${UIMGUI_SRC_PREFIX}/Framework/Modules/i18n/src/*.hpp"
        "${UIMGUI_SRC_PREFIX}/Framework/ThirdParty/source-libraries/*.hpp"
        "${UIMGUI_SRC_PREFIX}/Framework/Modules/Undo/src/*.hpp" "${UIMGUI_SRC_PREFIX}/Framework/Modules/Manager/*.hpp"
        "${UIMGUI_SRC_PREFIX}/Framework/Modules/OS/src/*.hpp" "${UIMGUI_SRC_PREFIX}/Framework/ThirdParty/utfcpp/*.h"
)

file(GLOB_RECURSE UGUI_APP_SRC "Source/*.cpp" "Source/*.c" "${UIMGUI_CUSTOM_APP_SOURCES}")
file(GLOB_RECURSE UGUI_APP_HEAD "Source/*.hpp" "Source/*.h" "Generated/Config.hpp" "${UIMGUI_CUSTOM_APP_HEADERS}")
setup_app_sources()

file(GLOB_RECURSE EXEC_SRC "${UIMGUI_CUSTOM_EXEC_SOURCES}")

# ----------------------------------------------------------------------------------------------------------------------
# ----------------------------------------------- Modify files for modules ---------------------------------------------
# ----------------------------------------------------------------------------------------------------------------------

if (USE_PLOTTING_MODULE)
    file(GLOB_RECURSE UGUI_IMPLOT_SRC "${UIMGUI_SRC_PREFIX}/Framework/Modules/Plotting/*.cpp")
    file(GLOB_RECURSE UGUI_IMPLOT_HEAD "${UIMGUI_SRC_PREFIX}/Framework/Modules/Plotting/*.hpp")
endif()

if (USE_KNOBS_MODULE)
    file(GLOB_RECURSE UGUI_KNOBS_SRC "${UIMGUI_SRC_PREFIX}/Framework/Modules/Knobs/ThirdParty/imgui-knobs/imgui-knobs.cpp")
    file(GLOB_RECURSE UGUI_KNOBS_HEAD "${UIMGUI_SRC_PREFIX}/Framework/Modules/Knobs/ThirdParty/imgui-knobs/imgui-knobs.h")
endif()

if (USE_SPINNER_MODULE)
    file(GLOB_RECURSE UGUI_SPINNER_HEAD "${UIMGUI_SRC_PREFIX}/Framework/Modules/Spinners/*.h")
endif()

if (USE_TOGGLES_MODULE)
    file(GLOB_RECURSE UGUI_TOGGLES_SRC "${UIMGUI_SRC_PREFIX}/Framework/Modules/Toggles/*.cpp")
    file(GLOB_RECURSE UGUI_TOGGLES_HEAD "${UIMGUI_SRC_PREFIX}/Framework/Modules/Toggles/*.h")
endif()

if (USE_TEXT_UTILS_MODULE)
    file(GLOB_RECURSE UGUI_TEXT_UTILS_SRC "${UIMGUI_SRC_PREFIX}/Framework/Modules/TextUtils/*.cpp")

    file(GLOB_RECURSE UGUI_TEXT_UTILS_HEAD "${UIMGUI_SRC_PREFIX}/Framework/Modules/TextUtils/*.hpp"
            "${UIMGUI_SRC_PREFIX}/Framework/Modules/TextUtils/*.h"
    )
endif()

if (USE_THEME_MODULE)
    file(GLOB_RECURSE UTHEME_SRC "${UIMGUI_SRC_PREFIX}/Framework/Modules/Theming/ThirdParty/UntitledImGuiTheme/UTheme.cpp"
            "${UIMGUI_SRC_PREFIX}/Framework/Modules/Theming/ThirdParty/UntitledImGuiTheme/C/CUTheme.cpp"
    )

    file(GLOB_RECURSE UTHEME_HEAD "${UIMGUI_SRC_PREFIX}/Framework/Modules/Theming/ThirdParty/UntitledImGuiTheme/UTheme.hpp"
            "${UIMGUI_SRC_PREFIX}/Framework/Modules/Theming/ThirdParty/UntitledImGuiTheme/C/CUTheme.h"
            "${UIMGUI_SRC_PREFIX}/Framework/Modules/Theming/ThirdParty/UntitledImGuiTheme/Common.h"
    )
endif()

if (USE_I18N_MODULE)
    file(GLOB_RECURSE UI18N_SRC "${UIMGUI_SRC_PREFIX}/Framework/Modules/i18n/src/*.cpp")

    file(GLOB_RECURSE UI18N_HEAD "${UIMGUI_SRC_PREFIX}/Framework/Modules/i18n/src/*.hpp"
            "${UIMGUI_SRC_PREFIX}/Framework/Modules/i18n/src/*.h"
    )
endif()

if (BUILD_MODE_VENDOR)
    foreach(f IN ITEMS ${ENABLED_LIBRARIES})
        get_target_property(INCLUDE_DIRS ${f} INCLUDE_DIRECTORIES)
        list(APPEND LM_INCLUDE_DIRS ${INCLUDE_DIRS})
    endforeach()
endif()

set(LIBRARY_SOURCES
        "${UGUI_SRC}" "${UGUI_HEAD}" "Generated/BuildDef.hpp" "${UGUI_IMPLOT_SRC}" "${UGUI_IMPLOT_HEAD}"
        "${UGUI_TOGGLES_HEAD}" "${UGUI_TOGGLES_SRC}" "${UGUI_SPINNER_HEAD}" "${UGUI_KNOBS_HEAD}" "${UGUI_KNOBS_SRC}"
        "${UGUI_CLI_SRC}" "${UGUI_CLI_HEAD}" "${UGUI_TEXT_UTILS_SRC}" "${UGUI_TEXT_UTILS_HEAD}" "${LM_INCLUDE_DIRS}"
        "${UTHEME_SRC}" "${UTHEME_HEAD}" "${UI18N_SRC}" "${UI18n_HEAD}" "${APPLE_SRC}"
)

set(EXECUTABLE_SOURCES
        "Generated/main.cpp" "${UGUI_HEAD}" "${EXEC_SRC}" "Generated/BuildDef.hpp" "${UGUI_IMPLOT_HEAD}"
        "${UGUI_TOGGLES_HEAD}" "${UGUI_SPINNER_HEAD}" "${UGUI_KNOBS_HEAD}" "${UGUI_CLI_HEAD}" "${UGUI_APP_HEAD}"
        "${UGUI_TEXT_UTILS_HEAD}" "${UTHEME_HEAD}" "${UI18N_HEAD}"
)

set(APP_LIBRARY_SOURCES "${UGUI_APP_SRC}" "${UGUI_APP_HEAD}" "${LM_INCLUDE_DIRS}")
