cmake_minimum_required(VERSION 3.17)

project(Coal VERSION 0.2.0)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(WIN32)
	set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
	set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
endif()

add_subdirectory(src/lib)
add_subdirectory(src/test)
