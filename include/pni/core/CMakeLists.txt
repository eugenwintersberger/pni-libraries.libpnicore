set(HEADER_FILES array_holder.hpp 
                 array_holder_interface.hpp 
                 array.hpp 
                 array_iterator.hpp 
                 array_operations.hpp 
                 array_selection.hpp 
                 arrays.hpp 
                 array_view.hpp 
                 array_view_selector.hpp 
                 binary.hpp 
                 cindex_map.hpp 
                 c_index_policy.hpp 
                 complex_utils.hpp 
                 container_iterator.hpp 
                 counter.hpp 
                 darray.hpp 
                 exceptions.hpp 
                 exception_utils.hpp 
                 id_type_map.hpp 
                 index_iterator.hpp 
                 index_map_base.hpp 
                 new_allocator.hpp 
                 numarray.hpp 
                 numarray_tags.hpp 
                 range_distributor.hpp 
                 sarray.hpp 
                 scalar.hpp 
                 service.hpp 
                 size_type.hpp 
                 slice.hpp 
                 static_allocator.hpp 
                 static_cindex_map.hpp 
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

add_subdirectory("benchmark")
add_subdirectory("config")
add_subdirectory("math")
