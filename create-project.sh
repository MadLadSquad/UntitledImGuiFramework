#!/bin/bash

windows=false

# Used to automatically find and add the Visual Studio MSBuild.exe directory to the environment variables!
function find_visual_studio_directory()
{
  env | grep "OS=Windows" > /dev/null && windows=true

  if [ "${windows}" = true ]; then
    wd=$(pwd)
    cd "C:/Program Files (x86)/Microsoft Visual Studio/Installer/"
    find "vswhere.exe" -maxdepth 0 &> /dev/null || (cd "${wd}" && download_vswhere)

    VSShortVer=$(./vswhere.exe | grep "catalog_productLine: Dev17")
    VSShortVer="${VSShortVer:24}"

    VSVer=$(./vswhere.exe | grep "catalog_productLineVersion:")
    VSVer="${VSVer:28}"

    cd "${wd}"
  fi
  return
}

function create_folders()
{
  cd Projects/ || exit
  mkdir "${prjname}" || echo "Project already exists!"
  cd "${prjname}" || exit

  # Create folders and files to be used as configs
  mkdir Source || echo "Project already exists!"
  mkdir Generated || echo "Project already exists!"
  mkdir build || echo "Project already exists!"
  mkdir Exported || echo "Project already exists!"

  # Copy the config template we want
  cp ../../Config/ . -r
  cp ../../Content/ . -r
  cp ../../export.sh .

  # We create a project file which will be used to configure our generated files
  touch uvproj.yaml && echo "\
name: \"${prjname}\"
version: \"1.0.0.0\"
engine-version: \"1.0.0.0\"
build-mode-static: false
build-mode-vendor: true
enabled-modules:
  os: false
  dbus: false
  uexec: false
  theming: false
  notifications: false
  polkit: false
  ufont: false
  i18n: false
  undo-redo: false
  plotting: false
  knobs: false
  spinners: false
  toggles: false
  text-utils: false
  cli-parser: false
" > uvproj.yaml

  # Create symbolic links
  ln -rs "../../Framework/" Framework 2> /dev/null || cp ../../Engine/ . -r
  ln -rs "../../UVKBuildTool/" UVKBuildTool 2> /dev/null || cp ../../UVKBuildTool/ . -r
}

function generate_files()
{
  cd ../../UVKBuildTool/build || exit
  if [ "${windows}" == true ]; then
    ./UVKBuildTool.exe --install ../../Projects/"${prjname}" || exit
  else
    ./UVKBuildTool --install ../../Projects/"${prjname}" || exit
  fi
  cd ../../Projects/"${prjname}" || exit
}

function compile()
{
  cd build || exit
  if [ "${windows}" == true ]; then
    cmake .. -G "Visual Studio ${VSShortVer} ${VSVer}" -DCMAKE_BUILD_TYPE=RELEASE || exit
    MSBuild.exe "${prjname}".sln -property:Configuration=Release -property:Platform=x64 -property:maxCpuCount="${cpus}" || exit

    cp Release/"${prjname}".exe . || exit
    cp ../UVKBuildTool/build/Release/UVKBuildToolLib.dll . || exit
    cp Framework/ThirdParty/yaml-cpp/Release/yaml-cpp.dll . || exit
    cp yaml-cpp.dll Release/ || exit 
  else
    cmake .. -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=RELEASE || exit
    make -j "${cpus}" || exit
  fi
}

if [ "$1" != "" ]; then
  prjname="$1"
else
  read -rp "Enter Your Application Name: " prjname # read the project name
fi
prjname=${prjname/ /} # Remove any spaces if the name contains them
cpus=$(grep -c processor /proc/cpuinfo) ## get the cpu threads for maximum performance when compiling
echo -e "\x1B[32mCopiling with ${cpus} compute jobs!\033[0m"
find_visual_studio_directory
create_folders "${prjname}"
generate_files "${prjname}"
compile "${prjname}" "$2"

echo -e "\x1B[32mFramework and project successfully installed! \033[0m"
