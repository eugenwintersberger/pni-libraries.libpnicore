set(HEADER_FILES array_holder.hpp
                 array_holder_interface.hpp
                 array.hpp
                 array_iterator.hpp
                 value_holder.hpp
                 value_holder_interface.hpp
                 value.hpp
                 value_ref.hpp
                 make_array.hpp
                 )

install(FILES ${HEADER_FILES} 
        DESTINATION ${CMAKE_INSTALL_FULL_INCLUDEDIR}/pni/core/type_erasures)
