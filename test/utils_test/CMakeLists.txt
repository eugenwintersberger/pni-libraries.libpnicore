#need to define the version of the library
set(SOURCES container_utils_array_test.cpp
            container_utils_std_test.cpp
            index_iterator_test.cpp
            iterator_test.cpp
            slice_test.cpp
    )

set_shared_test_defs(SOURCES "testing utilty code")

add_executable(utils_test ${SOURCES} $<TARGET_OBJECTS:test_common>)
target_link_libraries(utils_test pnicore_shared Boost::unit_test_framework)


add_logging_test("utils_test" utils_test 
                 ${PROJECT_BINARY_DIR}/test/utils_test)
         
if(CMAKE_HOST_SYSTEM_NAME MATCHES Windows)
    set_property(TEST utils_test APPEND PROPERTY
                 ENVIRONMENT "PATH=${PATH_STRING}") 
endif()
    
