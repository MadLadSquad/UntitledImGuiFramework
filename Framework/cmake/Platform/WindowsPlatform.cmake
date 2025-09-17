include(GenericPlatform)

macro(setup_pre_dependency_options)
endmacro()

macro(setup_freetype_vendored)
    set(SKIP_INSTALL_ALL ON) # Disable installing freetype
    setup_freetype_vendored_generic()
endmacro()

macro(setup_glfw_vendored)
    setup_glfw_vendored_generic(ON)
endmacro()

macro(setup_yaml_cpp_vendored)
    setup_yaml_cpp_vendored_generic(ON)
endmacro()

macro(setup_vulkan_vendored)
    set(VULKAN_LIBRARIES_T "vulkan-1")
    add_subdirectory("${UIMGUI_SRC_PREFIX}/Framework/ThirdParty/vulkan-headers")
endmacro()

macro(setup_opengl_vendored)
    set(OPENGL_LIBRARIES_T "opengl32")
endmacro()

macro(setup_opengl_system)
    setup_opengl_system_generic()
endmacro()

macro(setup_platform_os_module)
endmacro()

macro(setup_platform_additional_graphics_backends)
    option(IMGUI_BUILD_WITH_DX12 "Include the DirectX 12 graphics API for use in custom renderers." OFF)
    option(IMGUI_BUILD_WITH_DX11 "Include the DirectX 11 graphics API for use in custom renderers." OFF)
endmacro()

macro(build_framework_static)
    if (NOT UIMGUI_SKIP_FRAMEWORK)
        add_library(UntitledImGuiFramework STATIC "${LIBRARY_SOURCES}" "${APP_LIBRARY_SOURCES}")
    endif()
    add_executable(${APP_TARGET} ${EXECUTABLE_SOURCES} "Config/Resources/resource.rc")
endmacro()

macro(build_framework_shared)
    if (NOT UIMGUI_SKIP_FRAMEWORK)
        add_library(UntitledImGuiFramework SHARED ${LIBRARY_SOURCES} ${APP_LIBRARY_SOURCES})
    endif()
    add_executable(${APP_TARGET} ${EXECUTABLE_SOURCES} "Config/Resources/resource.rc")
endmacro()

macro(link_to_framework_libraries)
    if (NOT UIMGUI_SKIP_FRAMEWORK)
        target_link_libraries(UntitledImGuiFramework ${GLFW_LIBRARIES_T} ${OPENGL_LIBRARIES_T}
                ${YAML_CPP_LIBRARIES_T} ${FREETYPE_LIBRARIES} ${VULKAN_LIBRARIES_T})
    endif()
    target_link_libraries(${APP_TARGET} UntitledImGuiFramework ${YAML_CPP_LIBRARIES_T})

    if (IMGUI_BUILD_WITH_DX12)
        multicast(target_link_libraries d3d12 d3dcompiler dxgi)
    endif ()
    if (IMGUI_BUILD_WITH_DX11)
        multicast(target_link_libraries d3d11 d3dcompiler)
    endif ()
endmacro()

macro(setup_platform_compilation_plugin)
    target_compile_options(${UIMGUI_PLUGIN_NAME} PRIVATE "/Zc:__cplusplus")
endmacro()

macro(setup_output_path)
    set(LIBRARY_OUTPUT_PATH "${CMAKE_BINARY_DIR}")
    set(EXECUTABLE_OUTPUT_PATH "${CMAKE_BINARY_DIR}")
endmacro()

macro(setup_app_sources)
endmacro()

macro(setup_platform_imgui_sources)
    if (IMGUI_BUILD_WITH_DX12)
        file(GLOB_RECURSE IMGUI_DX12_SRC "${UIMGUI_SRC_PREFIX}/Framework/ThirdParty/imgui/backends/imgui_impl_dx12.cpp")
        file(GLOB_RECURSE IMGUI_DX12_HEAD "${UIMGUI_SRC_PREFIX}/Framework/ThirdParty/imgui/backends/imgui_impl_dx12.h")
    endif()

    if (IMGUI_BUILD_WITH_DX11)
        file(GLOB_RECURSE IMGUI_DX11_SRC "${UIMGUI_SRC_PREFIX}/Framework/ThirdParty/imgui/backends/imgui_impl_dx11.cpp")
        file(GLOB_RECURSE IMGUI_DX11_HEAD "${UIMGUI_SRC_PREFIX}/Framework/ThirdParty/imgui/backends/imgui_impl_dx11.h")
    endif()

    file(GLOB_RECURSE IMGUI_ADDITIONAL_BACKENDS_SRC ${IMGUI_DX11_SRC} ${IMGUI_DX12_SRC})
    file(GLOB_RECURSE IMGUI_ADDITIONAL_BACKENDS_HEAD ${IMGUI_DX11_HEAD} ${IMGUI_DX12_HEAD})
endmacro()

macro(setup_opengl_loader_sources)
    setup_opengl_loader_sources_generic(OFF)
endmacro()

macro(setup_platform_target_settings)
    setup_platform_target_settings_generic()
    if (NOT UIMGUI_SKIP_FRAMEWORK)
        target_compile_definitions(UntitledImGuiFramework PRIVATE "UIMGUI_PUBLIC_API=__declspec(dllexport)"
                "IMGUI_API=__declspec(dllexport)" "CIMGUI_API=__declspec(dllexport)"
                "MLS_PUBLIC_API=__declspec(dllexport)"
        )
    endif ()
    multicast(target_compile_definitions PRIVATE "UIMGUI_PLATFORM_WINDOWS")
    multicast(target_compile_options PRIVATE "/Zc:__cplusplus")
endmacro()

macro(initialise_platform)
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreadedDLL")
    add_compile_options("/MD")
endmacro()
