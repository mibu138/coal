set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(srcs linalg.c util.c intersect.c)
add_library(coal)
target_sources(coal PRIVATE ${srcs})
target_include_directories(coal
    PRIVATE ../include/coal
    INTERFACE ../include)
if (NOT WIN32)
	target_link_libraries(coal PUBLIC m)
else()
	set_target_properties(coal PROPERTIES WINDOWS_EXPORT_ALL_SYMBOLS TRUE)
endif()
add_library(Coal::Coal ALIAS coal)

if(COAL_SIMPLE_TYPE_NAMES)
    target_compile_definitions(coal INTERFACE "COAL_SIMPLE_TYPE_NAMES")
endif()

if(COAL_SIMPLE_FUNC_NAMES)
    target_compile_definitions(coal INTERFACE "COAL_SIMPLE_TYPE_NAMES")
endif()

if(COAL_64_BIT_REAL)
    target_compile_definitions(coal INTERFACE "COAL_64_BIT_REAL")
endif()

target_compile_options(coal PRIVATE -Wall -Wextra
    -Wno-missing-field-initializers -Wno-missing-braces)
