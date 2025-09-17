include(GenericUnix)

macro(setup_freetype_vendored)
    set(SKIP_INSTALL_ALL OFF)
    setup_freetype_vendored_generic()
endmacro()

macro(setup_vulkan_vendored)
    find_package(Vulkan REQUIRED)
    set(VULKAN_LIBRARIES_T Vulkan::Vulkan)
endmacro()

macro(setup_opengl_vendored)
    find_package(OpenGL REQUIRED)
    set(OPENGL_LIBRARIES_T ${OPENGL_LIBRARIES})
endmacro()

macro(setup_opengl_system)
    setup_opengl_system_generic()
endmacro()

macro(setup_platform_os_module)
endmacro()

macro(setup_platform_additional_graphics_backends)
    option(IMGUI_BUILD_WITH_METAL "Include Apple's Metal graphics API for use in custom renderers." OFF)
endmacro()

macro(setup_app_sources)
    file(GLOB_RECURSE UGUI_APP_SRC_APPLE "Source/*.m" "Source/*.mm")
    list(APPEND UGUI_APP_HEAD ${UGUI_APP_SRC_APPLE})

    file(GLOB_RECURSE APPLE_SRC "${UIMGUI_SRC_PREFIX}/Framework/Renderer/*.mm"
            "${UIMGUI_SRC_PREFIX}/Framework/Renderer/*.m" "${UIMGUI_SRC_PREFIX}/Framework/Core/*.mm")
endmacro()

macro(setup_platform_imgui_sources)
    if (IMGUI_BUILD_WITH_METAL)
        file(GLOB_RECURSE IMGUI_ADDITIONAL_BACKENDS_SRC
                "${UIMGUI_SRC_PREFIX}/Framework/ThirdParty/imgui/backends/imgui_impl_metal.mm")
        file(GLOB_RECURSE IMGUI_ADDITIONAL_BACKENDS_HEAD
                "${UIMGUI_SRC_PREFIX}/Framework/ThirdParty/imgui/backends/imgui_impl_metal.h")
    endif()
endmacro()

macro(setup_opengl_loader_sources)
    setup_opengl_loader_sources_generic(ON)
endmacro()

macro(setup_platform_target_settings)
    setup_platform_target_settings_generic()
    multicast(target_compile_definitions PRIVATE "GL_SILENCE_DEPRECATION")
    target_compile_definitions(${APP_LIB_TARGET} PRIVATE "URLL_USE_FUNCTIONAL" "MLS_EXPORT_LIBRARY")

    multicast(target_compile_definitions PRIVATE "UIMGUI_PLATFORM_MACOS")
endmacro()

macro(initialise_platform)
    # Fixes to be able to use the shared vulkan library
    set(CMAKE_INSTALL_RPATH "@executable_path/../Frameworks")
    set(CMAKE_MACOSX_RPATH TRUE)
    set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
endmacro()

macro(link_to_framework_libraries)
    link_to_framework_libraries_generic_unix()
    if (NOT UIMGUI_SKIP_FRAMEWORK)
        target_link_libraries(UntitledImGuiFramework "-framework Cocoa" "-framework IOKit" "-framework CoreFoundation"
                "-framework QuartzCore")
        if (IMGUI_BUILD_WITH_METAL)
            multicast(target_link_libraries "-framework Metal")
        endif()
    endif ()
endmacro()

