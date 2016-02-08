#need to define the version of the library
set(SOURCES container_utils_array_test.cpp
            container_utils_std_test.cpp
            index_iterator_test.cpp
            iterator_test.cpp
            slice_test.cpp
    )


link_directories("${CMAKE_CURRENT_BINARY_DIR}/../../src")
add_executable(utils_test EXCLUDE_FROM_ALL ${SOURCES} $<TARGET_OBJECTS:test_common>)
target_link_libraries(utils_test pnicore)

add_test(NAME utils_test 
         COMMAND utils_test
         WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/../
         )

add_dependencies(check utils_test)
