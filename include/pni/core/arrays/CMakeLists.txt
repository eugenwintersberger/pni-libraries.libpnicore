
set(HEADER_FILES array_arithmetic.hpp
                 array_operations.hpp
                 array_selection.hpp
                 array_factory.hpp
                 array_view.hpp
                 array_view_utils.hpp
                 index_iterator.hpp
                 mdarray.hpp
                 scalar.hpp
                 scalar_iterator.hpp
                 slice.hpp
                 algorithms.hpp
                 )

install(FILES ${HEADER_FILES} 
        DESTINATION ${CMAKE_INSTALL_FULL_INCLUDEDIR}/pni/core/arrays)

add_subdirectory("index_map")
#add_subdirectory("dimension_layout")
add_subdirectory("math")
