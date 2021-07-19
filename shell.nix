{ pkgs ? import <nixpkgs> {} }:

with pkgs;

mkShell {
  nativeBuildInputs = [ cmake ];
  buildInputs = [
    fuse
  ];
}
