set(HEADER_FILES cli_args.hpp 
                 config_argument.hpp 
                 config_option.hpp 
                 config_parser.hpp 
                 configuration.hpp 
                 )

install(FILES ${HEADER_FILES}
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/pni/core/configuration
        COMPONENT development)
add_doxygen_source_deps(${HEADER_FILES})
