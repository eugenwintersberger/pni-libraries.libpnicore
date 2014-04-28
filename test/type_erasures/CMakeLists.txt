#need to define the version of the library
set(SOURCES array_test.cpp
            type_erasures.cpp
            value_ref_test.cpp
            value_test.cpp
    )


link_directories("${CMAKE_CURRENT_BINARY_DIR}/../../src")
add_executable(type_erasures ${SOURCES} $<TARGET_OBJECTS:test_common>)

target_link_libraries(type_erasures pnicore)

if(CPPUNIT_FOUND)
    #add include directories
    include_directories(${CPPUNIT_INCLUDE_DIRS})

    #add libraries
    target_link_libraries(type_erasures ${CPPUNIT_LIBRARIES})

endif()

add_test(NAME type_erasures_test 
         COMMAND type_erasures
         WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/../
         )


