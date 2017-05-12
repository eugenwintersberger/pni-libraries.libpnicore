set(SOURCES cli_args.cpp 
            config_parser.cpp 
            configuration.cpp)

add_library(configuration_objects OBJECT ${SOURCES})
set_property(TARGET configuration_objects PROPERTY POSITION_INDEPENDENT_CODE ON)
target_include_directories(configuration_objects PUBLIC
                           $<BUILD_INTERFACE: ${Boost_INCLUDE_DIRS} ${PROJECT_SOURCE_DIR}/include>
                           $<INSTALL_INTERFACE: ${CMAKE_INSTALL_INCLUDEDIR}>)
target_compiler_features(configuration_objects PRIVATE cxx_std_11)                           
 
