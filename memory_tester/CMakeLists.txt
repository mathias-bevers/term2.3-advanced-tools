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

add_executable(at_10_10k ${SOURCES} main.cpp)
target_compile_definitions(at_10_10k PRIVATE STREAM_ARRAY_SIZE=10 ITERATIONS=10000)
target_link_libraries(at_10_10k PRIVATE -static-libgcc -static-libstdc++ -static)

add_executable(at_10k_10k ${SOURCES} main.cpp)
target_compile_definitions(at_10k_10k PRIVATE STREAM_ARRAY_SIZE=10000 ITERATIONS=10000)
target_link_libraries(at_10k_10k PRIVATE -static-libgcc -static-libstdc++ -static)

add_executable(at_10m_10k ${SOURCES} main.cpp)
target_compile_definitions(at_10m_10k PRIVATE STREAM_ARRAY_SIZE=10000000 ITERATIONS=10000)
target_link_libraries(at_10m_10k PRIVATE -static-libgcc -static-libstdc++ -static)

add_executable(at_100m_10k ${SOURCES} main.cpp)
target_compile_definitions(at_100m_10k PRIVATE STREAM_ARRAY_SIZE=100000000 ITERATIONS=10000)
target_link_libraries(at_100m_10k PRIVATE -static-libgcc -static-libstdc++ -static)