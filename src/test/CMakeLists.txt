add_executable(vecAdd vecAdd.c)
target_link_libraries(vecAdd Coal::Coal)
add_test(vector_addition vecAdd)
