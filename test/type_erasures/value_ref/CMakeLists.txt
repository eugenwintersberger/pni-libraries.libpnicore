#need to define the version of the library
set(SOURCES value_ref_construction_test.cpp
            value_ref_assignment_test.cpp
    )

if(BUILD_SHARED_LIBRARIES)
    set_shared_test_defs(SOURCES "testing the value_ref type erasure")
    add_executable(value_ref_test ${SOURCES} $<TARGET_OBJECTS:test_common>)
    target_link_libraries(value_ref_test pnicore_shared
                                         ${Boost_UNIT_TEST_FRAMEWORK_SHARED_LIBRARY})


    add_test(NAME "type_erasure_test:value_ref"
             COMMAND value_ref_test
             WORKING_DIRECTORY ${PROJECT_BINARY_DIR}/test
             )    
             
    if(CMAKE_CXX_COMPILER_ID MATCHES MSVC)
        set_property(TEST "type_erasure_test:value_ref" APPEND PROPERTY
                     ENVIRONMENT "PATH=${PATH_STRING}")
    endif()
    
endif(BUILD_SHARED_LIBRARIES)


