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

add_library(coal SHARED ${SRCS})
set_target_properties(coal PROPERTIES PUBLIC_HEADER "${PUBLIC_HEADERS}")

install(TARGETS coal 
    LIBRARY DESTINATION lib 
    PUBLIC_HEADER DESTINATION include/coal)

install(TARGETS coal 
    LIBRARY DESTINATION ${HOUDINI_TOOL_INS_DIR}/lib 
    PUBLIC_HEADER DESTINATION ${HOUDINI_TOOL_INS_DIR}/include/coal)
