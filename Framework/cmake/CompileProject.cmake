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

multicast(set_target_properties PROPERTIES LINKER_LANGUAGE CXX)
include(SetupTargetSettings)

if (EMSCRIPTEN)
    multicast(target_compile_options PRIVATE -fwasm-exceptions -sSUPPORT_LONGJMP=wasm)

    # Package asset files
    file(GLOB_RECURSE CONFIG_ASSET_FILES ${CMAKE_SOURCE_DIR}/Config/*)
    file(GLOB_RECURSE CONTENT_ASSET_FILES ${CMAKE_SOURCE_DIR}/Content/*)

    foreach(asset_file ${CONFIG_ASSET_FILES})
        string(REPLACE "${CMAKE_SOURCE_DIR}/" "" relative_asset_file ${asset_file})
        list(APPEND ASSET_LINK_FLAGS --preload-file ${asset_file}@/${relative_asset_file})
    endforeach()

    foreach(asset_file ${CONTENT_ASSET_FILES})
        string(REPLACE "${CMAKE_SOURCE_DIR}/" "" relative_asset_file ${asset_file})
        list(APPEND ASSET_LINK_FLAGS --preload-file ${asset_file}@/${relative_asset_file})
    endforeach()

    set_target_properties(${APP_LIB_TARGET} PROPERTIES LINK_FLAGS "${ASSET_LINK_FLAGS}")

    multicast(set_target_properties PROPERTIES LINK_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/Config)
    multicast(set_target_properties PROPERTIES LINK_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/Content)
    multicast(set_target_properties PROPERTIES LINK_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/uvproj.yaml)
endif ()

target_compile_definitions(UntitledImGuiFramework PRIVATE "UIMGUI_COMPILE_LIB" "YAML_CPP_DLL"
        "UVK_LOG_EXPORT_FROM_LIBRARY" "UVK_LIB_COMPILE" "URLL_USE_FUNCTIONAL")
if (NOT WIN32)
    target_compile_definitions(${APP_LIB_TARGET} PRIVATE "URLL_USE_FUNCTIONAL" "UVK_LOG_EXPORT_FROM_LIBRARY")
endif()
target_compile_definitions(${APP_TARGET} PRIVATE "UVK_LOG_EXPORT_FROM_LIBRARY" "URLL_USE_FUNCTIONAL")

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

    if (EMSCRIPTEN)
        multicast(target_link_options PRIVATE -sUSE_GLFW=3 -s ALLOW_MEMORY_GROWTH=1 -fwasm-exceptions
                -sSUPPORT_LONGJMP=wasm)
    else ()
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