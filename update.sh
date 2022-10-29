#!/bin/bash
cpus=$(grep -c processor /proc/cpuinfo)
echo -e "\x1b[32mCompiling with ${cpus} jobs!\x1b[0m"

git pull
git submodule update --remote --merge

cd UVKBuildTool || exit
git pull
git submodule update --remote --merge

cd build || exit
MSBuild.exe UVKBuildTool.sln -property:Configuration=Release -property:Platform=x64 -property:maxCpuCount="${cpus}" || make -j "${cpus}" || exit
cp Release/UVKBuildTool.exe . 2> /dev/null || echo " " || exit
cp Release/UVKBuildToolLib.dll . 2> /dev/null || cp Release/libUVKBuildToolLib.dll . 2> /dev/null || echo " "
cp Release/UVKBuildToolLib.lib . 2> /dev/null || cp Release/libUVKBuildToolLib.lib . 2> /dev/null || echo " "
cp yaml-cpp/Release/yaml-cpp.dll . 2> /dev/null || cp yaml-cpp/Release/libyaml-cpp.dll . 2> /dev/null || echo " "

cd ../../ || exit
echo -e "\x1b[32mSuccessfully updated the framework!\x1b[0m"
