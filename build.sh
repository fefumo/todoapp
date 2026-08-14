#!/usr/bin/env bash
set -euo pipefail

BUILD_DIR="build"
APP_NAME="todoapp"
BUILD_DEBUG_DIR="build/debug"
BUILD_RELEASE_DIR="build/release"
PREFIX="dist"

usage() {
  cat <<'EOF'
Usage:
  ./build.sh --argument=<value>

Supported arguments:
  ./build.sh (-p) --prepare         Configure the project for development (set clangd, compile_commands)
  ./build.sh (-d) --debug           Build into build/debug
  ./build.sh (-r) --release         Build into build/release
  ./build.sh (-i) --install=<path>  Install into `path`. `./dist` by default
  ./build.sh (-dr) --run            Build and run debug build app (doesn't rebuild)
  ./build.sh (-c) --clean           Remove build and install(prefix) dirs (if any)
EOF
}

remove_build_dir() {
  rm -rf "$BUILD_DIR"
}
remove_prefix_dir() {
  rm -rf "$PREFIX"
}

debugbuild() {
  cmake -S . -B "$BUILD_DEBUG_DIR" -G Ninja \
    -DCMAKE_BUILD_TYPE=Debug \
    -DCMAKE_EXPORT_COMPILE_COMMANDS=ON

  cmake --build "$BUILD_DEBUG_DIR" --parallel
}

releasebuild() {
  cmake -S . -B "$BUILD_RELEASE_DIR" -G Ninja \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_EXPORT_COMPILE_COMMANDS=ON

  cmake --build "$BUILD_RELEASE_DIR" --parallel
}

run() {
  $BUILD_DEBUG_DIR/$APP_NAME
}

prepare() {
  ln -sf "$BUILD_DEBUG_DIR/compile_commands.json" compile_commands.json

  clang-format -style=google -dump-config >.clang-format

  if [ ! -f .clangd ]; then
    cat >.clangd <<'EOF'
CompileFlags:
  Remove:
    - -mno-direct-extern-access
EOF
  fi
  echo Preparation done
}

install() {
  echo Installing to "$PREFIX"
  releasebuild
  cmake --install "$BUILD_RELEASE_DIR" --prefix "$PREFIX"
}

if [[ $# -eq 0 ]]; then
  usage
  exit 0
fi

while [ "$1" != "" ]; do
  case $1 in
  -d | --debug)
    debugbuild
    shift
    ;;
  -r | --release)
    releasebuild
    shift
    ;;
  -c | --clean)
    remove_build_dir
    remove_prefix_dir
    echo Removed "$BUILD_DIR" and "$PREFIX" directories
    shift
    ;;
  -p | --prepare)
    prepare
    shift
    exit
    ;;
  -i=* | --install=*)
    PREFIX="${1#*=}"
    install
    shift 2
    ;;
  -h | --help)
    usage
    ;;
  -dr | --run)
    debugbuild
    run
    shift
    ;;
  *)
    echo "Unknown argument: $1"
    usage
    exit 1
    ;;
  esac
  shift
done
