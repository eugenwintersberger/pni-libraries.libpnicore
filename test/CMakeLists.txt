#
#build some commonly used code
# 
set(COMMON_SOURCES compare.cpp data_generator.cpp)
add_library(test_common EXCLUDE_FROM_ALL OBJECT ${COMMON_SOURCES})
target_include_directories(test_common PRIVATE ${Boost_INCLUDE_DIRS} ${PROJECT_SOURCE_DIR}/include)

#
# this macro will be used by all tests to build properly with Boost unit test
#
macro(set_shared_test_defs source_list mod_description)
    list(GET ${source_list} 0 FIRST_SOURCE_FILE)
    message(STATUS "First source file is ${FIRST_SOURCE_FILE}")
    set_source_files_properties(${FIRST_SOURCE_FILE} PROPERTIES
                                COMPILE_DEFINITIONS "BOOST_TEST_DYN_LINK; BOOST_TEST_MODULE=${mod_description}")
endmacro()

#
# need to setup the PATH environment on Windows - this is important 
# otherwise the tests will not run since they would not be able to find teh 
# appropriate libraries
#
if(CMAKE_HOST_SYSTEM_NAME MATCHES Windows)
    set(PATH_STRING "$ENV{PATH};$<TARGET_FILE_DIR:pnicore_shared>;${Boost_LIBRARY_DIRS}")
    string(REPLACE ";" "\\;" PATH_STRING "${PATH_STRING}")
endif()

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




