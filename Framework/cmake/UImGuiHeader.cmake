if (WIN32)
	include(Platform/WindowsPlatform)
	initialise_platform()
elseif (APPLE)
	include(Platform/ApplePlatform)
	initialise_platform()
endif()

option(UIMGUI_SKIP_FRAMEWORK "Enable this option in order to compile directly with the system framework" OFF)