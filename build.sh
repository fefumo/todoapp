#!/usr/bin/env bash
set -euo pipefail

BUILD_DIR="build"

if [[ -d "$BUILD_DIR" ]]; then
  rm -rf $BUILD_DIR
fi

# -DCMAKE_BUILD_TYPE=Release \
cmake -S . -B "$BUILD_DIR" -G Ninja \
  -DCMAKE_BUILD_TYPE=Debug \
  -DCMAKE_EXPORT_COMPILE_COMMANDS=ON

cmake --build "$BUILD_DIR" --parallel
