set(HEADER_FILES mdarray.hpp
                 array_holder.hpp 
                 array_holder_interface.hpp 
                 array.hpp 
                 array_iterator.hpp 
                 array_operations.hpp 
                 array_selection.hpp 
                 arrays.hpp 
                 array_view.hpp 
                 array_view_selector.hpp 
                 binary.hpp 
                 complex_utils.hpp 
                 container_iterator.hpp 
                 container_utils.hpp
                 counter.hpp 
                 exceptions.hpp 
                 exception_utils.hpp 
                 id_type_map.hpp 
                 index_iterator.hpp 
                 numarray.hpp 
                 numarray_tags.hpp 
                 range_distributor.hpp 
                 scalar.hpp 
                 service.hpp 
                 slice.hpp 
                 type_class_map.hpp 
                 type_conversion.hpp 
                 type_id_map.hpp 
                 type_info.hpp 
                 types.hpp 
                 type_utils.hpp 
                 utilties.hpp 
                 value_holder.hpp 
                 value_holder_interface.hpp 
                 value.hpp value_ref.hpp)

install(FILES ${HEADER_FILES} 
        DESTINATION ${CMAKE_INSTALL_FULL_INCLUDEDIR}/pni/core/)

add_subdirectory("index_map")
add_subdirectory("benchmark")
add_subdirectory("config")
add_subdirectory("math")
