set(SOURCES exceptions.cpp
            exception_utils.cpp
            )

add_library(misc_objects OBJECT ${SOURCES})
set_property(TARGET misc_objects PROPERTY POSITION_INDEPENDENT_CODE ON)
target_include_directories(misc_objects PUBLIC 
                           $<BUILD_INTERFACE: ${Boost_INCLUDE_DIRS} ${PROJECT_SOURCE_DIR}/include> 
                           $<INSTALL_INTERFACE: ${CMAKE_INSTALL_INCLUDEDIR}>)

