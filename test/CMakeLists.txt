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
# macro adding a test including all command line options to write logging files
#
macro (add_logging_test test_name test_target working_dir)
    set(TEST_LOG_FILE ${TEST_LOG_PATH}/${test_target}.log.xml)
    set(TEST_REPORT_FILE ${TEST_REPORT_PATH}/${test_target}.report.xml)

    message(STATUS "log file: ${TEST_LOG_FILE}")
    message(STATUS "report file: ${TEST_REPORT_FILE}")

    #we need to create separate options configurations depending on the Boost
    #version installed 
    if(Boost_VERSION EQUAL 106200)
        message(STATUS "Setting up test for Boost Unit test version 1.6.2")
        set(LOG_OPTIONS --logger=XML,all,${TEST_LOG_FILE})
        set(REPORT_OPTIONS --report_level=detailed --report_format=XML --report_sink=${TEST_REPORT_FILE})
    else()
        set(LOG_OPTIONS --log_level=all --log_sink=${TEST_LOG_FILE})
        set(REPORT_OPTIONS --report_level=detailed --report_sink=${TEST_REPORT_FILE})
        if(Boost_VERSION LESS 106000)
            list(APPEND LOG_OPTIONS "--log_format=xml")
            list(APPEND REPORT_OPTIONS "--report_format=xml")
        else()
            list(APPEND LOG_OPTIONS "--log_format=XML")
            list(APPEND LOG_OPTIONS "--report_format=XML")
        endif()
    endif()
   
    add_test(NAME "${test_name}"
             COMMAND ${test_target} ${LOG_OPTIONS} ${REPORT_OPTIONS}
             WORKING_DIRECTORY ${working_dir})
    #in all cases we have to remove the log and report files
    set_property(DIRECTORY APPEND PROPERTY ADDITIONAL_MAKE_CLEAN_FILES
    ${TEST_LOG_FILE} ${TEST_REPORT_FILE})
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

