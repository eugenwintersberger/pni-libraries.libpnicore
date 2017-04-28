#need to define the version of the library
set(SOURCES add_operator_test.cpp
            div_operator_test.cpp
            inplace_arithmetics_test.cpp
            mult_operator_test.cpp
            sub_operator_test.cpp
    )

if(CMAKE_CXX_COMPILER_ID MATCHES MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /bigobj")
endif()


link_directories("${CMAKE_CURRENT_BINARY_DIR}/../../src")
add_executable(math_test EXCLUDE_FROM_ALL ${SOURCES} $<TARGET_OBJECTS:test_common>)
add_executable(random_ranges EXCLUDE_FROM_ALL random_ranges.cpp)

target_link_libraries(math_test pnicore_shared)
if(CMAKE_CXX_COMPILER_ID MATCHES GNU)
    target_link_libraries(math_test ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})
endif()

target_link_libraries(random_ranges pnicore_shared)

add_test(NAME math_test 
         COMMAND math_test
         WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/../
         )

add_dependencies(check math_test random_ranges)
