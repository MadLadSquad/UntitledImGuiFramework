include(GenericPlatform)

macro(setup_pre_dependency_options)
endmacro()

macro(setup_glfw_vendored)
    setup_glfw_vendored_generic(ON)
endmacro()

macro(build_framework_static)
    if (NOT UIMGUI_SKIP_FRAMEWORK)
        add_library(UntitledImGuiFramework STATIC "${LIBRARY_SOURCES}")
    endif ()
    add_library(${APP_LIB_TARGET} STATIC ${APP_LIBRARY_SOURCES})
    add_executable(${APP_TARGET} ${EXECUTABLE_SOURCES})
endmacro()

macro(build_framework_shared)
    if (NOT UIMGUI_SKIP_FRAMEWORK)
        add_library(UntitledImGuiFramework SHARED ${LIBRARY_SOURCES})
    endif ()
    add_library(${APP_LIB_TARGET} SHARED ${APP_LIBRARY_SOURCES})
    add_executable(${APP_TARGET} ${EXECUTABLE_SOURCES})
endmacro()

macro(link_to_framework_libraries_generic_unix)
    if (NOT UIMGUI_SKIP_FRAMEWORK)
        target_link_libraries(UntitledImGuiFramework ${GLFW_LIBRARIES_T} ${OPENGL_LIBRARIES_T} pthread
                ${YAML_LIBRARIES_T} ${FREETYPE_LIBRARIES} ${VULKAN_LIBRARIES_T} ${X11_LIBRARIES} dl util
        )
    endif()
    target_link_libraries(${APP_LIB_TARGET} UntitledImGuiFramework ${YAML_LIBRARIES_T})
    target_link_libraries(${APP_TARGET} UntitledImGuiFramework ${APP_LIB_TARGET})

    foreach(f IN ITEMS ${ENABLED_LIBRARIES})
        target_link_libraries(${APP_LIB_TARGET} ${f})
    endforeach()
endmacro()

macro(setup_platform_compilation_plugin)
    setup_platform_compilation_plugin_generic()
endmacro()

macro(setup_output_path)
endmacro()