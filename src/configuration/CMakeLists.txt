set(SOURCES cli_args.cpp config_parser.cpp configuration.cpp)

include_directories(${Boost_INCLUDE_DIR})
add_library(configuration_objects OBJECT ${SOURCES})
