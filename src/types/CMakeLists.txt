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
add_library(type_objects OBJECT ${SOURCES})
