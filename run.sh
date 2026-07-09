#!/usr/bin/env bash
set -euo pipefail

BUILD_DIR="build"
TARGET="todoapp"

# cmake -S . -B "$BUILD_DIR" -G Ninja \
#   -DCMAKE_BUILD_TYPE=Debug \
#   -DCMAKE_EXPORT_COMPILE_COMMANDS=ON

cmake --build "$BUILD_DIR" --parallel

$BUILD_DIR/$TARGET
