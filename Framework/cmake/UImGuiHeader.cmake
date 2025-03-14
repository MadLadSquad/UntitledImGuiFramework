if (WIN32)
	set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreadedDLL")
	add_compile_options("/MD")
elseif (APPLE)
	# Fixes to be able to use the shared vulkan library
	set(CMAKE_INSTALL_RPATH "@executable_path/../Frameworks")
	set(CMAKE_MACOSX_RPATH TRUE)
	set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
elseif (EMSCRIPTEN)
	# Fixes freetype not compiling
	add_compile_options(-fwasm-exceptions)
	add_link_options(-fwasm-exceptions)
endif()
option(UIMGUI_SKIP_FRAMEWORK "Enable this option in order to compile directly with the system framework" OFF)