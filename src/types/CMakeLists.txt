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

add_library(type_objects OBJECT ${SOURCES})
set_property(TARGET type_objects PROPERTY POSITION_INDEPENDENT_CODE ON)
target_include_directories(type_objects INTERFACE
                           ${Boost_INCLUDE_DIRS})

