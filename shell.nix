{ pkgs ? import <nixpkgs> {} }:

pkgs.mkShell {
  buildInputs = with pkgs; [
    gnumake
    libgcc
    libXext
    libX11
    minilibx
    zlib
  ];
}

