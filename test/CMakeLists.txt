
#need to define the version of the library
set(TEST_SOURCES 
                 vector_adapter_test.cpp
                 )

set(COMMON_SOURCES compare.cpp)
add_library(test_common OBJECT ${COMMON_SOURCES})

add_executable(rand_test "rand_test.cpp")
target_link_libraries(rand_test pnicore)

add_subdirectory(index_maps)
#add_subdirectory(dim_layout_test)
add_subdirectory(types)
add_subdirectory(arrays)
add_subdirectory(utils_test)
add_subdirectory(type_erasures)
add_subdirectory(config)
add_subdirectory(math)
add_subdirectory(error)

configure_file(run_tests.sh run_tests.sh COPYONLY)


