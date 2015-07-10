#need to define the version of the library
set(SOURCES array_selection_test.cpp
            arrays_test.cpp
            array_view_test.cpp
            array_view_unary_arithmetic_test.cpp
            dynamic_mdarray_test.cpp
            fix_mdarray_test.cpp
            mdarray_test.cpp
            mdarray_unary_arithmetic_test.cpp
            scalar_test.cpp
            static_mdarray_test.cpp
            array_view_utils_test.cpp
    )


enable_testing()
link_directories("${CMAKE_CURRENT_BINARY_DIR}/../../src")
add_executable(arrays_test EXCLUDE_FROM_ALL ${SOURCES} $<TARGET_OBJECTS:test_common>)
target_link_libraries(arrays_test pnicore)

if(CPPUNIT_FOUND)
    #add include directories
    include_directories(${CPPUNIT_INCLUDE_DIRS})

    #add libraries
    target_link_libraries(arrays_test ${CPPUNIT_LIBRARIES})

endif()

add_test(NAME arrays_test 
         COMMAND arrays_test
         WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/../
         )


