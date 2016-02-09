#need to define the version of the library
set(SOURCES add_operator_test.cpp
            div_operator_test.cpp
            inplace_arithmetics_test.cpp
            mult_operator_test.cpp
            sub_operator_test.cpp
    )


link_directories("${CMAKE_CURRENT_BINARY_DIR}/../../src")
add_executable(math_test EXCLUDE_FROM_ALL ${SOURCES} $<TARGET_OBJECTS:test_common>)
add_executable(random_ranges EXCLUDE_FROM_ALL random_ranges.cpp)

target_link_libraries(math_test pnicore)
if(CMAKE_CXX_COMPILER_ID MATCHES GNU)
    target_link_libraries(math_test ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})
endif()

target_link_libraries(random_ranges pnicore)

add_test(NAME math_test 
         COMMAND math_test
         WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/../
         )

add_dependencies(check math_test random_ranges)
