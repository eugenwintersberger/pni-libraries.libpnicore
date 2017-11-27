set(HEADER_FILES container_iterator.hpp
                 container_utils.hpp
                 service.hpp
                 sfinae_macros.hpp
                 )

install(FILES ${HEADER_FILES} 
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/pni/core/utilities
        COMPONENT development)
add_doxygen_source_deps(${HEADER_FILES})
