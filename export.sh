#!/usr/bin/env bash
windows=false
macos=false

if [ "$(uname)" == "Darwin" ]; then
  macos=true
fi

oldpwd=$(pwd)

# Standard cleanup error handler. Should be used everywhere exit is used
# Gentoo Linux uses the "die" command so I'm not sure we should use just "die"
die_() {
  cd "${oldpwd}"
  # Remove framework since this is just a copy of the files from the framework folder
  ls "${oldpwd}"/Framework &> /dev/null && ls "${oldpwd}"/FrameworkSym &> /dev/null && rm -rf "${oldpwd}"/Framework

  # Make the framework symlink the real framework
  ls "${oldpwd}"/FrameworkSym &> /dev/null && mv "${oldpwd}"/FrameworkSym "${oldpwd}"Framework

  # Remove the exported folder and recreate it
  ls "${oldpwd}"/Exported &> /dev/null && rm -rf "${oldpwd}"/Exported && mkdir "${oldpwd}"/Exported

  # Rename the failing prod-export-specific "CMakeLists.txt" file to "CMakeLists.txt.prodexport.fail" and replace it with the old file
  ls "${oldpwd}"/CMakeLists.txt && ls "${oldpwd}"/CMakeLists.txt.old && mv "${oldpwd}"/CMakeLists.txt "${oldpwd}"/CMakeLists.txt.prodexport.fail && mv "${oldpwd}"/CMakeLists.txt.old "${oldpwd}"/CMakeLists.txt

  exit
}

function find_visual_studio_directory()
{
  env | grep "OS=Windows" > /dev/null && windows=true

  if [ "${windows}" = true ]; then
    wd=$(pwd)
    cd "C:/Program Files (x86)/Microsoft Visual Studio/Installer/" || die_
    find "vswhere.exe" -maxdepth 0 &> /dev/null || (cd "${wd}" && download_vswhere)

    VSShortVer=$(./vswhere.exe | grep "catalog_productLine: Dev17")
    VSShortVer="${VSShortVer:24}"

    VSVer=$(./vswhere.exe | grep "catalog_productLineVersion:")
    VSVer="${VSVer:28}"

    cd "${wd}" || die_
  fi

  return
}

function process_files()
{
  # Cleanup the directory
  rm -rf "CMake*" "Makefile" "*.cmake" &> /dev/null  # Remove all CMake files and Makefiles
  find . -name '*.cmake' -delete &> /dev/null && find . -type d -name "CMakeFiles" -exec rm -rf {} \; &> /dev/null # Remove remaining CMake files
  find Framework/ -name "Makefile" -exec rm -rf {} \; &> /dev/null && find Framework/ -name "*.h" -exec rm -rf {} \; &> /dev/null # Remove all headers
  find Framework/ -name "*.pc" -exec rm -rf {} \; &> /dev/null && find . -type d -empty -exec rmdir {} \; &> /dev/null # Remove all PCs and dirs
  find . -type d -name "docs" -exec rm -rf {} \; &> /dev/null && find . -type d -empty -exec rmdir {} \; &> /dev/null # Remove all docs folders
  find Framework/ -name "*.tcl" -exec rm -rf {} \; &> /dev/null && find . -name "*.txt" -exec rm -rf {} \; &> /dev/null  # Remove all PCs and dirs
  find . -name "*.vcxproj*" -exec rm -rf {} \; &> /dev/null # Delete all vcproj and filter files since they aren't needed
  find . -name "*.vcxproj" -exec rm -rf {} \; &> /dev/null # Delete all vcproj files
  find . -name "x64" -type d -exec rm -rf "{}" \; &> /dev/null # Delete all x64 folders, that contain logs
  find . -name "*.dir" -type d -exec rm -rf "{}" \; &> /dev/null # Delete all object file folders
  find . -name "*.sln" -exec rm -rf {} \; &> /dev/null # Delete all VS solution files
  cd .. || die_
}

function help()
{
  echo "The following script helps you export your project for production"
  echo "It's recommended that you don't run this script alone and use the UVKBuildTool"
  echo "Commands:"
  echo "  --help/help/-H/-h - displays this help message"
  echo "  <anything else> - would treat the argument as the name of a project and compile"
}

if [ "$1" = "" ]; then # If the first argument is empty throw an error and show help
  echo -e "\x1B[31mError: You cannot run the script without an additional argument!\033[0m"
  help
  die_
elif [ "$1" == "help" ] || [ "$1" == "-help" ] || [ "$1" == "--help" ] || [ "$1" == "-H" ] || [ "$1" == "-h" ]; then # shows the help message
  help
  die_
fi

function cmake_i()
{
  cmake -DUIMGUI_INSTALL=ON "$@" || die_
}

jobs=$(grep -c processor /proc/cpuinfo 2> /dev/null) || jobs=$(sysctl -n hw.ncpu)

real_framework_path=$(realpath Framework)
mv Framework FrameworkSym || die_
cp -r "${real_framework_path}" . || die_

while true; do
  if [ "$macos" = true ]; then
    cd Config/Resources || break
    iconutil -c icns Icon.iconset || break
    cd ../../ || break
  elif [ "$windows" = true ]; then
    cd Config/Resources || break
    whick magick && magick Icon.iconset/* Icon.ico
    cd ../../ || break
  fi
  break
done

cd Exported/ || die_

find_visual_studio_directory

if [ "$3" == "--system-wide" ]; then
  # This sets all options created with "option" in cmake to "ON". Build variant options are not affected because they are set using rules
  sed -i 's/" OFF)/" ON)/g' ../CMakeLists.txt
fi

if [ "${windows}" == true ]; then
  cmake_i .. -G "Visual Studio ${VSShortVer} ${VSVer}" -DCMAKE_BUILD_TYPE=RELEASE -DCMAKE_INSTALL_PREFIX="$2" "${@:4}" || die_
  MSBuild.exe "$1".sln -property:Configuration=Release -property:Platform=x64 -property:maxCpuCount="${jobs}" || die_
  cp Release/"$1".exe Release/*.dll . || die_
else
  cmake_i .. -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=RELEASE -DCMAKE_INSTALL_PREFIX="$2" "${@:4}" || die_
  make -j "${jobs}" || die_
fi

cmake --install . --prefix="$2" || die_

process_files "$1"
mv "CMakeLists.txt.old" "CMakeLists.txt"

rm -rf Framework || die_
mv FrameworkSym Framework || die_

echo -e "\x1B[32m--------------------------------------------------------------------------------\033[0m"
echo -e "\x1B[32mBuild Done!\033[0m"
