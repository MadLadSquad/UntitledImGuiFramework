#!/usr/bin/env bash

windows=false

# Used to automatically find and add the Visual Studio MSBuild.exe directory to the environment variables!
function find_visual_studio_directory()
{
  env | grep "OS=Windows" > /dev/null && windows=true

  if [ "${windows}" = true ]; then
    wd=$(pwd)
    cd "C:/Program Files (x86)/Microsoft Visual Studio/Installer/" || exit
    find "vswhere.exe" -maxdepth 0 &> /dev/null || (cd "${wd}" && download_vswhere)

    VSShortVer=$(./vswhere.exe | grep "catalog_productLine: Dev17")
    VSShortVer="${VSShortVer:24}"

    VSVer=$(./vswhere.exe | grep "catalog_productLineVersion:")
    VSVer="${VSVer:28}"

    cd "${wd}" || exit
  fi
  return
}

function create()
{
  cd Projects || exit
  mkdir "${plugin_name}" || echo "Project already exists"
  cd "${plugin_name}" || exit

  echo "\
#include <Framework/Framework.hpp>
#include <Generated/Config.hpp>

#ifdef _WIN32
    #define PLUGIN_EXPORT __declspec(dllexport)
#else
    #define PLUGIN_EXPORT
#endif

#ifdef __cplusplus
extern \"C\"
{
#endif
    PLUGIN_EXPORT void UImGui_Plugin_attach(void* context)
    {
        UImGui::Utility::loadContext(context);
    }

    PLUGIN_EXPORT void UImGui_Plugin_detach()
    {
    }
#ifdef __cplusplus
}
#endif" > plugin.cpp

    echo "\
cmake_minimum_required(VERSION 3.21)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_C_STANDARD 99)

set(UIMGUI_PLUGIN_APP_NAME \"${prjname}\")
set(UIMGUI_PLUGIN_NAME \"${plugin_name}\")
set(CMAKE_MODULE_PATH \${CMAKE_MODULE_PATH} \"\${CMAKE_SOURCE_DIR}/\${UIMGUI_PLUGIN_APP_NAME}/Framework/cmake/\")

include(PluginDefaultsInit)
project(${plugin_name})
include(PluginDefaultsPostInst)
" > CMakeLists.txt

  cp ../../example.gitignore .gitignore

  # Create symbolic links
  if [ "${windows}" == true ]; then
    cmd //c mklink //d .\\"${prjname}" ..\\"${prjname}" && return
  fi
  ln -s "../${prjname}/" "${prjname}" 2> /dev/null || cp -r ../"${prjname}" .
}

function compile()
{
  mkdir build || exit
  cd build || exit
  cp ../"${prjname}"/Framework/ThirdParty/vulkan/vulkan-1.lib ../"${prjname}"/Framework/ThirdParty/vulkan/libvulkan.1.dylib . || exit
  if [ "${windows}" == true ]; then
    cmake .. -G "Visual Studio ${VSShortVer} ${VSVer}" -DCMAKE_BUILD_TYPE=RELEASE || exit
    MSBuild.exe "${plugin_name}".sln -property:Configuration=Release -property:Platform=x64 -property:maxCpuCount="${cpus}" || exit
  else
    cmake .. -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=RELEASE || exit
    make -j "${cpus}" || exit
  fi
}

if [ "$1" != "" ] && [ "$2" != "" ]; then
  plugin_name="$1"
  prjname="$2"

  headless=true
else
  read -rp "Enter your plugin's name: " plugin_name # read the project name
  read -rp "Enter the target application's name: " prjname
fi
prjname=${prjname/ /}
plugin_name=${plugin_name/ /}

cpus=$(grep -c processor /proc/cpuinfo 2> /dev/null) || cpus=$(sysctl -n hw.ncpu) # get the cpu threads for maximum performance when compiling. The second command is for macOS systems if we even try to support them
echo -e "\x1B[32mCopiling with ${cpus} compute jobs!\033[0m"

find_visual_studio_directory
create
if [ "$3" != "--skip-compilation" ]; then
  compile
fi
echo -e "\x1B[32mPlugin successfully installed!\x1B[0m"
