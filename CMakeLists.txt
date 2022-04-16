cmake_minimum_required(VERSION 3.19)

project(UGUI)
project(Example)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(ThirdParty/glfw)
add_subdirectory(ThirdParty/glew)

include_directories(ThirdParty/glfw/include)
include_directories(ThirdParty/glew/include)
include_directories(ThirdParty/imgui/backends/everything)
include_directories(ThirdParty/imgui/)
include_directories(Core/)
include_directories(Renderer/)

file(GLOB_RECURSE UGUI_SRC "Core/*.cpp" "Renderer/*.cpp" "ThirdParty/imgui/backends/everything/*.cpp" "ThirdParty/imgui/misc/cpp/*.cpp")
file(GLOB_RECURSE UGUI_HEAD "Core/*.hpp" "Renderer/*.hpp" "ThirdParty/imgui/backends/everything/*.h" "ThirdParty/imgui/misc/cpp/*.h" )

add_library(UGUI SHARED ${UGUI_SRC} ${UGUI_HEAD})
set_target_properties(UGUI PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(UGUI glfw GLEW OpenGL util pthread)