#need to define the version of the library
set(SOURCES unchecked_convertible_test.cpp
            is_unchecked_convertible_test.cpp
            is_checked_convertible_test.cpp
            is_convertible_test.cpp
            checked_convertible_test.cpp
            convert_uint8_test.cpp
            convert_uint16_test.cpp
            convert_uint32_test.cpp
            convert_uint64_test.cpp
            convert_int8_test.cpp
            convert_int16_test.cpp
            convert_int32_test.cpp
            convert_int64_test.cpp
            convert_float32_test.cpp
            convert_float64_test.cpp
            convert_float128_test.cpp
            convert_complex32_test.cpp
            convert_complex64_test.cpp
            convert_complex128_test.cpp
    )


list(GET SOURCES 0 FIRST_SOURCE_FILE)
set_source_files_properties(${FIRST_SOURCE_FILE} PROPERTIES 
                            COMPILE_DEFINITIONS "BOOST_TEST_DYN_LINK; BOOST_TEST_MODULE=Testing type conversion")
add_executable(conversion_test EXCLUDE_FROM_ALL ${SOURCES})
target_link_libraries(conversion_test pnicore_shared
                                      ${Boost_UNIT_TEST_FRAMEWORK_SHARED_LIBRARY})


add_test(NAME "types:conversion_test" 
         COMMAND conversion_test
         )

add_dependencies(check conversion_test)

