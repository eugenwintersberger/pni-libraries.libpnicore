add_executable(exception_record_test exception_record_test.cpp)
target_link_libraries(exception_record_test pnicore_shared
                     Boost::unit_test_framework)
target_compile_definitions(exception_record_test PRIVATE
         BOOST_TEST_DYN_LINK; BOOST_TEST_MODULE="testing exception record")

add_test(NAME "Exceptions:exception_record_test"
         COMMAND exception_record_test
         WORKING_DIRECTORY ${PROJECT_BINARY_DIR}/test/exceptions)

         
