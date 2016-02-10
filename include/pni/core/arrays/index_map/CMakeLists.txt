set(HEADER_FILES c_index_map_imp.hpp
                 index_map.hpp
                 index_maps.hpp
                 static_index_map.hpp
                 )

install(FILES ${HEADER_FILES} 
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/pni/core/arrays/index_map
        COMPONENT development)
