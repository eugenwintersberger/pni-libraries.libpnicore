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


if(BUILD_SHARED_LIBRARIES)
    set_shared_test_defs(SOURCES "Testing type conversions")
    add_executable(conversion_test ${SOURCES})
    target_link_libraries(conversion_test pnicore_shared
                                          ${Boost_UNIT_TEST_FRAMEWORK_SHARED_LIBRARY})

    add_test(NAME "types:conversion_test" 
             COMMAND conversion_test
             WORKING_DIRECTORY ${PROJECT_BINARY_DIR}/test
             )
             
    if(CMAKE_CXX_COMPILER_ID MATCHES MSVC)
        set_property(TEST "types:conversion_test" APPEND PROPERTY
                     ENVIRONMENT "PATH=${PATH_STRING}")
    endif()
    
endif(BUILD_SHARED_LIBRARIES)

