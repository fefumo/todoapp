cmake_minimum_required(VERSION 3.19)
project(todoapp LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)

qt_standard_project_setup()

qt_add_executable(todoapp
  src/main.cpp
  src/mainwindow.h src/mainwindow.cpp
  src/mainpage.h src/mainpage.cpp
  src/editpage.h src/editpage.cpp
  src/task.h src/task.cpp
  src/editbuttonswidget.h src/editbuttonswidget.cpp
)

qt_add_resources(todoapp "application_styles"
  PREFIX "/styles"
  BASE "${CMAKE_CURRENT_SOURCE_DIR}/resources"
  FILES
    "${CMAKE_CURRENT_SOURCE_DIR}/resources/app.qss"
)

target_sources(todoapp
  PRIVATE
    src/appstyle.cpp
    src/appstyle.h
)

target_link_libraries(todoapp
    PRIVATE
        Qt::Core
        Qt::Widgets
)

# target_include_directories(todoapp PRIVATE ${YOUR_DIRECTORY})

# ------------------------------------------------- DONT CARE RN --------------------------------------------------
install(TARGETS todoapp
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET todoapp
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
