#need to define the version of the library
set(SOURCES 
        array_creation_test.cpp
        array_access_test.cpp
        array_iterator_test.cpp
    )

if(CMAKE_CXX_COMPILER_ID MATCHES MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /bigobj")
endif()

add_executable(array_test EXCLUDE_FROM_ALL ${SOURCES} $<TARGET_OBJECTS:test_common>)

target_link_libraries(array_test pnicore_shared)
if(CMAKE_CXX_COMPILER_ID MATCHES GNU)
    target_link_libraries(array_test ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})
endif()


add_test(NAME "type_erasure_test:array"
         COMMAND array_test
         )

add_dependencies(check array_test)

