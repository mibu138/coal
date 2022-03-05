if(NOT COAL_SKIP_TESTS)

function(coal_test name)
    add_executable(${name}_exe)
    target_sources(${name}_exe PRIVATE ${name}.c)
    target_link_libraries(${name}_exe PRIVATE Coal::Coal)
    target_compile_definitions(${name}_exe PUBLIC COAL_SIMPLE_TYPE_NAMES
        COAL_SIMPLE_FUNC_NAMES)
    add_test(${name} ${name}_exe)
endfunction()

coal_test(cross)
coal_test(dot)
coal_test(vecAdd)
coal_test(generics)

endif()
