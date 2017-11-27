
set(HEADER_FILES  math.hpp)

install(FILES ${HEADER_FILES} 
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/pni/core/algorithms
        COMPONENT development)
add_doxygen_source_deps(${HEADER_FILES})

add_subdirectory("math")
