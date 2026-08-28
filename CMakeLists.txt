cmake_minimum_required(VERSION 3.21.0)
project(todoapp LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets Svg)

qt_standard_project_setup()

qt_add_executable(${PROJECT_NAME}
  # i put ui-related files here for readability
  src/mainwindow.ui
  src/duedatepicker.ui
  src/cpbar.h
)

qt_add_resources(${PROJECT_NAME} "application_styles"
  PREFIX "/styles"
  BASE "${CMAKE_CURRENT_SOURCE_DIR}/resources"
  FILES
    "${CMAKE_CURRENT_SOURCE_DIR}/resources/app.qss"
)

target_include_directories(${PROJECT_NAME}
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_sources(${PROJECT_NAME}
  PRIVATE
  src/main.cpp
  src/mainwindow.h src/mainwindow.cpp
  # src/mainpage.h src/mainpage.cpp
  src/editbuttonswidget.h src/editbuttonswidget.cpp
  src/converter.h src/converter.cpp
  src/appstyle.h src/appstyle.cpp
  src/taskstore.h src/taskstore.cpp
  src/duedatepicker.h src/duedatepicker.cpp
  src/task.h
)

add_subdirectory(dep/qlementine)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        Qt::Core
        Qt::Widgets
        qlementine
)


# Source - https://stackoverflow.com/a/71635802
# Posted by qqNade
# Retrieved 2026-08-07, License - CC BY-SA 4.0

string(TOLOWER "${CMAKE_BUILD_TYPE}" build_type)
if (build_type STREQUAL "release")
    target_compile_definitions(${PROJECT_NAME} PUBLIC
        QT_NO_DEBUG_OUTPUT
        QT_NO_INFO_OUTPUT
        QT_NO_WARNING_OUTPUT
        )
endif()

# ------------- Installation and Deployment -------------
include(GNUInstallDirs)

if (APPLE)
  set_target_properties(${PROJECT_NAME} PROPERTIES
    MACOSX_BUNDLE TRUE
  )
endif()

if(WIN32)
  set_target_properties(${PROJECT_NAME} PROPERTIES
    WIN32_EXECUTABLE TRUE
  )
endif()

set(extra_deploy_plugins)

if(LINUX)
  set(extra_deploy_plugins qxcb qwayland)
endif()

install(TARGETS ${PROJECT_NAME}
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET ${PROJECT_NAME}
    OUTPUT_SCRIPT deploy_script
    # NO_UNSUPPORTED_PLATFORM_ERROR
    # INCLUDE_PLUGIN_TYPES platforms
    INCLUDE_PLUGINS ${extra_deploy_plugins}
)

install(SCRIPT ${deploy_script})
