include(GenericPlatform)

macro(setup_pre_dependency_options)
    option(USE_HTML_GENERATION "Automatically generate HTML" ON)
    set(BUILD_VARIANT_STATIC ON)
    if (USE_HTML_GENERATION)
        set(CMAKE_EXECUTABLE_SUFFIX ".html")
    endif()
    set(OPENGL_LIBRARIES "-sWASM=1 -sUSE_WEBGPU=1 -sUSE_WEBGL2=1 -sFULL_ES3=1 -O0 -fwasm-exceptions")

    set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL " " FORCE)
    set(GLFW_BUILD_TESTS    OFF CACHE BOOL " " FORCE)
    set(GLFW_BUILD_DOCS     OFF CACHE BOOL " " FORCE)
    set(GLFW_INSTALL        OFF CACHE BOOL " " FORCE)
    set(GLFW_BUILD_WIN32    OFF CACHE BOOL " " FORCE)
    set(GLFW_BUILD_COCOA    OFF CACHE BOOL " " FORCE)
    set(GLFW_BUILD_X11      OFF CACHE BOOL " " FORCE)
    set(GLFW_BUILD_WAYLAND  OFF CACHE BOOL " " FORCE)
endmacro()

macro(setup_glfw_vendored)
    setup_glfw_vendored_generic(OFF)
endmacro()

macro(setup_yaml_cpp_vendored)
    setup_yaml_cpp_vendored_generic(OFF)
endmacro()

macro(setup_vulkan_vendored)
endmacro()

macro(setup_opengl_vendored)
endmacro()

macro(setup_freetype_vendored)
    set(SKIP_INSTALL_ALL ON) # Disable installing freetype
    setup_freetype_vendored_generic()
endmacro()

macro(setup_opengl_system)
    setup_opengl_system_generic()
endmacro()

macro(setup_platform_os_module)
endmacro()

macro(setup_platform_additional_graphics_backends)
endmacro()

macro(build_framework_static)
    add_executable(${APP_TARGET} "${LIBRARY_SOURCES}" "${APP_LIBRARY_SOURCES}" ${EXECUTABLE_SOURCES})
endmacro()

macro(build_framework_shared)
    build_framework_static()
endmacro()

macro(link_to_framework_libraries)
    target_link_libraries(${APP_TARGET} ${GLFW_LIBRARIES_T} ${OPENGL_LIBRARIES_T} pthread dl
            ${YAML_CPP_LIBRARIES_T} ${FREETYPE_LIBRARIES} ${VULKAN_LIBRARIES_T} ${X11_LIBRARIES})

    foreach(f IN ITEMS ${ENABLED_LIBRARIES})
        target_link_libraries(${APP_TARGET} ${f})
    endforeach()
endmacro()

macro(setup_platform_compilation_plugin)
    setup_platform_compilation_plugin_generic()
endmacro()

macro(setup_output_path)
endmacro()

macro(setup_app_sources)
endmacro()

macro(setup_platform_imgui_sources)
endmacro()

macro(setup_opengl_loader_sources)
    setup_opengl_loader_sources_generic(OFF)
endmacro()

macro(setup_platform_target_settings)
    multicast(target_compile_options PRIVATE -fwasm-exceptions -sSUPPORT_LONGJMP=wasm -Wbad-function-cast -Wcast-function-type)

    set(EM_LINK_FLAGS "--extern-pre-js ${UIMGUI_SRC_PREFIX}/Framework/Core/Platform/framework_pre.js -fwasm-exceptions --preload-file ${CMAKE_CURRENT_SOURCE_DIR}/Config@../Config --preload-file ${CMAKE_CURRENT_SOURCE_DIR}/Content@../Content --preload-file ${CMAKE_CURRENT_SOURCE_DIR}/uvproj.yaml@../uvproj.yaml")

    if (ENABLE_PRE_SCRIPT)
        set(EM_LINK_FLAGS "${EM_LINK_FLAGS} --pre-js ${CMAKE_CURRENT_SOURCE_DIR}/Config/WASM/pre.js")
    endif()

    if (ENABLE_POST_SCRIPT)
        set(EM_LINK_FLAGS "${EM_LINK_FLAGS} --post-js ${CMAKE_CURRENT_SOURCE_DIR}/Config/WASM/post.js")
    endif()

    multicast(set_target_properties PROPERTIES LINK_FLAGS "${EM_LINK_FLAGS}")

    multicast(target_link_options PRIVATE -sUSE_WEBGPU=1 -sUSE_GLFW=3 -sALLOW_MEMORY_GROWTH=1 -fwasm-exceptions
            -sSUPPORT_LONGJMP=wasm)

    multicast(target_compile_definitions PRIVATE "UIMGUI_PLATFORM_WASM")
endmacro()

macro(initialise_platform)
    # Fixes freetype not compiling
    add_compile_options(-fwasm-exceptions)
    add_link_options(-fwasm-exceptions)
endmacro()
