if (WIN32)
	set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreadedDLL")
	add_compile_options("/MD")
endif()
