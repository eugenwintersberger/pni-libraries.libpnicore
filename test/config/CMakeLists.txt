#need to define the version of the library
set(SOURCES  configuration_test.cpp)

if(BUILD_SHARED_LIBRARIES)
    set_shared_test_defs(SOURCES "testing the configuration facilities")
    add_executable(config_test EXCLUDE_FROM_ALL ${SOURCES} $<TARGET_OBJECTS:test_common>)
    target_link_libraries(config_test pnicore_shared
                                      ${Boost_UNIT_TEST_FRAMEWORK_SHARED_LIBRARY})


    configure_file(pni.cfg.cmake pni.cfg)

    add_test(NAME config_test 
             COMMAND config_test
             WORKING_DIRECTORY ${PROJECT_BINARY_DIR}/test
             )

    add_dependencies(check config_test)
endif(BUILD_SHARED_LIBRARIES)
