author_library(coal 
    EXPORT_NAME 
        Coal
    SOURCES
        linalg.c
        util.c
    PUBLIC_HEADERS
        coal.h
        linalg.h
        util.h
    DEPS
        m
        )

author_library(coalObj
    TYPE OBJECT
    EXPORT_NAME 
        CoalObj
    SOURCES
        linalg.c
        util.c
    DEPS
        m
        )
