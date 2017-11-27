#
# manage header files
#
set(HEADER_FILES ${CMAKE_CURRENT_SOURCE_DIR}/binary.hpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/complex_utils.hpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/id_type_map.hpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/type_class_map.hpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/type_conversion.hpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/type_id_map.hpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/type_info.hpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/types.hpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/type_utils.hpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/container_trait.hpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/bool.hpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/none.hpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/unchecked_convertible.hpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/checked_convertible.hpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/convertible.hpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/convert.hpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/traits.hpp
                 )

install(FILES ${HEADER_FILES} 
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/pni/core/types
        COMPONENT development)
add_doxygen_source_deps(${HEADER_FILES})

#
# build submodule
#
set(SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/bool.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/complex_utils.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/is_unchecked_convertible.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/is_checked_convertible.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/is_convertible.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/none.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/type_conversion.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/types.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/type_utils.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/traits.cpp
   )

set(PNICORE_LIBRARY_SOURCES ${PNICORE_LIBRARY_SOURCES} ${SOURCES} PARENT_SCOPE)
set(PNICORE_LIBRARY_HEADERS ${PNICORE_LIBRARY_HEADERS} ${HEADER_FILES} PARENT_SCOPE)