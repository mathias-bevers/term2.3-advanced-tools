cmake_minimum_required(VERSION 3.27)
project(advanced_tools LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -mcmodel=medium")

file(GLOB_RECURSE SOURCES
        src/*.h
        src/*.cpp
        libraries/*.hpp
)

# create all the executables with different sizes and iterations

add_executable(at_i100_s10 ${SOURCES} main.cpp)
target_compile_definitions(at_i100_s10 PRIVATE STREAM_ARRAY_SIZE=10 ITERATIONS=100)
target_link_libraries(at_i100_s10 PRIVATE -static-libgcc -static-libstdc++ -static)

add_executable(at_i100_s10k ${SOURCES} main.cpp)
target_compile_definitions(at_i100_s10k PRIVATE STREAM_ARRAY_SIZE=10000 ITERATIONS=100)
target_link_libraries(at_i100_s10k PRIVATE -static-libgcc -static-libstdc++ -static)

add_executable(at_i100_s10m ${SOURCES} main.cpp)
target_compile_definitions(at_i100_s10m PRIVATE STREAM_ARRAY_SIZE=10000000 ITERATIONS=100)
target_link_libraries(at_i100_s10m PRIVATE -static-libgcc -static-libstdc++ -static)

add_executable(at_i100_s100m ${SOURCES} main.cpp)
target_compile_definitions(at_i100_s100m PRIVATE STREAM_ARRAY_SIZE=100000000 ITERATIONS=100)
target_link_libraries(at_i100_s100m PRIVATE -static-libgcc -static-libstdc++ -static)