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

list(GET SOURCES 0 FIRST_SOURCE_FILE)
set_source_files_properties(${FIRST_SOURCE_FILE} PROPERTIES 
                            COMPILE_DEFINITIONS "BOOST_TEST_DYN_LINK; BOOST_TEST_MODULE=testing type traits")

add_executable(traits_test EXCLUDE_FROM_ALL ${SOURCES})
target_link_libraries(traits_test pnicore_shared
                                  ${Boost_UNIT_TEST_FRAMEWORK_SHARED_LIBRARY})



add_test(NAME "types:traits_test" 
         COMMAND traits_test
         )

add_dependencies(check traits_test)

