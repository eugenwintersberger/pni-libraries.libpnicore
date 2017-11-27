set(HEADER_FILES exceptions.hpp
                 exception_utils.hpp
                 )

install(FILES ${HEADER_FILES} 
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/pni/core/error
        COMPONENT development)
add_doxygen_source_deps(${HEADER_FILES})

