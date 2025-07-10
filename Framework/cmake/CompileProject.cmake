if (BUILD_VARIANT_STATIC)
    build_framework_static()
else()
    build_framework_shared()
endif()

include(SetupTargetSettings)

link_to_framework_libraries()
if (NOT EMSCRIPTEN AND NOT UIMGUI_SKIP_FRAMEWORK)
    foreach(f IN ITEMS ${ENABLED_LIBRARIES})
        target_link_libraries(UntitledImGuiFramework ${f})
    endforeach()
endif()

configure_file(Framework/cmake/UntitledImGuiFramework.pc.in UntitledImGuiFramework.pc @ONLY)