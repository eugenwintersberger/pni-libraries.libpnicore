
#build some commonly used code
set(COMMON_SOURCES compare.cpp data_generator.cpp)
include_directories(${Boost_INCLUDE_DIR})
add_library(test_common EXCLUDE_FROM_ALL OBJECT ${COMMON_SOURCES})

add_executable(rand_test EXCLUDE_FROM_ALL "rand_test.cpp"
                             $<TARGET_OBJECTS:test_common>)
target_link_libraries(rand_test pnicore)
#add_test(rand_test rand_test) -- need a better test here

add_executable(rand_gen EXCLUDE_FROM_ALL rand_gen.cpp)
target_link_libraries(rand_gen pnicore)

#add the check target to emulate GNU 'check' target
add_custom_target(check COMMAND ${CMAKE_CTEST_COMMAND})
add_dependencies(check rand_test)
add_dependencies(check rand_gen)

add_subdirectory(index_maps)
add_subdirectory(types)
add_subdirectory(arrays)
add_subdirectory(utils_test)
add_subdirectory(type_erasures)
add_subdirectory(config)
add_subdirectory(math)
add_subdirectory(error)


add_custom_target(build-test
                  DEPENDS arrays_test config_test error_test
                          index_maps_test math_test array_test
                          value_ref_test value_test conversion_test
                          type_test traits_test utils_test rand_test)



