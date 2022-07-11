# Used to automatically find and add the Visual Studio MSBuild.exe directory to the environment variables!
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

function create_folders()
{
  cd Projects/ || exit
  mkdir "$1" || echo "Project already exists!"
  cd "$1" || exit

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
  name: \"$1\"
  version: \"1.0.0.0\"
  engine-version: \"1.0.0\"" > uvproj.yaml

  # Create symbolic links
  ln -rs "../../Framework/" Framework 2> /dev/null || cp ../../Engine/ . -r
  ln -rs "../../UVKBuildTool/" UVKBuildTool 2> /dev/null || cp ../../UVKBuildTool/ . -r
}

function post_process_files()
{
  # cp Engine/ThirdParty/openal/Release/OpenAL32.dll . &> /dev/null
  # cp OpenAL32.dll Release/ &> /dev/null
  # cd ../Engine/ThirdParty/vulkan/ || exit # Go to the vulkan folder because there are a lot of libraries there
  # cp sndfile.dll ../../../build/ &> /dev/null
  # cd ../../../build/ || exit # Go back to the build folder
  # cp sndfile.dll Release/ &> /dev/null
  cp Release/"$1".exe . &> /dev/null
  cp ../UVKBuildTool/build/Release/UVKBuildToolLib.dll .
}

function generate_files()
{
  cd ../../UVKBuildTool/build || exit
  ./UVKBuildTool.exe --install "../../Projects/$1" || ./UVKBuildTool --install "../../Projects/$1" || exit
  cd "../../Projects/$1" || exit
}

function compile()
{
  cd build || exit
  if [ "$2" == "ci" ]; then
    cmake .. || exit
  else
    cmake .. -G "Visual Studio ${VSShortVer} ${VSVer}" || cmake .. -G "Unix Makefiles" || exit # Generate build files for the project
  fi
  MSBuild.exe "$1".sln -property:Configuration=Release -property:Platform=x64 -property:maxCpuCount="${cpus}" || make -j "${cpus}" || exit
}

if [ "$1" != "" ]; then
  prjname="$1"
else
  read -rp "Enter Your Application Name: " prjname # read the project name
fi
prjname=${prjname/ /} # Remove any spaces if the name contains them
cpus=$(grep -c processor /proc/cpuinfo) ## get the cpu threads for maximum performance when compiling
echo -e "\x1B[32mCopiling with ${cpus} compute jobs!\033[0m"
create_folders "${prjname}"
generate_files "${prjname}"
compile "${prjname}" "$2"
post_process_files "${prjname}"

echo -e "\x1B[32mFramework and project successfully installed! \033[0m"