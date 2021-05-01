set(SRCS
    m.c
    m_math.c
    util.c)

set(PUBLIC_HEADERS 
    coal.h
    m.h
    m_math.h
    util.h)

add_library(${LIBRARY_NAME} SHARED ${SRCS})

target_link_libraries(${LIBRARY_NAME} m)
set_target_properties(${LIBRARY_NAME} PROPERTIES PUBLIC_HEADER "${PUBLIC_HEADERS}")

message("Origin: ${ORIGIN}")
if (NOT DEFINED LIB_INSTALL_PREFIX)
    set(LIB_INSTALL_PREFIX lib)
endif()

install(TARGETS ${LIBRARY_NAME} 
    LIBRARY DESTINATION ${LIB_INSTALL_PREFIX})

if (NOT DEFINED LIB_ONLY)
    add_executable(demo coaltest.c)
    target_link_libraries(demo ${LIBRARY_NAME})
endif()

if (NOT DEFINED NO_HEADER_INSTALL)
    install(TARGETS ${LIBRARY_NAME} 
        PUBLIC_HEADER DESTINATION ${HEADER_INSTALL_PREFIX}${LIBRARY_NAME})
endif()

