set(srcs linalg.c util.c)
add_library(coalObj    OBJECT)
add_library(coal       SHARED)
target_sources(coalObj PRIVATE ${srcs})
target_include_directories(coalObj 
    PRIVATE ../include/coal
    INTERFACE ../include)
target_link_libraries(coalObj INTERFACE m)
target_link_libraries(coal PUBLIC Coal::CoalObj)
add_library(Coal::Coal    ALIAS coal)
add_library(Coal::CoalObj ALIAS coalObj)
