set(HEADER_FILES core.hpp)

install(FILES ${HEADER_FILES} 
        DESTINATION ${CMAKE_INSTALL_FULL_INCLUDEDIR}/pni/)

 add_subdirectory("core")


