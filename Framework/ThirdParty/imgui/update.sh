#!/bin/bash
git clone https://github.com/ocornut/imgui.git
cd imgui
git checkout docking

cp imgui* imstb* ../backends/everything/

cd backends/
cp imgui_impl_opengl3* imgui_impl_glfw* ../../backends/everything/
cp imgui_impl_vulkan* ../../backends/Vulkan

cd ../misc
rm -rf ../../misc/cpp ../../misc/fonts/ ../../misc/freetype
rm fonts/binary_to_compressed_c.cpp
mv cpp/ ../../misc/
mv fonts ../../misc/
mv freetype ../../misc/

cd ../../

rm -rf imgui/
