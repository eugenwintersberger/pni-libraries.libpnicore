#need to define the version of the library
set(SOURCES check_equal_size_test.cpp 
            check_index_in_dim_test.cpp 
            check_indexes_test.cpp 
            check_equal_rank_test.cpp
            check_equal_shape_test.cpp
            )

if(BUILD_SHARED_LIBRARIES)
    set_shared_test_defs(SOURCES "testing error functions")

    add_executable(error_test ${SOURCES} $<TARGET_OBJECTS:test_common>)
    target_link_libraries(error_test pnicore_shared
                                     ${Boost_UNIT_TEST_FRAMEWORK_SHARED_LIBRARY})


    add_test(NAME error_test 
             COMMAND error_test
             WORKING_DIRECTORY ${PROJECT_BINARY_DIR}/test
             )    
             
    if(CMAKE_CXX_COMPILER_ID MATCHES MSVC)
        set_property(TEST error_test APPEND PROPERTY
                     ENVIRONMENT "PATH=${PATH_STRING}")
    endif()
endif(BUILD_SHARED_LIBRARIES)

