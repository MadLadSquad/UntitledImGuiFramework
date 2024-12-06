#!/usr/bin/env bash
cpus=$(grep -c processor /proc/cpuinfo) || cpus=$(sysctl -n hw.ncpu)
echo -e "\x1b[32mCompiling with ${cpus} jobs!\x1b[0m"

git pull
git submodule update --remote --merge --init --recursive

cd UVKBuildTool || exit
git pull origin master
git submodule update --remote --merge --init --recursive

cd build || exit
cmake .. -DUBT_FRAMEWORK_DIR="$(realpath ../../)" || exit
MSBuild.exe UVKBuildTool.sln -property:Configuration=Release -property:Platform=x64 -property:maxCpuCount="${cpus}" || make -j "${cpus}" || exit

cd ../../ || exit
echo -e "\x1b[32mSuccessfully updated the framework!\x1b[0m"
