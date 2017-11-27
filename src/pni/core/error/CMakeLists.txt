#
# manage header files
#
set(HEADER_FILES exceptions.hpp
                 exception_utils.hpp
                 )

install(FILES ${HEADER_FILES} 
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/pni/core/error
        COMPONENT development)
add_doxygen_source_deps(${HEADER_FILES})

#
# build submodule
#
set(SOURCES exceptions.cpp
            exception_utils.cpp
            )

add_library(misc_objects OBJECT ${SOURCES})
set_property(TARGET misc_objects PROPERTY POSITION_INDEPENDENT_CODE ON)
target_include_directories(misc_objects PUBLIC 
                           $<BUILD_INTERFACE: ${Boost_INCLUDE_DIRS} ${PROJECT_SOURCE_DIR}/src> 
                           $<INSTALL_INTERFACE: ${CMAKE_INSTALL_INCLUDEDIR}>)