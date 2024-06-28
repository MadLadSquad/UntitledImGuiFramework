if (EMSCRIPTEN)


    set_target_properties(${APP_LIB_TARGET} PROPERTIES LINK_FLAGS "${ASSET_LINK_FLAGS}")

    multicast(set_target_properties PROPERTIES LINK_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/Config)
    multicast(set_target_properties PROPERTIES LINK_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/Content)
    multicast(set_target_properties PROPERTIES LINK_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/uvproj.yaml)
endif ()

if (EMSCRIPTEN)
    multicast(target_compile_options PRIVATE -fwasm-exceptions -sSUPPORT_LONGJMP=wasm)

    set(EM_LINK_FLAGS "--preload-file ${CMAKE_CURRENT_SOURCE_DIR}/Config@../Config --preload-file ${CMAKE_CURRENT_SOURCE_DIR}/Content@../Content --preload-file ${CMAKE_CURRENT_SOURCE_DIR}/uvproj.yaml@../uvproj.yaml")

    if (ENABLE_PRE_SCRIPT)
        set(EM_LINK_FLAGS "${EM_LINK_FLAGS} --pre-js ${CMAKE_CURRENT_SOURCE_DIR}/Config/WASM/pre.js")
    endif()

    if (ENABLE_POST_SCRIPT)
        set(EM_LINK_FLAGS "${EM_LINK_FLAGS} --post-js ${CMAKE_CURRENT_SOURCE_DIR}/Config/WASM/post.js")
    endif()

    multicast(set_target_properties PROPERTIES LINK_FLAGS "${EM_LINK_FLAGS}")
endif()

if (BUILD_VARIANT_STATIC)
    multicast(target_compile_definitions PRIVATE UIMGUI_BUILD_VARIANT_STATIC)
endif()

if (BUILD_VARIANT_VENDOR)
    multicast(target_compile_definitions PRIVATE UIMGUI_BUILD_VARIANT_VENDOR)
endif()

if (USE_PLOTTING_MODULE)
    multicast(target_compile_definitions PRIVATE UIMGUI_PLOTTING_MODULE_ENABLED)
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

    if (ENABLE_UFONT_UTILS)
        multicast(target_compile_definitions PRIVATE UIMGUI_UFONT_UTILS_SUBMODULE_ENABLED)
    endif()
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