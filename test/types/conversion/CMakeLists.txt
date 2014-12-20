#need to define the version of the library
set(SOURCES conversion_test.cpp
            unchecked_convertible_test.cpp
            is_unchecked_convertible_to_test.cpp
    )


link_directories("${CMAKE_CURRENT_BINARY_DIR}/../../src")
add_executable(conversion_test ${SOURCES})
target_link_libraries(conversion_test pnicore ${CPPUNIT_LIBRARIES})


add_test(NAME "types:conversion_test" 
         COMMAND conversion_test
         )

