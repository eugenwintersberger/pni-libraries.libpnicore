set(HEADER_FILES cli_args.hpp 
                 config_argument.hpp 
                 config_option.hpp 
                 config_parser.hpp 
                 configuration.hpp 
                 )

install(FILES ${HEADER_FILES}
        DESTINATION ${CMAKE_INSTALL_FULL_INCLUDEDIR}/pni/core/configuration)
