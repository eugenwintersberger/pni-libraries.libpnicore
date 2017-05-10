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

if(BUILD_SHARED_LIBRARIES)
    set_shared_test_defs(SOURCES "testing type traits")

    add_executable(traits_test ${SOURCES})
    target_link_libraries(traits_test pnicore_shared
                                      ${Boost_UNIT_TEST_FRAMEWORK_SHARED_LIBRARY})

    add_test(NAME "types:traits_test" 
             COMMAND traits_test
             WORKING_DIRECTORY ${PROJECT_BINARY_DIR}/test
             )
             
    if(CMAKE_CXX_COMPILER_ID MATCHES MSVC)
        set_property(TEST "types:traits_test" APPEND PROPERTY
                     ENVIRONMENT "PATH=${PATH_STRING}")
    endif()
    
endif(BUILD_SHARED_LIBRARIES)

