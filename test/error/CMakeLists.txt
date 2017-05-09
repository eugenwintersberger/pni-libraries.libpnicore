#need to define the version of the library
set(SOURCES check_equal_size_test.cpp 
            check_index_in_dim_test.cpp 
            check_indexes_test.cpp 
            check_equal_rank_test.cpp
            check_equal_shape_test.cpp
            )

set_shared_test_defs(SOURCES "testing error functions")

add_executable(error_test EXCLUDE_FROM_ALL ${SOURCES} $<TARGET_OBJECTS:test_common>)
#target_compile_definitions(error_test PRIVATE "BOOST_TEST_DYN_LINK; BOOST_TEST_MODULE=testing error functions" )
target_link_libraries(error_test pnicore_shared
                                 ${Boost_UNIT_TEST_FRAMEWORK_SHARED_LIBRARY})


add_test(NAME error_test 
         COMMAND error_test
         WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/../
         )
add_dependencies(check error_test)

