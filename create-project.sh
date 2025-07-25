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
  cp -r ../../Config .
  cp -r ../../Content .
  cp ../../export.sh .

  mkdir Config/cmake || die
  touch Config/cmake/"${prjname}".cmake && echo "\
function(custom_setup_step)
endfunction()

function(custom_compile_step)
endfunction()" > Config/cmake/"${prjname}".cmake

  # We create a project file which will be used to configure our generated files
  touch uvproj.yaml && echo "\
name: \"${prjname}\"
version: \"1.0.0.0\"
engine-version: \"1.0.0.0\"
build-mode-static: false
build-mode-vendor: true
system-wide: false
enabled-modules:
  os: false
  dbus: false
  uexec: false
  theming: false
  ufont: false
  i18n: false
  undo-redo: false
  plotting: false
  knobs: false
  spinners: false
  toggles: false
  text-utils: false
  cli-parser: false
  xdg: false
  open: false" > uvproj.yaml

  # Create symbolic links
  if [ "${windows}" == true ]; then
    cmd //c mklink //d .\\Framework ..\\..\\Framework && cmd //c mklink //d .\\UVKBuildTool ..\\..\\UVKBuildTool && return
  fi
  ln -s "../../Framework/" Framework 2> /dev/null || cp -r ../../Framework .
  ln -s "../../UVKBuildTool/" UVKBuildTool 2> /dev/null || cp -r ../../UVKBuildTool .

  cp ../../example.gitignore .gitignore
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

    cp ../UVKBuildTool/build/Release/UVKBuildToolLib.dll . || exit
  elif [ "$2" == "wasm" ]; then
    emcmake cmake .. -DCMAKE_BUILD_TYPE=RELEASE || exit
    make -j "${cpus}" || exit
  else
    cmake .. -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=RELEASE || exit
    make -j "${cpus}" || exit
  fi
}

if [ "$1" != "" ]; then
  prjname="$1"
else
  read -rp "Enter your application's name: " prjname # read the project name
fi
prjname=${prjname/ /} # Remove any spaces if the name contains them
cpus=$(grep -c processor /proc/cpuinfo 2> /dev/null) || cpus=$(sysctl -n hw.ncpu) # get the cpu threads for maximum performance when compiling. The second command is for macOS systems if we even try to support them
echo -e "\x1B[32mCopiling with ${cpus} compute jobs!\033[0m"
find_visual_studio_directory
create_folders "${prjname}"
generate_files "${prjname}"
if [ "$2" != "--skip-compilation" ]; then
  compile "${prjname}" "$3"
fi

echo -e "\x1B[32mFramework and project successfully installed! \033[0m"
