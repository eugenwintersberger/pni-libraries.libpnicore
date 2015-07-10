#need to define the version of the library
set(SOURCES add_operator_test.cpp
            div_operator_test.cpp
            inplace_arithmetics_test.cpp
            math_test.cpp
            mult_operator_test.cpp
            sub_operator_test.cpp
    )


link_directories("${CMAKE_CURRENT_BINARY_DIR}/../../src")
add_executable(math_test EXCLUDE_FROM_ALL ${SOURCES} $<TARGET_OBJECTS:test_common>)

target_link_libraries(math_test pnicore)

if(CPPUNIT_FOUND)
    #add include directories
    include_directories(${CPPUNIT_INCLUDE_DIRS})

    #add libraries
    target_link_libraries(math_test ${CPPUNIT_LIBRARIES})

endif()

add_test(NAME math_test 
         COMMAND math_test
         WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/../
         )
