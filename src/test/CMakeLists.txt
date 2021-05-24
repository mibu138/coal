add_executable(vecAdd vecAdd.c)
target_link_libraries(vecAdd Coal::Coal)
target_include_directories(vecAdd PRIVATE "${CMAKE_SOURCE_DIR}/src/lib")
add_test(vector_addition vecAdd)

add_executable(dot dot.c)
target_link_libraries(dot Coal::Coal)
target_include_directories(dot PRIVATE "${CMAKE_SOURCE_DIR}/src/lib")
add_test(dot dot)
