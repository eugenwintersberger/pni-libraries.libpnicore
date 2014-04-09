
set(HEADER_FILES general.hpp math.hpp)

install(FILES ${HEADER_FILES} 
        DESTINATION ${CMAKE_INSTALL_FULL_INCLUDEDIR}/pni/core/algorithms)

add_subdirectory("math")
