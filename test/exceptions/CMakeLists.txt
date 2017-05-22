add_executable(exception_record_test exception_record_test.cpp)
target_link_libraries(exception_record_test pnicore_shared
                     Boost::unit_test_framework)
target_compile_definitions(exception_record_test PRIVATE
         BOOST_TEST_DYN_LINK; BOOST_TEST_MODULE="testing exception record")

add_test(NAME "Exceptions:exception_record_test"
         COMMAND exception_record_test ${TEST_OPTIONS}
                --log_sink=exception_record_test.log.xml
                --report_sink=exception_record_test.report.xml
         WORKING_DIRECTORY ${PROJECT_BINARY_DIR}/test/exceptions)


add_executable(exception_test exception_test.cpp)
target_link_libraries(exception_test pnicore_shared
                      Boost::unit_test_framework)
target_compile_definitions(exception_test PRIVATE
    BOOST_TEST_DYN_LINK; BOOST_TEST_MODULE="testing the exception base class")

add_test(NAME "Exceptions:exception_test"
         COMMAND exception_test ${TEST_OPTIONS} 
                 --log_sink=exception_test.log.xml 
                 --report_sink=exception_test.report.xml
         WORKING_DIRECTORY ${PROJECT_BINARY_DIR}/test/exceptions)

set(CLEAN_FILES exception_test.log.xml exception_test.report.xml
                exception_record_test.log.xml exception_record_test.report.xml)
set_directory_properties(PROPERTIES ADDITIONAL_MAKE_CLEAN_FILES
    "${CLEAN_FILES}")
         
