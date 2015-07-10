#need to define the version of the library
set(SOURCES error_test.cpp check_equal_size_test.cpp 
            check_index_in_dim_test.cpp check_indexes_test.cpp 
            check_equal_rank_test.cpp
            check_equal_shape_test.cpp)


link_directories("${CMAKE_CURRENT_BINARY_DIR}/../../src")
add_executable(error_test EXCLUDE_FROM_ALL ${SOURCES} $<TARGET_OBJECTS:test_common>)

target_link_libraries(error_test pnicore)

if(CPPUNIT_FOUND)
    #add include directories
    include_directories(${CPPUNIT_INCLUDE_DIRS})

    #add libraries
    target_link_libraries(error_test ${CPPUNIT_LIBRARIES})

endif()

add_test(NAME error_test 
         COMMAND error_test
         WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/../
         )

