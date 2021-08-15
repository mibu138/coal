cmake_minimum_required(VERSION 3.17)

project(Coal VERSION 0.2.0)

option(COAL_SKIP_TESTS "Skip building tests." OFF)
option(COAL_ENABLE_TESTING "Enables Ctest." ON)
option(COAL_SIMPLE_TYPE_NAMES "Enables simple type names." OFF)

if(COAL_ENABLE_TESTING)
    enable_testing()
endif()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(WIN32)
	set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
	set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
endif()

add_subdirectory(src/lib)
add_subdirectory(src/test)
