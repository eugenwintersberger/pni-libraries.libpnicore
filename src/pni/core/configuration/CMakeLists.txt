#
# manage header files
#
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

#
# build submodule
#
set(SOURCES cli_args.cpp 
            config_parser.cpp 
            configuration.cpp)

add_library(configuration_objects OBJECT ${SOURCES})
set_property(TARGET configuration_objects PROPERTY POSITION_INDEPENDENT_CODE ON)
target_include_directories(configuration_objects PUBLIC
                           $<BUILD_INTERFACE: ${Boost_INCLUDE_DIRS} ${PROJECT_SOURCE_DIR}/src>
                           $<INSTALL_INTERFACE: ${CMAKE_INSTALL_INCLUDEDIR}>)