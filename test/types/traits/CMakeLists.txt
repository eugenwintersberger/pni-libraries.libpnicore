#need to define the version of the library
set(SOURCES is_integer_type_test.cpp
            is_integer_test.cpp

            is_complex_test.cpp
            is_complex_type_test.cpp

            is_float_type_test.cpp
            is_float_test.cpp

            is_numeric_type_test.cpp
            is_numeric_test.cpp
            
            is_non_numeric_type_test.cpp
    )



link_directories("${CMAKE_CURRENT_BINARY_DIR}/../../src")
add_executable(traits_test EXCLUDE_FROM_ALL ${SOURCES})
target_link_libraries(traits_test pnicore ${CPPUNIT_LIBRARIES})


add_test(NAME "types:traits_test" 
         COMMAND traits_test
         )

add_dependencies(check traits_test)

