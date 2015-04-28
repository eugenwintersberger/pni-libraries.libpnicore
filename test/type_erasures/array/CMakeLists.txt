#need to define the version of the library
set(SOURCES 
        array_test.cpp
        array_creation_test.cpp
        array_access_test.cpp
    )

add_executable(array_test ${SOURCES} $<TARGET_OBJECTS:test_common>)

target_link_libraries(array_test pnicore ${CPPUNIT_LIBRARIES})


add_test(NAME "type_erasure_test:array"
         COMMAND array_test
         )


