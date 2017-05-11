set(SOURCES array_selection.cpp 
            slice.cpp)

add_library(array_objects OBJECT ${SOURCES})
set_property(TARGET array_objects PROPERTY POSITION_INDEPENDENT_CODE ON)
target_include_directories(array_objects INTERFACE
                           ${Boost_INCLUDE_DIRS})

