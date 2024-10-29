let
  pkgs = import <nixpkgs> {};
in
  pkgs.mkShell {
    buildInputs = with pkgs; [
        dbus
        webkitgtk
        openssl
        libxkbcommon
    ];
    nativeBuildInputs = with pkgs; [
        pkg-config
        cmake
        gnumake
        gdb
        rr
        yaml-cpp
        freetype
        glew
        glfw
        fontconfig
        shaderc
        glslang
        vulkan-headers
        vulkan-loader
        vulkan-validation-layers
        libxkbcommon
    ];
    dbus = pkgs.dbus;
    shellHook = ''
        export LD_LIBRARY_PATH=${pkgs.wayland}/lib:${pkgs.libxkbcommon}/lib:$LD_LIBRARY_PATH
    '';
  }
