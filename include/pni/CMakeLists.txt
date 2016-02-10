set(HEADER_FILES core.hpp)

install(FILES ${HEADER_FILES} 
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/pni/
        COMPONENT development)

 add_subdirectory("core")


