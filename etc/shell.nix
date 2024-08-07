# To get dependencies and build in a Nix environment:
#   1. Get the Nix package manager (https://nixos.org/download)
#   2. Invoke `nix-shell ./etc/shell.nix` in your shell. First invocation will
#      take around 5 minutes depending on your internet connection
#   3. `cd build`
#   4. `cmake $CMAKE_FLAGS ..`
{
  pkgs ? import (fetchTarball "https://github.com/NixOS/nixpkgs/archive/refs/tags/24.05.tar.gz") {}
}:
with pkgs; let
  # Default spdlog package uses external libfmt, which causes compile issues
  spdlog-internal-fmt = (spdlog.overrideAttrs(new: old: {
      cmakeFlags = builtins.filter (flag: (!lib.strings.hasPrefix "-DSPDLOG_FMT_EXTERNAL" flag)) old.cmakeFlags;
      doCheck = false;
  }));
in (mkShell.override { stdenv = clangStdenv; }) {
  # Runtime Dependencies
  buildInputs = [
    boost
    eigen
    tcl
    python3
    readline
    tclreadline
    libffi
    libsForQt5.qtbase
    llvmPackages.openmp
    spdlog-internal-fmt

    lemon-graph
    or-tools
    glpk
    zlib
    clp
    cbc
    re2
  ];

  # Compile-time Dependencies
  nativeBuildInputs = [
    swig4
    pkg-config
    cmake
    gnumake
    flex
    bison
  ];
  
  # Environment variable in resulting shell
  CMAKE_FLAGS = "-DUSE_SYSTEM_BOOST:BOOL=ON -DTCL_LIBRARY=${tcl}/lib/libtcl${stdenv.hostPlatform.extensions.sharedLibrary}";
}