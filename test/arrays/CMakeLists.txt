#need to define the version of the library
set(SOURCES scalar_test.cpp
            array_selection_test.cpp
            array_view_test.cpp
            array_view_unary_arithmetic_test.cpp
            dynamic_mdarray_test.cpp
            fix_mdarray_test.cpp
            static_mdarray_test.cpp
            mdarray_test.cpp
            array_view_utils_test.cpp
    )
   
if(CMAKE_CXX_COMPILER_ID MATCHES MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /bigobj")
endif()

if(BUILD_SHARED_LIBRARIES)
    set_shared_test_defs(SOURCES "Testing array functions")    

    add_executable(arrays_test_shared ${SOURCES}
                                      $<TARGET_OBJECTS:test_common>)
    target_link_libraries(arrays_test_shared pnicore_shared
                                      ${Boost_UNIT_TEST_FRAMEWORK_SHARED_LIBRARY})

    add_test(NAME arrays_test_shared 
             COMMAND arrays_test_shared
             WORKING_DIRECTORY ${PROJECT_BINARY_DIR}/test
             )
             
    if(CMAKE_CXX_COMPILER_ID MATCHES MSVC)
        set_property(TEST arrays_test_shared APPEND PROPERTY
                     ENVIRONMENT "PATH=${PATH_STRING}")
    endif()
    
endif(BUILD_SHARED_LIBRARIES)




