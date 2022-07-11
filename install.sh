#!/bin/bash
VSVer=" "
VSShortVer="1"
VSType=" "
cpus=" "

# Used to automatically find and add the Visual Studio MSBuild.exe directory to the environment variables!
function find_visual_studio_directory()
{
  wdir=$(pwd)
  cd "C:/Program Files (x86)/Microsoft Visual Studio/" &> /dev/null || cd "C:/Program Files/Microsoft Visual Studio/" &> /dev/null || return
  VSVer=$(find "2022" -maxdepth 0 2> /dev/null) || VSVer=$(find "2019" -maxdepth 0 2> /dev/null) || VSVer=$(find "2017" -maxdepth 0 2> /dev/null) || (echo -e "\x1b[31mError: Couldn't find a compatible Visual Studio version! Please note that we only support Visual Studio 2017, 2019, 2022 or newer versions! Exiting!\x1b[0m" && exit)
  cd "${VSVer}" &> /dev/null || exit
  VSType=$(find "Community" -maxdepth 0 2> /dev/null) || VSType=$(find "Enterprise" -maxdepth 0 2> /dev/null) || VSType=$(find "Professional" -maxdepth 0 2> /dev/null) || (echo -e "'x1b[31mError: Couldn't find a compatible Visual Studio Version Type! Exiting!\x1b[0m" && exit)
  vspath=$(pwd)
  cd "${wdir}" || exit

  setx PATH "${vspath}/${VSType}/MSBuild/Current/Bin/amd64/;%PATH%" 2> /dev/null || (echo -e "\x1b[31mError: Couldn't set the path to the MSBuild.exe binary using setx! Try to set it yourself and try again without running the find Visual Studio option!\x1b[0m" && exit)
  if [ "$VSVer" == "2022" ]; then VSShortVer="17"
  elif [ "$VSVer" == "2019" ]; then VSShortVer="16"
  elif [ "$VSVer" == "2017" ]; then VSShortVer="15"
  else VSShortVer="1"
  fi
  return
}

# Installs the UVKBuildTool
function install_build_tool()
{
  cd UVKBuildTool/ || exit
  mkdir build || exit
  cd build || exit

  if [ "$1" == "ci" ]; then
    cmake .. -DUBT_COMPILING_FOR_ENGINE=OFF || exit
  else
    cmake .. -G "Visual Studio ${VSShortVer} ${VSVer}" -DUBT_COMPILING_FOR_ENGINE=OFF || cmake .. -G "Unix Makefiles" -DUBT_COMPILING_FOR_ENGINE=OFF || exit
  fi

  MSBuild.exe UVKBuildTool.sln -property:Configuration=Release -property:Platform=x64 -property:maxCpuCount="${cpus}" || make -j "${cpus}" || exit

  cp Release/UVKBuildTool.exe . 2> /dev/null
  cp Release/UVKBuildToolLib.dll . 2> /dev/null || cp Release/libUVKBuildToolLib.dll . 2> /dev/null
  cp Release/UVKBuildToolLib.lib . 2> /dev/null || cp Release/libUVKBuildToolLib.lib . 2> /dev/null
  cp yaml-cpp/Release/yaml-cpp.dll . 2> /dev/null || cp yaml-cpp/Release/libyaml-cpp.dll . 2> /dev/null
  cd ../../ || exit
  return
}

if [ "$1" == "" ]; then
  if find "C:/Program Files (x86)/Microsoft Visual Studio/" -maxdepth 0 2> /dev/null || find "C:/Program Files/Microsoft Visual Studio/" -maxdepth 0 2> /dev/null || which MSBuild.exe &> /dev/null; then
    while true; do
      read -rp "Are you running this script on a Windows system? Y(Yes)/N(No): " yn
      case $yn in
        [Yy]* ) echo -e "\x1b[31mWe couldn't find Visual Studio in the default installation under C:/Program Files/ or C:/Program Files (x86) and we couldn't find MSBuild.exe in the path.\nInstall the location of MSBuild.exe into your path environment variable, reopen your terminal and run the script again!\nMost of the times it's located under your visual-studio-install-directory/<year>/<type>/MSBuild/Current/Bin/amd64" && exit;;
        [Nn]* ) break;;
        * ) echo "Please answer with Y(Yes) or N(No)!";;
      esac
    done
  fi

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
cpus=$(grep -c processor /proc/cpuinfo) ## get the cpu threads for maximum performance when compiling
echo -e "\x1B[32mCopiling with ${cpus} compute jobs!\033[0m"

find_visual_studio_directory
mkdir Projects/
install_build_tool "$1"
echo -e "\x1b[32mFramework successfully installed!\x1b[0m"