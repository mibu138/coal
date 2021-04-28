set(SRCS
    coaltest.c
    m.c
    m_math.c
    util.c)

set(PUBLIC_HEADERS 
    coal.h
    m.h
    m_math.h
    util.h)

add_library(${LIBRARY_NAME} SHARED ${SRCS})
set_target_properties(${LIBRARY_NAME} PROPERTIES PUBLIC_HEADER "${PUBLIC_HEADERS}")

install(TARGETS ${LIBRARY_NAME} 
    LIBRARY DESTINATION ${LIB_INSTALL_PREFIX}lib 
    PUBLIC_HEADER DESTINATION ${HEADER_INSTALL_PREFIX}include/coal)
