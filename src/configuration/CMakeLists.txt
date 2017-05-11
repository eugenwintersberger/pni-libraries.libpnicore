set(SOURCES cli_args.cpp 
            config_parser.cpp 
            configuration.cpp)

add_library(configuration_objects OBJECT ${SOURCES})
set_property(TARGET configuration_objects PROPERTY POSITION_INDEPENDENT_CODE ON)
target_include_directories(configuration_objects INTERFACE ${Boost_INCLUDE_DIRS})
 
