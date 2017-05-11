set(SOURCES exceptions.cpp
            exception_utils.cpp
            )

add_library(misc_objects OBJECT ${SOURCES})
set_property(TARGET misc_objects PROPERTY POSITION_INDEPENDENT_CODE ON)
target_include_directories(misc_objects INTERFACE ${Boost_INCLUDE_DIRS})

