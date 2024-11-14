cmake_minimum_required(VERSION 3.16)

project(fun_club VERSION 0.1 LANGUAGES CXX)

# Enable automatic processing for Qt modules
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

# Specify C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find Qt packages
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Sql Multimedia Network NetworkAuth WebEngineWidgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Sql Multimedia Network NetworkAuth WebEngineWidgets)

# Define include directories
include_directories(include Manager Widget)

# Automatically add all .cpp and .h files in the src and include directories
file(GLOB_RECURSE PROJECT_SOURCES
    "Manager/*.h"
    "Manager/*.cpp"
    "Manager/*.hpp"
    "Widget/*.h"
    "Widget/*.cpp"
    "Resource/FunClub.qrc"
    "main.cpp"
    "mainwindow.cpp"
    "mainwindow.h"
)

# Add executable or library based on Qt version and platform
if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(fun_club
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
else()
    if(ANDROID)
        add_library(fun_club SHARED ${PROJECT_SOURCES})
    else()
        add_executable(fun_club ${PROJECT_SOURCES})
    endif()
endif()

# Link Qt libraries
target_link_libraries(fun_club PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Sql
    Qt${QT_VERSION_MAJOR}::Multimedia
    Qt${QT_VERSION_MAJOR}::Network
    Qt${QT_VERSION_MAJOR}::NetworkAuth
    Qt${QT_VERSION_MAJOR}::WebEngineWidgets
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/elawidgettoolsd.lib
)

# Set properties for bundle and executable
if(${QT_VERSION} VERSION_LESS 6.1.0)
    set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.fun_club)
endif()

set_target_properties(fun_club PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

# Install rules
include(GNUInstallDirs)
install(TARGETS fun_club
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# Finalize executable for Qt 6
if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(fun_club)
endif()
