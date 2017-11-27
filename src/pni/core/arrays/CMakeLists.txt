#
# manage header files
#

set(HEADER_FILES array_arithmetic.hpp
                 array_operations.hpp
                 array_selection.hpp
                 array_factory.hpp
                 array_view.hpp
                 array_view_utils.hpp
                 index_iterator.hpp
                 mdarray.hpp
                 scalar.hpp
                 scalar_iterator.hpp
                 slice.hpp
                 )

install(FILES ${HEADER_FILES} 
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/pni/core/arrays
        COMPONENT development)
add_doxygen_source_deps(${HEADER_FILES})
add_subdirectory("index_map")

#
# build submodule
#
set(SOURCES array_selection.cpp 
            slice.cpp)

add_library(array_objects OBJECT ${SOURCES})
set_property(TARGET array_objects PROPERTY POSITION_INDEPENDENT_CODE ON)
target_include_directories(array_objects PUBLIC
                           $<BUILD_INTERFACE: ${Boost_INCLUDE_DIRS} ${PROJECT_SOURCE_DIR}/include>
                           $<INSTALL_INTERFACE: ${CMAKE_INSTALL_INCLUDEDIR}>)

