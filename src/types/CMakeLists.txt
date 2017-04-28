set(SOURCES bool.cpp
            complex_utils.cpp
            is_unchecked_convertible.cpp
            is_checked_convertible.cpp
            is_convertible.cpp
            none.cpp
            type_conversion.cpp
            types.cpp
            type_utils.cpp
            traits.cpp
   )

include_directories(${Boost_INCLUDE_DIR})

if(BUILD_SHARED_LIBRARIES)
    add_library(type_objects_shared OBJECT ${SOURCES})
    set_property(TARGET type_objects_shared PROPERTY
                 POSITION_INDEPENDENT_CODE ON)
endif(BUILD_SHARED_LIBRARIES)

if(BUILD_STATIC_LIBRARIES)
    add_library(type_objects_static OBJECT ${SOURCES})
    set_property(TARGET type_objects_static PROPERTY
                 POSITION_INDEPENDENT_CODE OFF)
endif(BUILD_STATIC_LIBRARIES)
