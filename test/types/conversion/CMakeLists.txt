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



link_directories("${CMAKE_CURRENT_BINARY_DIR}/../../src")
add_executable(conversion_test EXCLUDE_FROM_ALL ${SOURCES})
target_link_libraries(conversion_test pnicore)

if(CMAKE_CXX_COMPILER_ID MATCHES GNU)
    target_link_libraries(conversion_test ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})
endif()


add_test(NAME "types:conversion_test" 
         COMMAND conversion_test
         )

add_dependencies(check conversion_test)

