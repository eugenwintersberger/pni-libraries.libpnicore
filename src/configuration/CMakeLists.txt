set(SOURCES cli_args.cpp 
            config_parser.cpp 
            configuration.cpp)

include_directories(${Boost_INCLUDE_DIR})

if(BUILD_SHARED_LIBRARIES)
    add_library(configuration_objects_shared OBJECT ${SOURCES})
    set_property(TARGET configuration_objects_shared PROPERTY 
                 POSITION_INDEPENDENT_CODE ON)
 endif(BUILD_SHARED_LIBRARIES)
 
if(BUILD_STATIC_LIBRARIES)
    add_library(configuration_objects_static OBJECT ${SOURCES})
    set_property(TARGET configuration_objects_static PROPERTY
                 POSITION_INDEPENDENT_CODE OFF)
endif(BUILD_STATIC_LIBRARIES)
