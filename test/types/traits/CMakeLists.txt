#need to define the version of the library
set(SOURCES traits_test.cpp
            integer_type_test.cpp
            float_type_test.cpp
            complex_type_test.cpp
            numeric_type_test.cpp
    )



link_directories("${CMAKE_CURRENT_BINARY_DIR}/../../src")
add_executable(traits_test ${SOURCES})
target_link_libraries(traits_test pnicore ${CPPUNIT_LIBRARIES})


add_test(NAME "types:traits_test" 
         COMMAND traits_test
         )

