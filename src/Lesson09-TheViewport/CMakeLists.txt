cmake_minimum_required (VERSION 3.11)

# create project with provided name
project (Lesson09-TheViewport)

# set own defined version for the project
set (Lesson09-TheViewport_VERSION_MAJOR 1)
set (Lesson09-TheViewport_VERSION_MINOR 0)

add_executable(TheViewport "")

target_sources(TheViewport
    PUBLIC
        main.cpp
        types/drkrEventHandler.h
        types/drkrEventHandler.cpp
        types/drkrWindow.h
        types/drkrWindow.cpp
        ../../resources/h/enums.h
)