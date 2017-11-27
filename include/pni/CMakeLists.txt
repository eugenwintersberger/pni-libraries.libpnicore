set(HEADER_FILES core.hpp)

install(FILES ${HEADER_FILES} 
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/pni/
        COMPONENT development)
add_doxygen_source_deps(${HEADER_FILES})

 add_subdirectory("core")


