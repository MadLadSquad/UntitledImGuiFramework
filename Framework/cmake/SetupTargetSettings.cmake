multicast(set_target_properties PROPERTIES LINKER_LANGUAGE CXX)
setup_platform_target_settings()

if (BUILD_VARIANT_STATIC)
    multicast(target_compile_definitions PRIVATE UIMGUI_BUILD_VARIANT_STATIC)
endif()

if (BUILD_VARIANT_VENDOR)
    multicast(target_compile_definitions PRIVATE UIMGUI_BUILD_VARIANT_VENDOR)
endif()

if (USE_PLOTTING_MODULE)
    multicast(target_compile_definitions PRIVATE UIMGUI_PLOTTING_MODULE_ENABLED)
else ()
    multicast(target_compile_definitions PRIVATE DISABLE_CIMPLOT)
endif()

if (USE_KNOBS_MODULE)
    multicast(target_compile_definitions PRIVATE UIMGUI_KNOBS_MODULE_ENABLED)
endif()

if (USE_SPINNER_MODULE)
    multicast(target_compile_definitions PRIVATE UIMGUI_SPINNERS_MODULE_ENABLED)
endif()

if (USE_TOGGLES_MODULE)
    multicast(target_compile_definitions PRIVATE UIMGUI_TOGGLES_MODULE_ENABLED)
endif()

if (USE_UNDO_MODULE)
    multicast(target_compile_definitions PRIVATE UIMGUI_UNDO_MODULE_ENABLED)
endif()

if (USE_TEXT_UTILS_MODULE)
    multicast(target_compile_definitions PRIVATE UIMGUI_TEXT_UTILS_MODULE_ENABLED)
endif()

if (USE_THEME_MODULE)
    multicast(target_compile_definitions PRIVATE UIMGUI_THEME_MODULE_ENABLED)
endif()

if (USE_OS_MODULE AND NOT EMSCRIPTEN)
    multicast(target_compile_definitions PRIVATE UIMGUI_OS_MODULE_ENABLED)

    if (ENABLE_UOPEN)
        multicast(target_compile_definitions PRIVATE UIMGUI_OPEN_SUBMODULE_ENABLED)
    endif ()
endif()
if (BUILD_MODE_VENDOR)
    foreach(f IN ITEMS ${ENABLED_LIBRARIES})
        get_target_property(COMPILE_DEFS ${f} COMPILE_DEFINITIONS)
        multicast(target_compile_definitions PRIVATE ${COMPILE_DEFS})
    endforeach()
else()
    foreach(f IN ITEMS ${VENDOR_COMPILE_DEFS})
        multicast(target_compile_definitions PRIVATE ${f})
    endforeach ()
endif()

if (UIMGUI_PRODUCTION_BUILD)
    multicast(target_compile_definitions PRIVATE "PRODUCTION")
endif()

if (IMGUI_BUILD_WITH_DX11)
    multicast(target_compile_definitions PRIVATE "IMGUI_BUILD_WITH_DX11")
endif()

if (IMGUI_BUILD_WITH_DX12)
    multicast(target_compile_definitions PRIVATE "IMGUI_BUILD_WITH_DX12")
endif()

if (IMGUI_BUILD_WITH_METAL)
    multicast(target_compile_definitions PRIVATE "IMGUI_BUILD_WITH_METAL")
endif()

target_compile_definitions(${APP_TARGET} PRIVATE "MLS_EXPORT_LIBRARY" "URLL_USE_FUNCTIONAL")
multicast(target_compile_definitions PRIVATE "UIMGUI_FRAMEWORK_VERSION=\"${UIMGUI_FRAMEWORK_VERSION}\""
        "UIMGUI_FRAMEWORK_VERSION_NUMERIC=${UIMGUI_FRAMEWORK_VERSION_NUMERIC}")

custom_compile_step()