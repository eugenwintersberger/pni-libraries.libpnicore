#need to define the version of the library
set(SOURCES 
        array_creation_test.cpp
        array_access_test.cpp
        array_iterator_test.cpp
    )

if(CMAKE_CXX_COMPILER_ID MATCHES MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /bigobj")
endif()

set_shared_test_defs(SOURCES "testing the array type erasure")

add_executable(array_test ${SOURCES} $<TARGET_OBJECTS:test_common>)
target_link_libraries(array_test pnicore_shared Boost::unit_test_framework)

add_logging_test("type_erasure_test:array" array_test
                  ${PROJECT_BINARY_DIR}/test/type_erasures/array)
         
if(CMAKE_HOST_SYSTEM_NAME MATCHES Windows)
    set_property(TEST "type_erasure_test:array" APPEND PROPERTY
                 ENVIRONMENT "PATH=${PATH_STRING}")
endif()


