if (BUILD_VARIANT_STATIC)
    if (WIN32)
        add_library(UntitledImGuiFramework STATIC "${LIBRARY_SOURCES}" "${APP_LIBRARY_SOURCES}")
    else()
        add_library(UntitledImGuiFramework STATIC "${LIBRARY_SOURCES}")
        add_library(${APP_LIB_TARGET} STATIC ${APP_LIBRARY_SOURCES})
    endif()
    add_executable(${APP_TARGET} ${EXECUTABLE_SOURCES})
else()
    if (WIN32)
        add_library(UntitledImGuiFramework SHARED ${LIBRARY_SOURCES} ${APP_LIBRARY_SOURCES})
    else()
        add_library(UntitledImGuiFramework SHARED ${LIBRARY_SOURCES})
        add_library(${APP_LIB_TARGET} SHARED ${APP_LIBRARY_SOURCES})
    endif()
    add_executable(${APP_TARGET} ${EXECUTABLE_SOURCES})
endif()

include(SetupTargetSettings)

# ----------------------------------------------------------------------------------------------------------------------
# --------------------------------------------- Link to the required libraries -----------------------------------------
# ----------------------------------------------------------------------------------------------------------------------

if (WIN32)
    target_link_libraries(UntitledImGuiFramework ${GLFW_LIBRARIES_T} ${GLEW_LIBRARIES_T} ${OPENGL_LIBRARIES_T}
            ${YAML_CPP_LIBRARIES_T} ${FREETYPE_LIBRARIES} ${VULKAN_LIBRARIES_T})
    target_link_libraries(${APP_TARGET} UntitledImGuiFramework ${YAML_CPP_LIBRARIES_T})
else()
    target_link_libraries(UntitledImGuiFramework ${GLFW_LIBRARIES_T} ${GLEW_LIBRARIES_T} ${OPENGL_LIBRARIES_T} pthread
            ${YAML_CPP_LIBRARIES_T} ${FREETYPE_LIBRARIES} ${VULKAN_LIBRARIES_T} ${X11_LIBRARIES} dl)
    target_link_libraries(${APP_LIB_TARGET} UntitledImGuiFramework pthread dl ${YAML_CPP_LIBRARIES_T})
    target_link_libraries(${APP_TARGET} UntitledImGuiFramework ${APP_LIB_TARGET} ${YAML_CPP_LIBRARIES_T} dl)

    if (APPLE)
        target_link_libraries(UntitledImGuiFramework "-framework Cocoa" "-framework IOKit" "-framework CoreFoundation"
                "-framework QuartzCore")
    endif ()

    if (NOT EMSCRIPTEN)
        multicast(target_link_libraries util)
    endif()

    foreach(f IN ITEMS ${ENABLED_LIBRARIES})
        target_link_libraries(${APP_LIB_TARGET} ${f})
    endforeach()

    if (USE_OS_MODULE AND NOT EMSCRIPTEN)
        if (ENABLE_DBUS_UTILS)
            target_link_libraries(UntitledImGuiFramework    ${DBUS_LIBRARIES})
            target_link_libraries(${APP_LIB_TARGET}         ${DBUS_LIBRARIES})
        endif()
        if (ENABLE_UFONT_UTILS)
            target_link_libraries(UntitledImGuiFramework    Fontconfig::Fontconfig)
            target_link_libraries(${APP_LIB_TARGET}         Fontconfig::Fontconfig)
        endif()
    endif()
endif()

foreach(f IN ITEMS ${ENABLED_LIBRARIES})
    target_link_libraries(UntitledImGuiFramework ${f})
endforeach()