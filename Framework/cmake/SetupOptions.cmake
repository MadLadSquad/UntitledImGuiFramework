include("${APP_TARGET}Modules")

option(UIMGUI_INSTALL_FRAMEWORK "Whether to install the framework" OFF)
option(UIMGUI_INSTALL "Installs all libraries" OFF)
option(BUILD_VARIANT_STATIC "Builds the Framework, application library(exists only on Unix) and executable into a single
    executable binary" OFF)
option(BUILD_VARIANT_VENDOR "If set to OFF will use the globally installed framework(not available on Windows)" ON)
option(UIMGUI_PRODUCTION_BUILD "Whether the current compilation is going to be targeting a production environment. Read the documentation for more information" OFF)
option(UIMGUI_IN_BUNDLE "Enabled only if compiling as a macOS app bundle." OFF)

setup_pre_dependency_options()

if (BUILD_VARIANT_VENDOR OR WIN32)
    setup_glfw_vendored()
    setup_opengl_vendored()
    setup_vulkan_vendored()
	
    setup_freetype_vendored()
else()
    find_package(PkgConfig REQUIRED)
    find_package(Freetype REQUIRED)

    setup_opengl_system()
    setup_vulkan_system()
    setup_glfw_system()
endif()
setup_yaml_vendored()

set(BUILD_SHARED_LIBS OFF)

# ----------------------------------------------------------------------------------------------------------------------
# ------------------------------------------------- Add compile options ------------------------------------------------
# ----------------------------------------------------------------------------------------------------------------------

option(USE_OS_MODULE "Use the operating system module" OFF)
if (USE_OS_MODULE AND NOT EMSCRIPTEN)
    option(ENABLE_UEXEC "Compile in the UntitledExec library for a cross-platform method of launching applications" OFF)
    option(ENABLE_UOPEN "Enables the UntitledOpen library, that opens URLs and files with a default application" OFF)

    setup_platform_os_module()

    if (ENABLE_UOPEN)
        if (BUILD_VARIANT_VENDOR)
            include_directories("${UIMGUI_SRC_PREFIX}/Framework/Modules/OS/ThirdParty/"
                    "${UIMGUI_SRC_PREFIX}/Framework/Modules/OS/ThirdParty/UntitledOpen"
            )
            add_subdirectory("${UIMGUI_SRC_PREFIX}/Framework/Modules/OS/ThirdParty/UntitledOpen")
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
            include_directories("${UIMGUI_SRC_PREFIX}/Framework/Modules/OS/ThirdParty/"
                    "${UIMGUI_SRC_PREFIX}/Framework/Modules/OS/ThirdParty/uexec"
            )
            add_subdirectory("${UIMGUI_SRC_PREFIX}/Framework/Modules/OS/ThirdParty/uexec")
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
endif()

option(USE_THEME_MODULE "Compile in the UDE theme integration system for supporting theming in your application" OFF)
option(USE_I18N_MODULE "Use the i18n module" OFF)
option(USE_UNDO_MODULE "Use the Undo/Redo module" OFF)

# Styling and GUI widgets modules
option(USE_PLOTTING_MODULE "Use the plotting module" OFF)
option(USE_KNOBS_MODULE "Use the knobs module" OFF)
option(USE_SPINNER_MODULE "Use the spinners module" OFF)
option(USE_TOGGLES_MODULE "Use the toggles module" OFF)
option(USE_TEXT_UTILS_MODULE "Use the text utils module" OFF)
option(USE_CLI_PARSER_MODULE "Use the CLI Parser module" OFF)

if (USE_CLI_PARSER_MODULE)
    if (BUILD_VARIANT_VENDOR)
        add_subdirectory("${UIMGUI_SRC_PREFIX}/Framework/Modules/CLIParser/ThirdParty/UntitledCLIParser")
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

if (USE_I18N_MODULE)
    if (BUILD_VARIANT_VENDOR)
        # TODO: remove: set(USE_PRECONFIGURED_YAML ON)
        add_subdirectory("${UIMGUI_SRC_PREFIX}/Framework/Modules/i18n/ThirdParty/UntitledI18N")
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

setup_platform_additional_graphics_backends()
custom_setup_step()
