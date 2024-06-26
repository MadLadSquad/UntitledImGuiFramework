option(UIMGUI_INSTALL_FRAMEWORK "Whether to install the framework" OFF)
option(UIMGUI_INSTALL "Installs all libraries" OFF)
option(BUILD_VARIANT_STATIC "Builds the Framework, application library(exists only on Unix) and executable into a single
    executable binary" OFF)

if (EMSCRIPTEN)
    set(BUILD_VARIANT_STATIC ON)
    set(CMAKE_EXECUTABLE_SUFFIX ".html")
    set(OPENGL_LIBRARIES "-s WASM=1 -s USE_WEBGL2=1 -s FULL_ES3=1")

    set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL " " FORCE)
    set(GLFW_BUILD_TESTS    OFF CACHE BOOL " " FORCE)
    set(GLFW_BUILD_DOCS     OFF CACHE BOOL " " FORCE)
    set(GLFW_INSTALL        OFF CACHE BOOL " " FORCE)
    set(GLFW_BUILD_WIN32    OFF CACHE BOOL " " FORCE)
    set(GLFW_BUILD_COCOA    OFF CACHE BOOL " " FORCE)
    set(GLFW_BUILD_X11      OFF CACHE BOOL " " FORCE)
    set(GLFW_BUILD_WAYLAND  OFF CACHE BOOL " " FORCE)
endif()

option(BUILD_VARIANT_VENDOR "If set to OFF will use the globally installed framework(not available on Windows)" ON)
if (BUILD_VARIANT_VENDOR OR WIN32)
    if (NOT EMSCRIPTEN)
        add_subdirectory(Framework/ThirdParty/glfw)
    endif()
    set(GLFW_INCLUDE_DIRS "Framework/ThirdParty/glfw/include/")
    set(GLFW_LIBRARIES_T "glfw")
    if (WIN32)
        add_subdirectory(Framework/ThirdParty/glew)
        set(GLEW_INCLUDE_DIRS "Framework/ThirdParty/glew/include")

        set(GLEW_LIBRARIES_T "libglew_static")
        set(OPENGL_LIBRARIES_T "opengl32")
        set(VULKAN_LIBRARIES_T "vulkan-1")
    elseif (APPLE)
        find_package(OpenGL REQUIRED)
        set(GLEW_LIBRARIES_T "${OPENGL_LIBRARIES}")

        find_package(Vulkan REQUIRED)
        set(VULKAN_LIBRARIES_T Vulkan::Vulkan)
    elseif (NOT EMSCRIPTEN)
        add_subdirectory(Framework/ThirdParty/glew)
        set(GLEW_INCLUDE_DIRS "Framework/ThirdParty/glew/include")

        set(GLEW_LIBRARIES_T "GLEW")
        set(OPENGL_LIBRARIES_T "OpenGL")
        set(X11_LIBRARIES "X11")
        set(VULKAN_LIBRARIES_T "vulkan")
    else ()
    endif()
    add_subdirectory(Framework/ThirdParty/vulkan-headers)
    if (NOT BUILD_VARIANT_STATIC)
        set(BUILD_SHARED_LIBS ON)
    endif()
    if (NOT EMSCRIPTEN)
        add_subdirectory(Framework/ThirdParty/freetype)
        set(FREETYPE_LIBRARIES "freetype")
        set(FREETYPE_INCLUDE_DIRS "")
    endif()

    set(BUILD_SHARED_LIBS ON)
    add_subdirectory(Framework/ThirdParty/yaml-cpp)
    set(YAML_CPP_LIBRARIES_T "yaml-cpp")
    set(YAML_CPP_INCLUDE_DIRS_T "Framework/ThirdParty/yaml-cpp/include/yaml-cpp"
            "Framework/ThirdParty/yaml-cpp/include")
else()
    find_package(PkgConfig REQUIRED)
    find_package(OpenGL REQUIRED)
    if (NOT EMSCRIPTEN)
        find_package(Freetype REQUIRED)
    endif()
    if (NOT WIN32)
        find_package(X11 REQUIRED)
    endif()
    # Re-enable when yaml-cpp 0.8 is released
    if (BUILD_VARIANT_STATIC)
        set(YamlCpp_STATIC ON)
    endif()
    include(FindYamlCpp)
    find_package(YamlCpp REQUIRED)
    set(YAML_CPP_INCLUDE_DIRS_T "${YamlCpp_INCLUDE_PATH}")
    set(YAML_CPP_LIBRARIES_T "${YamlCpp_LIBRARY}")

    set(OPENGL_LIBRARIES_T "${OPENGL_gl_LIBRARY}")
    pkg_check_modules(GLFW REQUIRED glfw3)
    if (BUILD_VARIANT_STATIC)
        set(GLFW_LIBRARIES_T ${GLFW_STATIC_LIBRARIES})
    else()
        set(GLFW_LIBRARIES_T ${GLFW_LIBRARIES})
    endif()
    if (NOT APPLE)
        pkg_check_modules(GLEW REQUIRED glew)
        if (BUILD_VARIANT_STATIC)
            set(GLEW_LIBRARIES_T ${GLEW_STATIC_LIBRARIES})
        else()
            set(GLEW_LIBRARIES_T ${GLEW_LIBRARIES})
        endif()
    endif()
    pkg_check_modules(Vulkan REQUIRED vulkan)
    set(VULKAN_LIBRARIES_T ${Vulkan_LINK_LIBRARIES})
endif()

set(BUILD_SHARED_LIBS OFF)

# ----------------------------------------------------------------------------------------------------------------------
# ------------------------------------------------- Add compile options ------------------------------------------------
# ----------------------------------------------------------------------------------------------------------------------

option(USE_OS_MODULE "Use the operating system module" OFF)
if (USE_OS_MODULE AND NOT EMSCRIPTEN)
    option(ENABLE_UEXEC "Compile in the UntitledExec library for a cross-platform method of launching applications" OFF)
    option(ENABLE_UFONT_UTILS "Compiles in cross-platform utilities for dealing with system fonts" OFF)
    option(ENABLE_UOPEN "Enables the UntitledOpen library, that opens URLs and files with a default application" OFF)

    if (NOT WIN32 AND NOT APPLE)
        option(ENABLE_XDG_BASEDIR "Compile in the UntitledXDGBasedir library for a XDG Basedir implementation" OFF)
        if (ENABLE_XDG_BASEDIR)
            if (BUILD_VARIANT_VENDOR)
                add_subdirectory(Framework/Modules/OS/ThirdParty/UntitledXDGBasedir)
                list(APPEND ENABLED_LIBRARIES UntitledXDGBasedir)
            else()
                find_package(PkgConfig REQUIRED)
                pkg_check_modules(UntitledXDGBasedir REQUIRED UntitledXDGBasedir)

                link_directories(${UntitledXDGBasedir_LIBRARY_DIRS})
                list(APPEND LM_INCLUDE_DIRS ${UntitledXDGBasedir_INCLUDE_DIRS})
                list(APPEND ENABLED_LIBRARIES UntitledXDGBasedir)
                pkg_get_variable(UXDG_COMPILE_DEFS UntitledXDGBasedir compile_defs)
                list(APPEND VENDOR_COMPILE_DEFS ${UXDG_COMPILE_DEFS})
            endif()
        endif()

        option(ENABLE_DBUS_UTILS "Compile in additional utility functions that make using the C DBus API safer" OFF)
        if (ENABLE_DBUS_UTILS)
            find_package(PkgConfig REQUIRED)

            if (BUILD_VARIANT_VENDOR)
                add_subdirectory(Framework/Modules/OS/ThirdParty/UntitledDBusUtils)
                include_directories(${UntitledDBusUtils_INCLUDE_DIRS})
                list(APPEND ENABLED_LIBRARIES UntitledDBusUtils)
            else()
                pkg_check_modules(UntitledDBusUtils REQUIRED UntitledDBusUtils)

                link_directories(${UntitledDBusUtils_LIBRARY_DIRS})
                string(REPLACE " " ";" DBUS_DIRS "${UntitledDBusUtils_INCLUDE_DIRS}")
                include_directories(${DBUS_DIRS})
                list(APPEND ENABLED_LIBRARIES UntitledDBusUtils)
                pkg_get_variable(UDBUS_COMPILE_DEFS UntitledDBusUtils compile_defs)
                list(APPEND VENDOR_COMPILE_DEFS ${UDBUS_COMPILE_DEFS})
            endif()
        endif()
    endif()

    if (ENABLE_UOPEN)
        if (BUILD_VARIANT_VENDOR)
            include_directories("Framework/Modules/OS/ThirdParty/" "Framework/Modules/OS/ThirdParty/UntitledOpen")
            add_subdirectory(Framework/Modules/OS/ThirdParty/UntitledOpen)
            list(APPEND ENABLED_LIBRARIES UntitledOpen)
        else ()
            find_package(PkgConfig REQUIRED)
            pkg_check_modules(UntitledOpen REQUIRED UntitledOpen)

            link_directories(${UntitledOpen_LIBRARY_DIRS})
            list(APPEND LM_INCLUDE_DIRS ${UntitledOpen_INCLUDE_DIRS})
            list(APPEND ENABLED_LIBRARIES UntitledOpen)
            pkg_get_variable(UEXEC_COMPILE_DEFS UntitledOpen compile_defs)
            list(APPEND VENDOR_COMPILE_DEFS ${UntitledOpen_COMPILE_DEFS})
        endif ()
    endif()

    if (ENABLE_UEXEC)
        if (BUILD_VARIANT_VENDOR)
            include_directories("Framework/Modules/OS/ThirdParty/" "Framework/Modules/OS/ThirdParty/uexec")
            add_subdirectory(Framework/Modules/OS/ThirdParty/uexec)
            list(APPEND ENABLED_LIBRARIES uexec)
        else ()
            find_package(PkgConfig REQUIRED)
            pkg_check_modules(uexec REQUIRED uexec)

            link_directories(${uexec_LIBRARY_DIRS})
            list(APPEND LM_INCLUDE_DIRS ${uexec_INCLUDE_DIRS})
            list(APPEND ENABLED_LIBRARIES uexec)
            pkg_get_variable(UEXEC_COMPILE_DEFS uexec compile_defs)
            list(APPEND VENDOR_COMPILE_DEFS ${UEXEC_COMPILE_DEFS})
        endif ()
    endif()
    if (ENABLE_UFONT_UTILS)
        find_package(Fontconfig REQUIRED)
    endif()
endif()

option(USE_THEME_MODULE "Compile in the UDE theme integration system for supporting theming in your application" ON)
option(USE_I18N_MODULE "Use the i18n module" ON)
option(USE_UNDO_MODULE "Use the Undo/Redo module" ON)

# Styling and GUI widgets modules
option(USE_PLOTTING_MODULE "Use the plotting module" ON)
option(USE_KNOBS_MODULE "Use the knobs module" ON)
option(USE_SPINNER_MODULE "Use the spinners module" ON)
option(USE_TOGGLES_MODULE "Use the toggles module" ON)
option(USE_TEXT_UTILS_MODULE "Use the text utils module" ON)
option(USE_CLI_PARSER_MODULE "Use the CLI Parser module" ON)

if (USE_CLI_PARSER_MODULE)
    if (BUILD_VARIANT_VENDOR)
        add_subdirectory(Framework/Modules/CLIParser/ThirdParty/UntitledCLIParser)
        list(APPEND ENABLED_LIBRARIES UntitledCLIParser)
    else()
        find_package(PkgConfig REQUIRED)
        pkg_check_modules(UntitledCLIParser REQUIRED UntitledCLIParser)

        link_directories(${UntitledCLIParser_LIBRARY_DIRS})
        list(APPEND LM_INCLUDE_DIRS ${UntitledCLIParser_INCLUDE_DIRS})
        list(APPEND ENABLED_LIBRARIES UntitledCLIParser)
        pkg_get_variable(UCLI_COMPILE_DEFS UntitledCLIParser compile_defs)
        list(APPEND VENDOR_COMPILE_DEFS ${UCLI_COMPILE_DEFS})
    endif()
endif()

add_subdirectory(Framework/ThirdParty/utfcpp)

if (USE_I18N_MODULE)
    if (BUILD_VARIANT_VENDOR)
        set(USE_PRECONFIGURED_YAML ON)
        add_subdirectory(Framework/Modules/i18n/ThirdParty/UntitledI18N)
        list(APPEND ENABLED_LIBRARIES UntitledI18N)
    else()
        find_package(PkgConfig REQUIRED)
        pkg_check_modules(UntitledI18N REQUIRED UntitledI18N)

        link_directories(${UntitledI18N_LIBRARY_DIRS})
        list(APPEND LM_INCLUDE_DIRS ${UntitledI18N_INCLUDE_DIRS})
        list(APPEND ENABLED_LIBRARIES UntitledI18N)
        pkg_get_variable(UI18N_COMPILE_DEFS UntitledI18N compile_defs)
        list(APPEND VENDOR_COMPILE_DEFS ${UI18N_COMPILE_DEFS})
    endif()
endif()