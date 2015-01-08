#need to define the version of the library
set(SOURCES value_test.cpp
            value_construction_test.cpp
            value_assignment_test.cpp
            uint8_value_as_test.cpp
            uint16_value_as_test.cpp
            uint32_value_as_test.cpp
            uint64_value_as_test.cpp
    )


link_directories("${CMAKE_CURRENT_BINARY_DIR}/../../../src")
add_executable(value_test ${SOURCES} $<TARGET_OBJECTS:test_common>)

target_link_libraries(value_test pnicore)

if(CPPUNIT_FOUND)
    #add include directories
    include_directories(${CPPUNIT_INCLUDE_DIRS})

    #add libraries
    target_link_libraries(value_test ${CPPUNIT_LIBRARIES})

endif()

add_test(NAME "type_erasure_test:value"
         COMMAND value_test
         )


