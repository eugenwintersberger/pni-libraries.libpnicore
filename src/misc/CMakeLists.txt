set(SOURCES exceptions.cpp
            exception_utils.cpp
            )

include_directories(${Boost_INCLUDE_DIR})
add_library(misc_objects OBJECT ${SOURCES})
