#!/usr/bin/env bash
set -euo pipefail

BUILD_DIR="build"
TARGET="todoapp"

cmake --build "$BUILD_DIR" --parallel

QT_SCALE_FACTOR=1 $BUILD_DIR/$TARGET
