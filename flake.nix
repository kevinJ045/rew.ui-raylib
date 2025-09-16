{
  inputs = {
    utils.url = "github:numtide/flake-utils";
  };

  outputs = { self, nixpkgs, utils }:
    utils.lib.eachDefaultSystem (system:
      let
        pkgs = nixpkgs.legacyPackages.${system};
        libraries = with pkgs; [
          # Core toolchain
          # gcc
          # git
          cmake
          gnumake

          # Core graphics + rendering
          mesa
          libdrm
          libGL
          libGLU
          cairo
          libglvnd
          libxkbcommon
          fontconfig
          freetype
          zlib

          # X11
          # xorg.libX11
          # xorg.libXext
          # xorg.libXrandr
          # xorg.libXcursor
          # xorg.libXfixes
          # xorg.libXi
          # xorg.libXScrnSaver

          # Wayland
          # wayland
          # wayland-protocols
          # libdecor

          # Audio
          # alsa-lib
          # pulseaudio
          # pipewire
          # pipewire.jack

          # Input / misc
          # dbus
          # ibus
          # systemd
          # libusb1

          # EGL / GLES / Vulkan
          # vulkan-loader
          # vulkan-headers
          # vulkan-tools
          # vulkan-validation-layers
          # mesa.drivers
          # mesa.dev
          # mesa.gbmlib

          # Gstuff
          # glib
          # gvfs
          # gtk3
          # gtk4
          # gobject-introspection


          # Raylib
          raylib
          assimp
          assimp.dev
        ];
      in
      {
        devShell = pkgs.mkShell {
          buildInputs = libraries;
          nativeBuildInputs = [ pkgs.pkg-config ];

          shellHook = ''
            export LD_LIBRARY_PATH=/nix/store/2i2csri2c0kgp19f4jzv2f04ml6pg8y1-SDL2-2.30.2/lib:/nix/store/y2d2sxplgqckzzkkak31apasc3irixn7-SDL2_ttf-2.22.0/lib:${pkgs.lib.makeLibraryPath libraries}:$LD_LIBRARY_PATH
            echo "DevShell ready with full X11/Wayland/EGL/Vulkan/Audio stack"
          '';
        };
      }
    );
}
