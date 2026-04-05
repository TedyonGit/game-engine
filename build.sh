#!/bin/bash

case "$1" in
  linux)
    cmake -B build-linux
    cmake --build build-linux --config Release
    ;;
  windows)
    cmake -B build-win -DCMAKE_TOOLCHAIN_FILE=toolchain-mingw.cmake
    cmake --build build-win --config Release
    ;;
  clean)
    rm -rf build-linux build-win
    ;;
  *)
    echo "Usage: ./build.sh [linux|windows|clean]"
    ;;
esac