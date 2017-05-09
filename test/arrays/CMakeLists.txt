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
    
list(GET SOURCES 0 FIRST_SOURCE_FILE)
set_source_files_properties(${FIRST_SOURCE_FILE} PROPERTIES
                            COMPILE_DEFINITIONS "BOOST_TEST_DYN_LINK; BOOST_TEST_MODULE=Testing array functions")

if(CMAKE_CXX_COMPILER_ID MATCHES MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /bigobj")
endif()

add_executable(arrays_test EXCLUDE_FROM_ALL ${SOURCES} $<TARGET_OBJECTS:test_common>)
target_link_libraries(arrays_test pnicore_shared
                                  ${Boost_UNIT_TEST_FRAMEWORK_SHARED_LIBRARY})


add_test(NAME arrays_test 
         COMMAND arrays_test
         WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/../
         )

add_dependencies(check arrays_test)


