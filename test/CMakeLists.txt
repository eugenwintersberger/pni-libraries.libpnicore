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
# set the path where all the test reports and logs will be stored
#
set(TEST_LOG_PATH ${PROJECT_BINARY_DIR}/test/logs)
set(TEST_REPORT_PATH ${PROJECT_BINARY_DIR}/test/logs)

#
# setup lists for log and report files
#
set(TEST_LOG_FILES )
set(TEST_REPORT_FILES )

#
# macro adding a test including all command line options to write logging files
#
macro (add_logging_test test_name test_target working_dir)
    set(TEST_LOG_FILE ${TEST_LOG_PATH}/${test_target}.log.xml)
    set(TEST_REPORT_FILE ${TEST_REPORT_PATH}/${test_target}.report.xml)

    add_test(NAME "${test_name}"
             COMMAND ${test_target} 
                    --log_level=all --log_format=xml
                    --log_sink=${TEST_LOG_FILE}
                    --report_level=detailed --report_format=xml
                    --report_sink=${TEST_REPORT_FILE}
             WORKING_DIRECTORY ${working_dir})
    
list(APPEND TEST_LOG_FILES "${TEST_LOG_FILE}")
list(APPEND TEST_REPORT_FILES "${TEST_REPORT_FILE}")
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
add_subdirectory(exceptions)
add_subdirectory(logs)

#
# print a list of all log and report files
#
message(STATUS "Create the following test log files: ${TEST_LOG_FILES}")
message(STATUS "Create the following report files: ${TEST_REPORT_FILES}")


