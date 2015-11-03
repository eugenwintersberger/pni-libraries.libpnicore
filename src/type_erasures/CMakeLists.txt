set(SOURCES array.cpp value.cpp value_ref.cpp )

include_directories(${Boost_INCLUDE_DIR})
add_library(type_erasure_objects OBJECT ${SOURCES})
