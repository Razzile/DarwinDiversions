#!/bin/bash

function help {
    echo "Help:"
    echo "$0 setup - setup build files"
    echo "$0 build - build project"
    echo "$0 clean - clean project"
}

MODE=$1

echo "This build script is not really meant for public use. It may work, it may not."

if [[ "$MODE" == "build" ]]; then
  cmake . -DCMAKE_BUILD_TYPE=Release -DBUILD_SHARED_LIBS=OFF -B./build
  make -C build
elif [[ "$MODE" == "clean" ]]; then
  make -C build clean
  rm -rf build/*
elif [[ "$MODE" == "generate" ]]; then
  cmake . -DCMAKE_EXPORT_COMPILE_COMMANDS=1 -B./build
  mv ./build/compile_commands.json ./compile_commands.json
fi
