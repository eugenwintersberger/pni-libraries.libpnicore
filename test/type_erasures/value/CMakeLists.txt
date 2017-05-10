#need to define the version of the library
set(SOURCES value_construction_test.cpp
            value_assignment_test.cpp
            uint8_value_as_test.cpp
            uint16_value_as_test.cpp
            uint32_value_as_test.cpp
            uint64_value_as_test.cpp
            int8_value_as_test.cpp
            int16_value_as_test.cpp
            int32_value_as_test.cpp
            int64_value_as_test.cpp
            float32_value_as_test.cpp
            float64_value_as_test.cpp
            float128_value_as_test.cpp
            complex32_value_as_test.cpp
            complex64_value_as_test.cpp
            complex128_value_as_test.cpp
            string_value_as_test.cpp
            binary_value_as_test.cpp
            bool_value_as_test.cpp
    )

if(BUILD_SHARED_LIBRARIES)    
    set_shared_test_defs(SOURCES "testing the value type erasure")

    add_executable(value_test ${SOURCES} $<TARGET_OBJECTS:test_common>)

    target_link_libraries(value_test pnicore_shared
                                     ${Boost_UNIT_TEST_FRAMEWORK_SHARED_LIBRARY})


    add_test(NAME "type_erasure_test:value"
             COMMAND value_test
             WORKING_DIRECTORY ${PROJECT_BINARY_DIR}/test
             )
             
    if(CMAKE_CXX_COMPILER_ID MATCHES MSVC)
        set_property(TEST "type_erasure_test:value" APPEND PROPERTY
                     ENVIRONMENT "PATH=${PATH_STRING}")
    endif()

endif(BUILD_SHARED_LIBRARIES)


