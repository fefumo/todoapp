#!/usr/bin/env bash
set -euo pipefail

BUILD_DIR="build"

# -DCMAKE_BUILD_TYPE=Debug \
cmake -S . -B "$BUILD_DIR" -G Ninja \
  -DCMAKE_BUILD_TYPE=Debug \
  -DCMAKE_EXPORT_COMPILE_COMMANDS=ON

ln -sf "$BUILD_DIR/compile_commands.json" compile_commands.json

if [ ! -f .clangd ]; then
  cat >.clangd <<'EOF'
CompileFlags:
  Remove:
    - -mno-direct-extern-access
EOF
fi
