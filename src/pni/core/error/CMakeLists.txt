#
# manage header files
#
set(HEADER_FILES ${CMAKE_CURRENT_SOURCE_DIR}/exceptions.hpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/exception_utils.hpp
                 )

install(FILES ${HEADER_FILES} 
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/pni/core/error
        COMPONENT development)
add_doxygen_source_deps(${HEADER_FILES})

#
# build submodule
#
set(SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/exceptions.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/exception_utils.cpp
            )
set(PNICORE_LIBRARY_SOURCES ${PNICORE_LIBRARY_SOURCES} ${SOURCES} PARENT_SCOPE)
set(PNICORE_LIBRARY_HEADERS ${PNICORE_LIBRARY_HEADERS} ${HEADERS} PARENT_SCOPE)
