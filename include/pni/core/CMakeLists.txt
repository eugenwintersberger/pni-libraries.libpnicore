set(HEADER_FILES arrays.hpp
                 benchmark.hpp
                 configuration.hpp
                 types.hpp
                 utilities.hpp
                 error.hpp
                 type_erasures.hpp
                 algorithms.hpp
                 )

install(FILES ${HEADER_FILES} 
        DESTINATION ${CMAKE_INSTALL_FULL_INCLUDEDIR}/pni/core/)

add_subdirectory("algorithms")
add_subdirectory("arrays")
add_subdirectory("benchmark")
add_subdirectory("configuration")
add_subdirectory("types")
add_subdirectory("error")
add_subdirectory("utilities")
add_subdirectory("type_erasures")
