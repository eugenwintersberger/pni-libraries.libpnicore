#
# manage header files
#
set(HEADER_FILES binary.hpp
                 complex_utils.hpp
                 id_type_map.hpp
                 type_class_map.hpp
                 type_conversion.hpp
                 type_id_map.hpp
                 type_info.hpp
                 types.hpp
                 type_utils.hpp
                 container_trait.hpp
                 bool.hpp
                 none.hpp
                 unchecked_convertible.hpp
                 checked_convertible.hpp
                 convertible.hpp
                 convert.hpp
                 traits.hpp
                 )

install(FILES ${HEADER_FILES} 
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/pni/core/types
        COMPONENT development)
add_doxygen_source_deps(${HEADER_FILES})

#
# build submodule
#
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
target_include_directories(type_objects PUBLIC
                           $<BUILD_INTERFACE: ${Boost_INCLUDE_DIRS} ${PROJECT_SOURCE_DIR}/include>
                           $<INSTALL_INTERFACE: ${CMAKE_INSTALL_INCLUDEDIR}>)