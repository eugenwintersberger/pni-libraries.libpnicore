set(HEADER_FILES arrays.hpp
                 benchmark.hpp
                 configuration.hpp
                 types.hpp
                 utilities.hpp
                 error.hpp
                 type_erasures.hpp
                 algorithms.hpp
                 windows.hpp
                 )

install(FILES ${HEADER_FILES} 
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/pni/core/
        COMPONENT development)
add_doxygen_source_deps(${HEADER_FILES})

add_subdirectory("algorithms")
add_subdirectory("arrays")
add_subdirectory("benchmark")
add_subdirectory("configuration")
add_subdirectory("types")
add_subdirectory("error")
add_subdirectory("utilities")
add_subdirectory("type_erasures")
