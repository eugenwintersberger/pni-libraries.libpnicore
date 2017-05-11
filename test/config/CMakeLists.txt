#need to define the version of the library
set(SOURCES  configuration_test.cpp)

set_shared_test_defs(SOURCES "testing the configuration facilities")
add_executable(config_test ${SOURCES} $<TARGET_OBJECTS:test_common>)
target_link_libraries(config_test pnicore_shared
                                  ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})

configure_file(pni.cfg.cmake pni.cfg)

add_test(NAME config_test 
         COMMAND config_test
         WORKING_DIRECTORY ${PROJECT_BINARY_DIR}/test
         )
         
if(CMAKE_HOST_SYSTEM_NAME MATCHES Windows)
    set_property(TEST config_test APPEND PROPERTY
                 ENVIRONMENT "PATH=${PATH_STRING}")
endif()
    
