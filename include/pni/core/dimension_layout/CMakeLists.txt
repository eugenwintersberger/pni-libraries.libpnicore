set(HEADER_FILES 
                algorithms.hpp
                dynamic_dim_layout.hpp
                static_dim_layout.hpp
                dimension_layout.hpp
                 )

install(FILES ${HEADER_FILES} 
        DESTINATION ${CMAKE_INSTALL_FULL_INCLUDEDIR}/pni/core/dimension_layout)
