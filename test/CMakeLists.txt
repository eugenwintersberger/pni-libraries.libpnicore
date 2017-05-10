
#build some commonly used code
set(COMMON_SOURCES compare.cpp data_generator.cpp)
include_directories(${Boost_INCLUDE_DIR})
add_library(test_common EXCLUDE_FROM_ALL OBJECT ${COMMON_SOURCES})

set(CTEST_ENVIRONMENT "PATH=C:/Program Files/DESY Software Distribution/lib\;D:/Development/libpnicore-build/src/Debug\;%PATH%")

macro(set_shared_test_defs source_list mod_description)
    list(GET ${source_list} 0 FIRST_SOURCE_FILE)
    message(STATUS "First source file is ${FIRST_SOURCE_FILE}")
    set_source_files_properties(${FIRST_SOURCE_FILE} PROPERTIES
                                COMPILE_DEFINITIONS "BOOST_TEST_DYN_LINK; BOOST_TEST_MODULE=${mod_description}")
endmacro()

add_executable(rand_test EXCLUDE_FROM_ALL "rand_test.cpp"
                             $<TARGET_OBJECTS:test_common>)
target_link_libraries(rand_test pnicore_shared)
#add_test(rand_test rand_test) -- need a better test here

add_executable(rand_gen EXCLUDE_FROM_ALL rand_gen.cpp)
target_link_libraries(rand_gen pnicore_shared)

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



