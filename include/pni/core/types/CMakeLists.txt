set(HEADER_FILES binary.hpp
                 id_type_map.hpp
                 type_class_map.hpp
                 type_conversion.hpp
                 type_id_map.hpp
                 type_info.hpp
                 types.hpp
                 type_utils.hpp
                 )

install(FILES ${HEADER_FILES} 
        DESTINATION ${CMAKE_INSTALL_FULL_INCLUDEDIR}/pni/core/types)

