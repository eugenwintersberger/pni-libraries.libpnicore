set(HEADER_FILES container_iterator.hpp
                 container_utils.hpp
                 counter.hpp
                 service.hpp
                 vector_adapter.hpp
                 )

install(FILES ${HEADER_FILES} 
        DESTINATION ${CMAKE_INSTALL_FULL_INCLUDEDIR}/pni/core/utilities)
