set(HEADER_FILES binary.hpp
                 complex_utils.hpp
                 id_type_map.hpp
                 type_class_map.hpp
                 type_conversion.hpp
                 type_id_map.hpp
                 type_info.hpp
                 types.hpp
                 type_utils.hpp
                 container_trait.hpp
                 bool.hpp
                 none.hpp
                 unchecked_convertible.hpp
                 checked_convertible.hpp
                 convertible.hpp
                 )

install(FILES ${HEADER_FILES} 
        DESTINATION ${CMAKE_INSTALL_FULL_INCLUDEDIR}/pni/core/types)

