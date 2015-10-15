#need to define the version of the library
set(SOURCES check_equal_size_test.cpp 
            check_index_in_dim_test.cpp 
            check_indexes_test.cpp 
            check_equal_rank_test.cpp
            check_equal_shape_test.cpp
            )


link_directories("${CMAKE_CURRENT_BINARY_DIR}/../../src")
add_executable(error_test EXCLUDE_FROM_ALL ${SOURCES} $<TARGET_OBJECTS:test_common>)

target_link_libraries(error_test pnicore ${Boost_LIBRARIES})

add_test(NAME error_test 
         COMMAND error_test
         WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/../
         )
add_dependencies(check error_test)

