#
# manage header files
#

set(HEADER_FILES ${CMAKE_CURRENT_SOURCE_DIR}/array_arithmetic.hpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/array_operations.hpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/array_selection.hpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/array_factory.hpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/array_view.hpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/array_view_utils.hpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/index_iterator.hpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/mdarray.hpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/scalar.hpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/scalar_iterator.hpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/slice.hpp
                 )

install(FILES ${HEADER_FILES} 
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/pni/core/arrays
        COMPONENT development)
add_doxygen_source_deps(${HEADER_FILES})
add_subdirectory("index_map")

#
# build submodule
#
set(SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/array_selection.cpp 
            ${CMAKE_CURRENT_SOURCE_DIR}/slice.cpp)

set(PNICORE_LIBRARY_SOURCES ${PNICORE_LIBRARY_SOURCES} ${SOURCES} PARENT_SCOPE)
set(PNICORE_LIBRARY_HEADERS ${PNICORE_LIBRARY_HEADERS} ${HEADER_FILES} PARENT_SCOPE)

