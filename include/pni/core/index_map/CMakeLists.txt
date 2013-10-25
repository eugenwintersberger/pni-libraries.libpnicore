set(HEADER_FILES c_index_policy_imp.hpp 
                 index_map.hpp 
                 index_maps.hpp 
                 index_policy.hpp 
                 static_index_map.hpp
                 index_map_common.hpp
                 )

install(FILES ${HEADER_FILES} 
        DESTINATION ${CMAKE_INSTALL_FULL_INCLUDEDIR}/pni/core/index_map)
