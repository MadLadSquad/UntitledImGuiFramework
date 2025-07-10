set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/Config/cmake/")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/Generated/")

if (EMSCRIPTEN)
    include(Platform/EmscriptenPlatform)
    initialise_platform()
elseif (NOT WIN32 AND NOT APPLE)
    include(Platform/UnixPlatform)
    initialise_platform()
endif()

include(${APP_TARGET})

include(SetupLanguageBoilerplate)
include(SetupOptions)
include(SetupSources)
include(CompileProject)