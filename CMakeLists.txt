cmake_minimum_required(VERSION 3.5)

project(deflash LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_executable(deflash
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    painter.cpp
    painter.h
    tool.h
    projectdialog.cpp
    projectdialog.h
    projectdialog.ui
    newprojectwizard.cpp
    newprojectwizard.h
    filepicker.cpp
    filepicker.h
    filepicker.ui
    config.cpp
    config.h
    animationframe.h
    animationframe.cpp
    version.h
    videoexporter.cpp
    videoexporter.h
)

target_link_libraries(deflash PRIVATE Qt5::Widgets)
