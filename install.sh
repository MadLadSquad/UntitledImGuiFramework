#!/bin/bash
VSVer=" "
VSShortVer="1"
cpus=" "
windows=false

oldpwd=$(pwd)

# Standard cleanup error handler. Should be used everywhere exit is used
# Gentoo Linux uses the die command so I'm not sure we should use just die
die_() {
  rm -rf "${oldpwd}"/Projects &> /dev/null
  rm -rf "${oldpwd}"/UVKBuildTool/build &> /dev/null
  exit
}

download_vswhere() {
  # Get the raw JSON code for the releases from Github, get the lines that have the browser download URL and truncate the string in the front and back
  # to get the URL, then we use the URL to download the application, this only happens if we cannot find
  line=$(curl https://api.github.com/repos/microsoft/vswhere/releases 2> /dev/null | grep "https://github.com/microsoft/vswhere/releases/download/")
  line="${line:33}"
  line="${line%\"*}"

  # Set a fake user agent string here so that we evade being blocked by GitHub
  curl "${line}" -L -A "Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:106.0) Gecko/20100101 Firefox/106.0" -o vswhere.exe
}


# Used to automatically find and add the Visual Studio MSBuild.exe directory to the environment variables!
function find_visual_studio_directory()
{
  env | grep "OS=Windows" > /dev/null && windows=true

  if [ "${windows}" = true ]; then
    wd=$(pwd)
    cd "C:/Program Files (x86)/Microsoft Visual Studio/Installer/" || die_
    find "vswhere.exe" -maxdepth 0 &> /dev/null || (cd "${wd}" && download_vswhere)
    vs_path=$(./vswhere.exe | grep "installationPath")
    vs_path="${vs_path:18}"

    VSShortVer=$(./vswhere.exe | grep "catalog_productLine: Dev17")
    VSShortVer="${VSShortVer:24}"

    VSVer=$(./vswhere.exe | grep "catalog_productLineVersion:")
    VSVer="${VSVer:28}"

    setx PATH "${vs_path}/MSBuild/Current/Bin/amd64/;%PATH%" 2> /dev/null
    cd "${wd}" || die_
  fi

  return
}

# Installs the UVKBuildTool
function install_build_tool()
{
  cd UVKBuildTool/ || die_
  mkdir build || die_
  cd build || die_

  if [ "${windows}" == true ]; then
    cmake .. -G "Visual Studio ${VSShortVer} ${VSVer}" -DUBT_COMPILING_FOR_WEB=OFF -DCMAKE_BUILD_TYPE=RELEASE || die_
    MSBuild.exe UVKBuildTool.sln -property:Configuration=Release -property:Platform=x64 -property:maxCpuCount="${cpus}" || die_

    cp Release/UVKBuildTool.exe . &> /dev/null
    cp Release/*.dll . &> /dev/null
  else
    cmake .. -G "Unix Makefiles" -DUBT_COMPILING_FOR_WEB=OFF -DCMAKE_BUILD_TYPE=RELEASE || die_
    make -j "${cpus}" || die_
  fi

  cd ../../ || die_
  return
}

if [ "$1" == "" ]; then
  while true; do
    read -rp "Start installation? Y(Yes)/N(No): " yn
    case $yn in
       [Yy]* ) break;;
       [Nn]* ) exit;;
       * ) echo "Please answer with Y(Yes) or N(No)!";;
    esac
  done

  while true; do
    read -rp "Do you want to download offline documentation Y(Yes)/N(No): " yn
    case $yn in
       [Yy]* ) git clone https://github.com/MadLadSquad/UntitledImGuiFramework.wiki.git docs/; break;;
       [Nn]* ) break;;
       * ) echo "Please answer with Y(Yes) or N(No)!";;
    esac
  done
fi
cpus=$(grep -c processor /proc/cpuinfo) || cpus=$(sysctl -n hw.ncpu) # get the cpu threads for maximum performance when compiling
echo -e "\x1B[32mCopiling with ${cpus} compute jobs!\033[0m"

find_visual_studio_directory
mkdir Projects/
install_build_tool "$1"

echo -e "\x1b[32mFramework successfully installed!\x1b[0m"
