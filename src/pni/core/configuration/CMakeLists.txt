#
# manage header files
#
set(HEADER_FILES ${CMAKE_CURRENT_SOURCE_DIR}/cli_args.hpp 
                 ${CMAKE_CURRENT_SOURCE_DIR}/config_argument.hpp 
                 ${CMAKE_CURRENT_SOURCE_DIR}/config_option.hpp 
                 ${CMAKE_CURRENT_SOURCE_DIR}/config_parser.hpp 
                 ${CMAKE_CURRENT_SOURCE_DIR}/configuration.hpp 
                 )

install(FILES ${HEADER_FILES}
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/pni/core/configuration
        COMPONENT development)
add_doxygen_source_deps(${HEADER_FILES})

#
# build submodule
#
set(SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/cli_args.cpp 
            ${CMAKE_CURRENT_SOURCE_DIR}/config_parser.cpp 
            ${CMAKE_CURRENT_SOURCE_DIR}/configuration.cpp)

set(PNICORE_LIBRARY_SOURCES ${PNICORE_LIBRARY_SOURCES} ${SOURCES} PARENT_SCOPE)
set(PNICORE_LIBRARY_HEADERS ${PNICORE_LIBRARY_HEADERS} ${HEADER_FILES} PARENT_SCOPE)