set(SOURCES bool.cpp
            complex_utils.cpp
            is_unchecked_convertible.cpp
            none.cpp
            type_conversion.cpp
            types.cpp
            type_utils.cpp
   )

add_library(type_objects OBJECT ${SOURCES})
