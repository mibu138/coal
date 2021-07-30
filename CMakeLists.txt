cmake_minimum_required(VERSION 3.17)

project(Coal VERSION 0.2.0)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(src/lib)
add_subdirectory(src/test)
