set(SOURCES array_selection.cpp slice.cpp)

include_directories(${Boost_INCLUDE_DIR})
add_library(array_objects OBJECT ${SOURCES})
