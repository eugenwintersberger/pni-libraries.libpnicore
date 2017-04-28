set(SOURCES array_selection.cpp 
            slice.cpp)

include_directories(${Boost_INCLUDE_DIR})

# build module for shared library 
if(BUILD_SHARED_LIBRARIES)
    add_library(array_objects_shared OBJECT ${SOURCES})
    set_property(TARGET array_objects_shared PROPERTY POSITION_INDEPENDENT_CODE ON)
endif(BUILD_SHARED_LIBRARIES)

# build module for static library
if(BUILD_STATIC_LIBRARIES)
    add_library(array_objects_static OBJECT ${SOURCES})
    set_property(TARGET array_objects_static PROPERTY POSITION_INDEPENDENT_CODE OFF)
endif(BUILD_STATIC_LIBRARIES)
