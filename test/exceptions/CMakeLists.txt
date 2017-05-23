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


#===============================================================================
add_executable(memory_allocation_error_test 
               memory_allocation_error_test.cpp)
target_link_libraries(memory_allocation_error_test PRIVATE
                      pnicore_shared
                      Boost::unit_test_framework)
target_compile_definitions(memory_allocation_error_test
                      PRIVATE
     BOOST_TEST_DYN_LINK; BOOST_TEST_MODULE="testing memory allocation error exception")
add_logging_test("Exceptions:memory_allocation_error"
                 memory_allocation_error_test
                 ${PROJECT_BINARY_DIR}/test/exceptions)

#===============================================================================
add_executable(memory_not_allocated_error_test 
               memory_not_allocated_error_test.cpp)
target_link_libraries(memory_not_allocated_error_test PRIVATE
                      pnicore_shared
                      Boost::unit_test_framework)
target_compile_definitions(memory_not_allocated_error_test
                      PRIVATE
     BOOST_TEST_DYN_LINK; BOOST_TEST_MODULE="testing memory not allocated exception")
add_logging_test("Exceptions:memory_not_allocated_error"
                 memory_not_allocated_error_test
                 ${PROJECT_BINARY_DIR}/test/exceptions)
