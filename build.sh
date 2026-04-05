#!/bin/bash

case "$1" in
  linux)
    cmake -B build-linux
    cmake --build build-linux --config Release
    cd build-linux/bin
    ./Sandbox
    cd ../../
    ;;
  windows)
    cmake -B build-win -DCMAKE_TOOLCHAIN_FILE=toolchain-mingw.cmake
    cmake --build build-win --config Release
    cd build-win/bin/
    wine Sandbox.exe
    cd ../../
    ;;
  clean)
    rm -rf build-win build-linux
    ;;
  *)
    echo "Usage: ./build.sh [linux|windows|clean]"
    ;;
esac
