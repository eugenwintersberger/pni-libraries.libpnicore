set(HEADER_FILES container_iterator.hpp
                 container_utils.hpp
                 service.hpp
                 )

install(FILES ${HEADER_FILES} 
        DESTINATION ${CMAKE_INSTALL_FULL_INCLUDEDIR}/pni/core/utilities)
