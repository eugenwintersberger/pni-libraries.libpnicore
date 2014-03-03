
#need to define the version of the library
set(TEST_SOURCES 
                 math/inplace_arithmetics_test.cpp
                 math/add_operator_test.cpp
                 math/div_operator_test.cpp
                 math/sub_operator_test.cpp
                 math/mult_operator_test.cpp
                 configuration_test.cpp
                 vector_adapter_test.cpp
                 )

set(COMMON_SOURCES compare.cpp)
add_library(test_common OBJECT ${COMMON_SOURCES})

add_executable(rand_test "rand_test.cpp")
target_link_libraries(rand_test pnicore)

add_subdirectory(index_maps)
add_subdirectory(dim_layout_test)
add_subdirectory(types)
add_subdirectory(arrays)
add_subdirectory(utils_test)
add_subdirectory(type_erasures)
add_subdirectory(config)



