set(SOURCES array.cpp value.cpp value_ref.cpp )

add_library(type_erasure_objects OBJECT ${SOURCES})
set_property(TARGET type_erasure_objects PROPERTY POSITION_INDEPENDENT_CODE ON)
target_include_directories(type_erasure_objects INTERFACE
                           ${Boost_INCLUDE_DIRS})

