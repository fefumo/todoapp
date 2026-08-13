# Repository Guidelines

## Agent-Specific Instructions

Do not overwrite local user changes. Treat `dep/qlementine/` as third-party code, and keep repository-specific edits scoped to `src/`, `resources/`, scripts, or top-level build files unless instructed otherwise.

Do not change the files unless you are explicitly told to. In most cases I will only ask you some code-related questions. Not to write it yourself. However, suggestions are good. But only make them for files that I am currently working on.

## Project Structure & Module Organization

This is a Qt 6/CMake C++ desktop app. Application code lives in `src/`, with paired `.h` and `.cpp` files for widgets and pages such as `mainwindow`, `mainpage`, and `editpage`. Qt Designer UI markup is in `src/mainwindow.ui`. Runtime styling is in `resources/app.qss` and is registered through `CMakeLists.txt`. `dep/qlementine/` is a vendored UI dependency; avoid changing it unless the task specifically concerns that library. Top-level helper scripts (`prepare.sh`, `build.sh`, `run.sh`) wrap the common development flow.

## Build, Test, and Development Commands

- `./prepare.sh`: configure a Debug Ninja build, link `compile_commands.json`, and generate `.clang-format`/`.clangd` if needed.
- `./build.sh`: recreate `build/` and compile the `todoapp` target in Debug mode.
- `./run.sh`: rebuild the existing `build/` directory and launch `build/todoapp` with `QT_SCALE_FACTOR=1`.
- `cmake -S . -B build -G Ninja -DCMAKE_BUILD_TYPE=Debug`: configure manually when you need custom CMake options.
- `cmake --build build --parallel`: compile without running the app.

## Coding Style & Naming Conventions

Use C++ with Qt idioms and keep headers/sources paired by feature. The generated `.clang-format` uses Google style, so prefer two-space indentation, compact function definitions when readable, and include ordering handled by clang-format. Class names use `PascalCase` (`MainWindow`, `EditPage`), member variables use trailing underscores (`tabs_`, `editPage_`), and slots/signals use lower snake case (`goto_main_tab`, `task_saved`). Keep UI resource paths in CMake explicit and update `target_sources()` whenever adding new source files.
