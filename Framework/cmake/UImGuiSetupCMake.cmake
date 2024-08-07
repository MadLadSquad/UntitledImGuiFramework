set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/Config/cmake/")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/Generated/")
include(${APP_TARGET})

include(SetupLanguageBoilerplate)
include(SetupCompilation)
include(SetupSources)
include(CompileProject)