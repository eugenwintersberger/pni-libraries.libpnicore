#
# load some utilities
#
include(${PROJECT_SOURCE_DIR}/cmake/common/BoostTestConfig.cmake)


#
#build some commonly used code
#
include_directories(${PROJECT_SOURCE_DIR}/src)
set(COMMON_SOURCES compare.cpp data_generator.cpp)
add_library(test_common OBJECT ${COMMON_SOURCES})
target_include_directories(test_common PRIVATE ${Boost_INCLUDE_DIRS} ${PROJECT_SOURCE_DIR}/include)

#
# build test program for the random number generator
#
add_executable(rand_test "rand_test.cpp" $<TARGET_OBJECTS:test_common>)
target_link_libraries(rand_test PRIVATE pnicore_shared)

#
# build random number generator
#
add_executable(rand_gen rand_gen.cpp)
target_link_libraries(rand_gen pnicore_shared)

#
# build the environment test program
#
add_executable(environment_test environment_test.cpp)
add_test(NAME "Environment:test"
         COMMAND environment_test
         WORKING_DIRECTORY ${PROJECT_BINARY_DIR}/test)

#
# build all the other tests
#
add_subdirectory(index_maps)
add_subdirectory(types)
add_subdirectory(arrays)
add_subdirectory(utils_test)
add_subdirectory(type_erasures)
add_subdirectory(config)
add_subdirectory(math)
add_subdirectory(error)
add_subdirectory(exceptions)
add_subdirectory(logs)
