#!/usr/bin/env bash

# This file has to be run only once for development.

set -euo pipefail

BUILD_DIR="build"

cmake -S . -B "$BUILD_DIR" -G Ninja \
  -DCMAKE_BUILD_TYPE=Debug \
  -DCMAKE_EXPORT_COMPILE_COMMANDS=ON

ln -sf "$BUILD_DIR/compile_commands.json" compile_commands.json

clang-format -style=google -dump-config > .clang-format

if [ ! -f .clangd ]; then
  cat >.clangd <<'EOF'
CompileFlags:
  Remove:
    - -mno-direct-extern-access
EOF
fi
