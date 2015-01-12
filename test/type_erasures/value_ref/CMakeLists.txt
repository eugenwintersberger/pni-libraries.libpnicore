#need to define the version of the library
set(SOURCES value_ref_test.cpp
            value_ref_construction_test.cpp
            value_ref_assignment_test.cpp
    )


link_directories("${CMAKE_CURRENT_BINARY_DIR}/../../../src")
add_executable(value_ref_test ${SOURCES} $<TARGET_OBJECTS:test_common>)

target_link_libraries(value_ref_test pnicore)

if(CPPUNIT_FOUND)
    #add include directories
    include_directories(${CPPUNIT_INCLUDE_DIRS})

    #add libraries
    target_link_libraries(value_ref_test ${CPPUNIT_LIBRARIES})

endif()

add_test(NAME "type_erasure_test:value_ref"
         COMMAND value_ref_test
         )


