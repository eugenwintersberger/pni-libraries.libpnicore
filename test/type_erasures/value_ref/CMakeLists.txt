#need to define the version of the library
set(SOURCES value_ref_construction_test.cpp
            value_ref_assignment_test.cpp
    )


link_directories("${CMAKE_CURRENT_BINARY_DIR}/../../../src")
add_executable(value_ref_test EXCLUDE_FROM_ALL ${SOURCES} $<TARGET_OBJECTS:test_common>)
target_link_libraries(value_ref_test pnicore_shared)

if(CMAKE_CXX_COMPILER_ID MATCHES GNU)
    target_link_libraries(value_ref_test ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})
endif()

add_test(NAME "type_erasure_test:value_ref"
         COMMAND value_ref_test)

add_dependencies(check value_ref_test)


