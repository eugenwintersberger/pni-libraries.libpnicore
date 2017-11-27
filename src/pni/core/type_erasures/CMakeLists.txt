#
# manage header files
#
set(HEADER_FILES array_holder.hpp
                 array_holder_interface.hpp
                 array.hpp
                 array_iterator.hpp
                 value_holder.hpp
                 value_holder_interface.hpp
                 value.hpp
                 value_ref.hpp
                 make_array.hpp
                 utils.hpp
                 )

install(FILES ${HEADER_FILES} 
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/pni/core/type_erasures
        COMPONENT development)
add_doxygen_source_deps(${HEADER_FILES})

#
# build submodule
# 
set(SOURCES array.cpp value.cpp value_ref.cpp )

add_library(type_erasure_objects OBJECT ${SOURCES})
set_property(TARGET type_erasure_objects PROPERTY POSITION_INDEPENDENT_CODE ON)
target_include_directories(type_erasure_objects PUBLIC
                           $<BUILD_INTERFACE: ${Boost_INCLUDE_DIRS} ${PROJECT_SOURCE_DIR}/src>
                           $<INSTALL_INTERFACE: ${CMAKE_INSTALL_INCLUDEDIR}>)
