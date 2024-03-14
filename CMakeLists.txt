cmake_minimum_required(VERSION 3.27)
project(advanced_tools)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -mcmodel=medium")


file(GLOB_RECURSE SOURCES
        src/*.h
        src/*.cpp
        libraries/*.hpp
)

add_executable(advanced_tools ${SOURCE_FILES} ${SOURCES} main.cpp)