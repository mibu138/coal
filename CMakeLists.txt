cmake_minimum_required(VERSION 3.17)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/cmake-common)

project(Coal VERSION 0.2.0)

include(header)
include(author_library)

add_subdirectory(cmake)
add_subdirectory(src/lib)
add_subdirectory(src/test)
