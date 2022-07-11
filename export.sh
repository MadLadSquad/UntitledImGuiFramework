#!/bin/bash
function find_visual_studio_directory()
{
  wdir=$(pwd)
  vsdir=$(which MSBuild.exe)
  cd "${vsdir}" || exit
  # go back from $vspath/$vstype/MSBuild/Current/Bin/amd64 to $vspath/../
  cd ../../../../../ || exit

  VSVer=$(find "2022" -maxdepth 0 2> /dev/null) || VSVer=$(find "2019" -maxdepth 0 2> /dev/null) || VSVer=$(find "2017" -maxdepth 0 2> /dev/null) || (echo -e "\x1b[31mError: Couldn't find a compatible Visual Studio version! Please note that we only support Visual Studio 2017, 2019, 2022 or newer versions! Exiting!\x1b[0m" && exit)
  cd "${VSVer}" &> /dev/null || exit
  VSType=$(find "Community" -maxdepth 0 2> /dev/null) || VSType=$(find "Enterprise" -maxdepth 0 2> /dev/null) || VSType=$(find "Professional" -maxdepth 0 2> /dev/null) || (echo -e "'x1b[31mError: Couldn't find a compatible Visual Studio Version Type! Exiting!\x1b[0m" && exit)
  cd "${wdir}" || exit

  if [ "$VSVer" == "2022" ]; then VSShortVer="17"
  elif [ "$VSVer" == "2019" ]; then VSShortVer="16"
  elif [ "$VSVer" == "2017" ]; then VSShortVer="15"
  else VSShortVer="1"
  fi
  return
}

function process_files()
{
  #(echo -e "\x1B[32mOpenAL32.dll required for this system!\033[0m" && cp Engine/ThirdParty/openal/Release/OpenAL32.dll . &> /dev/null) || echo -e "\x1B[32mOpenAL32.dll not required for this system!\033[0m"
  #(cp OpenAL32.dll Release/ &> /dev/null && echo -e "\x1B[32mSuccessfully installed OpenAL!\033[0m") || echo -e "\x1B[32mNo need to install OpenAL32!\033[0m"
  #cd ../Engine/ThirdParty/vulkan/ || exit # Change into the Vulkan directory which for some reason contains the needed libraries for Windows
  #(cp sndfile.dll ../../../Exported/ &> /dev/null && echo -e "\x1B[32msndfile.dll required for this system!\033[0m") || echo -e "\x1B[32msndfile.dll not required for this system!\033[0m" # Copy the sndfile.dll file (responsible for loading and operating with sound files)
  #cd ../../../Exported/ || exit # Go back into the build directory
  #(cp sndfile.dll Release/ &> /dev/null && echo -e "\x1B[32mInstalled sndfile.dll!\033[0m") || echo -e "\x1B[32mNo need to install sndfile.dll!\033[0m" # Finally copy the libraries to the Release folder because that is where Visual Studio builds
  cp Release/"$1".exe . &> /dev/null || echo -e "\x1B[32mProject Installed!\033[0m"
  cp Release/UntitledImGuiFramework.dll . &> /dev/null || echo -e "\x1B[32mEngine Installed!\x1B[0m"

  # Cleanup the directory
  rm -rf "CMake*" "Makefile" "*.cmake" &> /dev/null  # Remove all CMake files and Makefiles
  find . -name '*.cmake' -delete &> /dev/null && find . -type d -name "CMakeFiles" -exec rm -rf {} \; &> /dev/null # Remove remaining CMake files
  find Engine/ -name "Makefile" -exec rm -rf {} \; &> /dev/null && find Engine/ -name "*.h" -exec rm -rf {} \; &> /dev/null # Remove all headers
  find Engine/ -name "*.pc" -exec rm -rf {} \; &> /dev/null && find . -type d -empty -exec rmdir {} \; &> /dev/null # Remove all PCs and dirs
  find . -type d -name "docs" -exec rm -rf {} \; &> /dev/null && find . -type d -empty -exec rmdir {} \; &> /dev/null # Remove all docs folders
  find Engine/ -name "*.tcl" -exec rm -rf {} \; &> /dev/null && find . -name "*.txt" -exec rm -rf {} \; &> /dev/null  # Remove all PCs and dirs
  find . -name "*.vcxproj*" -exec rm -rf {} \; &> /dev/null # Delete all vcproj and filter files since they aren't needed
  find . -name "*.vcxproj" -exec rm -rf {} \; &> /dev/null # Delete all vcproj files
  find . -name "x64" -type d -exec rm -rf "{}" \; &> /dev/null # Delete all x64 folders, that contain logs
  find . -name "*.dir" -type d -exec rm -rf "{}" \; &> /dev/null # Delete all object file folders
  find . -name "*.sln" -exec rm -rf {} \; &> /dev/null # Delete all VS solution files
  cd .. || exit
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
  exit
elif [ "$1" == "help" ] || [ "$1" == "-help" ] || [ "$1" == "--help" ] || [ "$1" == "-H" ] || [ "$1" == "-h" ]; then # shows the help message
  help
  exit
fi

jobs=$(grep -c processor /proc/cpuinfo)
cd Exported/ || exit

find_visual_studio_directory

cmake .. -G "Visual Studio ${VSShortVer} ${VSVer}" || cmake .. -G "Unix Makefiles" || exit # Either cmake using VS or Make
MSBuild.exe "$1".sln -property:Configuration=Release -property:Platform=x64 -property:maxCpuCount="${jobs}" || make -j "${jobs}" || exit

process_files "$1"

echo -e "\x1B[32m--------------------------------------------------------------------------------\033[0m"
echo -e "\x1B[32mBuild Done!\033[0m"