#
# manage header files
#
set(HEADER_FILES ${CMAKE_CURRENT_SOURCE_DIR}/array_holder.hpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/array_holder_interface.hpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/array.hpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/array_iterator.hpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/value_holder.hpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/value_holder_interface.hpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/value.hpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/value_ref.hpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/make_array.hpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/utils.hpp
                 )

install(FILES ${HEADER_FILES} 
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/pni/core/type_erasures
        COMPONENT development)
add_doxygen_source_deps(${HEADER_FILES})

#
# build submodule
# 
set(SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/array.cpp 
            ${CMAKE_CURRENT_SOURCE_DIR}/value.cpp 
            ${CMAKE_CURRENT_SOURCE_DIR}/value_ref.cpp )

set(PNICORE_LIBRARY_SOURCES ${PNICORE_LIBRARY_SOURCES} ${SOURCES} PARENT_SCOPE)
set(PNICORE_LIBRARY_HEADERS ${PNICORE_LIBRARY_HEADERS} ${HEADER_FILES} PARENT_SCOPE)
