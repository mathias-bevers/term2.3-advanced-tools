cmake_minimum_required(VERSION 3.27)
project(advanced_tools)

set(CMAKE_CXX_STANDARD 17)
file(GLOB_RECURSE SOURCES
        src/*.h
        src/*.cpp
)

add_executable(advanced_tools ${SOURCE_FILES} ${SOURCES} main.cpp)