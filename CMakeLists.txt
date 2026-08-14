cmake_minimum_required(VERSION 3.19)
project(todoapp LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets Svg)

qt_standard_project_setup()

qt_add_executable(${PROJECT_NAME}
  # i put ui-related files here for readability
  src/mainwindow.ui
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
  src/mainpage.h src/mainpage.cpp
  src/editpage.h src/editpage.cpp
  src/editbuttonswidget.h src/editbuttonswidget.cpp
  src/converter.h src/converter.cpp
  src/appstyle.h src/appstyle.cpp
)

add_subdirectory(dep/qlementine)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        Qt::Core
        Qt::Widgets
        qlementine
)


# add_library(qlementine STATIC IMPORTED)

# set_target_properties(qlementine PROPERTIES
#   IMPORTED_LOCATION "${CMAKE_SOURCE_DIR}/dep/qlementine/build/lib/libqlementine.a"
#   INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_SOURCE_DIR}/dep/qlementine/lib/include"
# )

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

# ------------------------------------------------- DONT CARE RN (idk what id does tbh) --------------------------------------------------
install(TARGETS ${PROJECT_NAME}
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET ${PROJECT_NAME}
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
