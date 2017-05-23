add_executable(exception_record_test exception_record_test.cpp)
target_link_libraries(exception_record_test pnicore_shared
                     Boost::unit_test_framework)
target_compile_definitions(exception_record_test PRIVATE
         BOOST_TEST_DYN_LINK; BOOST_TEST_MODULE="testing exception record")

add_logging_test("Exceptions:exception_record_test" 
                 exception_record_test
                 ${PROJECT_BINARY_DIR}/test/exceptions)



add_executable(exception_test exception_test.cpp)
target_link_libraries(exception_test pnicore_shared
                      Boost::unit_test_framework)
target_compile_definitions(exception_test PRIVATE
    BOOST_TEST_DYN_LINK; BOOST_TEST_MODULE="testing the exception base class")

add_logging_test("Exceptions:exception_test" 
                 exception_test
                 ${PROJECT_BINARY_DIR}/test/exceptions)

if(CMAKE_HOST_SYSTEM_NAME MATCHES Windows)
    set_property(TEST "Exceptions:exception_test" APPEND PROPERTY
        ENVIRONMENT "PATH=${PATH_STRING}")
    set_property(TEST "Exceptions:exception_record_test" APPEND PROPERTY
        ENVIRONMENT "PATH=${PATH_STRING}")
endif()
