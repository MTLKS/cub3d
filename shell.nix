{ pkgs ? import <nixpkgs> {} }:

pkgs.mkShell {
  buildInputs = with pkgs; [
    gnumake
    libgcc
    xorg.libXext
    xorg.libX11
    minilibx
  ];
}

