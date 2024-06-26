set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/Config/cmake/")
include(${APP_TARGET})

include(SetupLanguageBoilerplate)
include(SetupCompilation)
include(SetupSources)
include(CompileProject)