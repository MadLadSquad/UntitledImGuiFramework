if (BUILD_VARIANT_STATIC)
    if (WIN32)
        if (NOT UIMGUI_SKIP_FRAMEWORK)
            add_library(UntitledImGuiFramework STATIC "${LIBRARY_SOURCES}" "${APP_LIBRARY_SOURCES}")
        endif()
        add_executable(${APP_TARGET} ${EXECUTABLE_SOURCES})
    elseif (EMSCRIPTEN)
        add_executable(${APP_TARGET} "${LIBRARY_SOURCES}" "${APP_LIBRARY_SOURCES}" ${EXECUTABLE_SOURCES})
    else ()
        if (NOT UIMGUI_SKIP_FRAMEWORK)
            add_library(UntitledImGuiFramework STATIC "${LIBRARY_SOURCES}")
        endif ()
        add_library(${APP_LIB_TARGET} STATIC ${APP_LIBRARY_SOURCES})
        add_executable(${APP_TARGET} ${EXECUTABLE_SOURCES})
    endif()
else()
    if (WIN32 AND NOT UIMGUI_SKIP_FRAMEWORK)
        add_library(UntitledImGuiFramework SHARED ${LIBRARY_SOURCES} ${APP_LIBRARY_SOURCES})
    else()
        if (NOT UIMGUI_SKIP_FRAMEWORK)
            add_library(UntitledImGuiFramework SHARED ${LIBRARY_SOURCES})
        endif ()
        add_library(${APP_LIB_TARGET} SHARED ${APP_LIBRARY_SOURCES})
    endif()
    add_executable(${APP_TARGET} ${EXECUTABLE_SOURCES})
endif()

include(SetupTargetSettings)

# ----------------------------------------------------------------------------------------------------------------------
# --------------------------------------------- Link to the required libraries -----------------------------------------
# ----------------------------------------------------------------------------------------------------------------------

if (WIN32)
    if (NOT UIMGUI_SKIP_FRAMEWORK)
        target_link_libraries(UntitledImGuiFramework ${GLFW_LIBRARIES_T} ${OPENGL_LIBRARIES_T}
                ${YAML_CPP_LIBRARIES_T} ${FREETYPE_LIBRARIES} ${VULKAN_LIBRARIES_T})
    endif()
    target_link_libraries(${APP_TARGET} UntitledImGuiFramework ${YAML_CPP_LIBRARIES_T})
elseif (EMSCRIPTEN)
    target_link_libraries(${APP_TARGET} ${GLFW_LIBRARIES_T} ${OPENGL_LIBRARIES_T} pthread dl
            ${YAML_CPP_LIBRARIES_T} ${FREETYPE_LIBRARIES} ${VULKAN_LIBRARIES_T} ${X11_LIBRARIES})

    foreach(f IN ITEMS ${ENABLED_LIBRARIES})
        target_link_libraries(${APP_TARGET} ${f})
    endforeach()
else ()
    if (NOT UIMGUI_SKIP_FRAMEWORK)
        target_link_libraries(UntitledImGuiFramework ${GLFW_LIBRARIES_T} ${OPENGL_LIBRARIES_T} pthread
                ${YAML_CPP_LIBRARIES_T} ${FREETYPE_LIBRARIES} ${VULKAN_LIBRARIES_T} ${X11_LIBRARIES} dl util)
    endif()
    target_link_libraries(${APP_LIB_TARGET} UntitledImGuiFramework pthread dl ${YAML_CPP_LIBRARIES_T} util)
    target_link_libraries(${APP_TARGET} UntitledImGuiFramework ${APP_LIB_TARGET} ${YAML_CPP_LIBRARIES_T} dl util)

    if (APPLE AND NOT UIMGUI_SKIP_FRAMEWORK)
        target_link_libraries(UntitledImGuiFramework "-framework Cocoa" "-framework IOKit" "-framework CoreFoundation"
                "-framework QuartzCore")
    endif ()

    foreach(f IN ITEMS ${ENABLED_LIBRARIES})
        target_link_libraries(${APP_LIB_TARGET} ${f})
    endforeach()

    if (USE_OS_MODULE)
        if (ENABLE_DBUS_UTILS)
            if (NOT UIMGUI_SKIP_FRAMEWORK)
                target_link_libraries(UntitledImGuiFramework    ${DBUS_LIBRARIES})
            endif()
            target_link_libraries(${APP_LIB_TARGET}         ${DBUS_LIBRARIES})
        endif()
        if (ENABLE_UFONT_UTILS)
        endif()
    endif()
endif()

if (NOT EMSCRIPTEN AND NOT UIMGUI_SKIP_FRAMEWORK)
    foreach(f IN ITEMS ${ENABLED_LIBRARIES})
        target_link_libraries(UntitledImGuiFramework ${f})
    endforeach()
endif()

configure_file(Framework/cmake/UntitledImGuiFramework.pc.in UntitledImGuiFramework.pc @ONLY)